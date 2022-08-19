//
// low-level driver routines for 16550a UART.
//

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

// the UART control registers are memory-mapped
// at address UART0. this macro returns the
// address of one of the registers.
#define Reg(reg) ((volatile unsigned int *)(UART0 + 4*reg))

// the UART control registers.
// some have different meanings for
// read vs write.
// see http://byterunner.com/16550.html
#define RHR 0                 // receive holding register (for input bytes)
#define THR 0                 // transmit holding register (for output bytes)
#define IER 1                 // interrupt enable register
#define IER_RX_ENABLE (1<<0)
#define IER_TX_ENABLE (1<<1)
#define FCR 2                 // FIFO control register
#define FCR_FIFO_ENABLE (1<<0)
#define FCR_FIFO_CLEAR (3<<1) // clear the content of the two FIFOs
#define ISR 2                 // interrupt status register
#define LCR 3                 // line control register
#define LCR_EIGHT_BITS (3<<0)
#define LCR_BAUD_LATCH (1<<7) // special mode to set baud rate
#define LSR 5                 // line status register
#define LSR_RX_READY (1<<0)   // input is waiting to be read from RHR
#define LSR_TX_IDLE (1<<5)    // THR can accept another character to send

#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

// the transmit output buffer.
struct spinlock uart_tx_lock;
#define UART_TX_BUF_SIZE 32
char uart_tx_buf[UART_TX_BUF_SIZE];
uint64 uart_tx_w; // write next to uart_tx_buf[uart_tx_w % UART_TX_BUF_SIZE]
uint64 uart_tx_r; // read next from uart_tx_buf[uar_tx_r % UART_TX_BUF_SIZE]

extern volatile int panicked; // from printf.c

void uartstart();

void
uartinit(void)
{
  // init performed in sys_uart0_init now
  initlock(&uart_tx_lock, "uart");
}

// add a character to the output buffer and tell the
// UART to start sending if it isn't already.
// blocks if the output buffer is full.
// because it may block, it can't be called
// from interrupts; it's only suitable for use
// by write().
static void
__uartputc(int c)
{
  acquire(&uart_tx_lock);

  if(panicked){
    for(;;)
      ;
  }

  while(1){
    if(uart_tx_w == uart_tx_r + UART_TX_BUF_SIZE){
      // buffer is full.
      // wait for uartstart() to open up space in the buffer.
      sleep(&uart_tx_r, &uart_tx_lock);
    } else {
      uart_tx_buf[uart_tx_w % UART_TX_BUF_SIZE] = c;
      uart_tx_w += 1;
      uartstart();
      release(&uart_tx_lock);
      return;
    }
  }
}

void
uartputc(int c) {
  if (c == '\n') {
    __uartputc('\r');
  }
  __uartputc(c);
}


// alternate version of uartputc() that doesn't 
// use interrupts, for use by kernel printf() and
// to echo characters. it spins waiting for the uart's
// output register to be empty.
static void
__uartputc_sync(int c)
{
  push_off();

  if(panicked){
    for(;;)
      ;
  }

  // wait for Transmit Holding Empty to be set in LSR.
  while((ReadReg(LSR) & LSR_TX_IDLE) == 0)
    ;
  WriteReg(THR, c);

  pop_off();
}

void
uartputc_sync(int c) {
  if (c == '\n') {
    __uartputc_sync('\r');
  }
  __uartputc_sync(c);
}

// if the UART is idle, and a character is waiting
// in the transmit buffer, send it.
// caller must hold uart_tx_lock.
// called from both the top- and bottom-half.
void
uartstart()
{
  while(1){
    if(uart_tx_w == uart_tx_r){
      // transmit buffer is empty.
      return;
    }
    
    if((ReadReg(LSR) & LSR_TX_IDLE) == 0){
      // the UART transmit holding register is full,
      // so we cannot give it another byte.
      // it will interrupt when it's ready for a new byte.
      return;
    }
    
    int c = uart_tx_buf[uart_tx_r % UART_TX_BUF_SIZE];
    uart_tx_r += 1;
    
    // maybe uartputc() is waiting for space in the buffer.
    wakeup(&uart_tx_r);
    
    WriteReg(THR, c);
  }
}

// read one input character from the UART.
// return -1 if none is waiting.
int
uartgetc(void)
{
  if(ReadReg(LSR) & 0x01){
    // input data is ready.
    return ReadReg(RHR);
  } else {
    return -1;
  }
}

// handle a uart interrupt, raised because input has
// arrived, or the uart is ready for more output, or
// both. called from trap.c.
void
uartintr(void)
{
  // read and process incoming characters.
  while(1){
    int c = uartgetc();
    if(c == -1)
      break;
    consoleintr(c);
  }

  // send buffered characters.
  acquire(&uart_tx_lock);
  uartstart();
  release(&uart_tx_lock);
}


// Adapted from https://github.com/bigmagic123/d1-nezha-baremeta

//D1 debug uart use GPIOB8(TX0) and GPIOB9(RX0)

#define UART_BASE   (0X02500000)
#define UART1_BASE  (0X02500400)
#define UART2_BASE  (0X02500800)
#define UART3_BASE  (0X02500C00)
#define UART4_BASE  (0X02501000)
#define UART5_BASE  (0X02501400)


#define UART_RBR            (0x0000)
#define UART_THR            (0x0000)
#define UART_DLL            (0x0000)
#define UART_DLH            (0x0004)
#define UART_IER            (0x0004)
#define UART_IIR            (0x0008)
#define UART_FCR            (0x0008)
#define UART_LCR            (0x000C)
#define UART_MCR            (0x0010)
#define UART_LSR            (0x0014)
#define UART_MSR            (0x0018)
#define UART_SCH            (0x001C)
#define UART_USR            (0x007C)
#define UART_TFL            (0x0080)
#define UART_RFL            (0x0084)
#define UART_HSK            (0x0088)
#define UART_DMA_REQ_EN     (0x008C)
#define UART_HALT           (0x00A4)
#define UART_DBG_DLL        (0x00B0)
#define UART_DBG_DLH        (0x00B4)
#define UART_A_FCC          (0x00F0)
#define UART_A_RXDMA_CTRL   (0x0100)
#define UART_A_RXDMA_STR    (0x0104)
#define UART_A_RXDMA_STA    (0x0108)
#define UART_A_RXDMA_LMT    (0x010C)
#define UART_A_RXDMA_SADDRL           (0x0110)
#define UART_A_RXDMA_SADDRH           (0x0114)
#define UART_A_RXDMA_BL     (0x0118)
#define UART_A_RXDMA_IE     (0x0120)
#define UART_A_RXDMA_IS     (0x0124)
#define UART_A_RXDMA_WADDRL           (0x0128)
#define UART_A_RXDMA_WADDRH           (0x012C)
#define UART_A_RXDMA_RADDRL           (0x0130)
#define UART_A_RXDMA_RADDRH           (0x0134)
#define UART_A_RXDMA_DCNT   (0x0138)

#define UART_LSR_FIFOE		0x80    /* Fifo error */
#define UART_LSR_TEMT		0x40    /* Transmitter empty */
#define UART_LSR_THRE		0x20    /* Transmit-hold-register empty */
#define UART_LSR_BI		0x10    /* Break interrupt indicator */
#define UART_LSR_FE		0x08    /* Frame error indicator */
#define UART_LSR_PE		0x04    /* Parity error indicator */
#define UART_LSR_OE		0x02    /* Overrun error indicator */
#define UART_LSR_DR		0x01    /* Receiver data ready */
#define UART_LSR_BRK_ERROR_BITS	0x1E    /* BI, FE, PE, OE bits */

#define UART0_MODE_TX   (6)
#define UART0_MODE_RX   (6)

void sys_uart_putc(uint8 uart_num, char c)
{
  virtual_addr_t addr = UART_BASE + uart_num * 0x4000;

  while((r_mem(addr + UART_LSR) & UART_LSR_THRE) == 0);
  w_mem(addr + UART_THR, c);
}

char sys_uart_getc(uint8 uart_num)
{
  virtual_addr_t addr = UART_BASE + uart_num * 0x4000;
  if((r_mem(addr + UART_LSR) & UART_LSR_DR))
  {
    return r_mem(addr + UART_RBR);
  }
  else
  {
    return -1;
  }
}

void sys_uart0_init(void)
{
  virtual_addr_t addr;
  uint32 val;

  /* Config GPIOB8 and GPIOB9 to txd0 and rxd0 */
  addr = 0x02000030 + 0x04;
  val = r_mem(addr);
  val &= ~(0xf << ((8 & 0x7) << 2));
  val |= ((0x6 & 0xf) << ((8 & 0x7) << 2));
  w_mem(addr, val);

  val = r_mem(addr);
  val &= ~(0xf << ((9 & 0x7) << 2));
  val |= ((0x6 & 0xf) << ((9 & 0x7) << 2));
  w_mem(addr, val);

  /* Open the clock gate for uart0 */
  addr = 0x0200190c;
  val = r_mem(addr);
  val |= 1 << 0;
  w_mem(addr, val);

  /* Deassert uart0 reset */
  addr = 0x0200190c;
  val = r_mem(addr);
  val |= 1 << 16;
  w_mem(addr, val);


  /* Config uart0 to 115200-8-1-0 */
  addr = UART_BASE + 0 * 0x4000;
  w_mem(addr + UART_DLH, 0x0);      //disable all interrupt
  w_mem(addr + UART_FCR, 0xf7);     //reset fifo
  w_mem(addr + UART_MCR, 0x0);      //uart mode
  //set 115200
  val = r_mem(addr + UART_LCR);
  val |= (1 << 7);                    //select Divisor Latch LS Register
  w_mem(addr + UART_LCR, val);
  w_mem(addr + UART_DLL, 0xd & 0xff);   // 0x0d=13 240000000/(13*16) = 115200 Divisor Latch Lows
  w_mem(addr + UART_DLH, (0xd >> 8) & 0xff); //Divisor Latch High
  val = r_mem(addr + UART_LCR);
  val &= ~(1 << 7);
  w_mem(addr + UART_LCR, val);

  val = r_mem(addr + UART_LCR);
  val &= ~0x1f;
  val |= (0x3 << 0) | (0 << 2) | (0x0 << 3); //8 bit, 1 stop bit,parity disabled
  w_mem(addr + UART_LCR, val);
  w_mem(addr + UART_IER, 1); // only enable RX IRQ
  // BUG:, system hangs when also enabling TX IRQ
}