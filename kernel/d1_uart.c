// Adapted from https://github.com/bigmagic123/d1-nezha-baremeta

#include "riscv.h"
#include "d1.h"

void sys_uart_putc(uint8 uart_num, char c)
{
  while((get(r_mem(UART_LSR(uart_num)), UART_LSR_5_THRE)) == 0);
  w_mem(UART_THR(uart_num), c);
}

char sys_uart_getc(uint8 uart_num)
{
  if(get(r_mem(UART_LSR(uart_num)), UART_LSR_0_DR)) {
    return r_mem(UART_RBR(uart_num));
  } else {
    return -1;
  }
}

//D1 debug uart use GPIOB8(TX0) and GPIOB9(RX0)
void sys_uart0_init(void)
{
  virtual_addr_t addr;
  uint32 val;

  /* Config GPIOB8 and GPIOB9 to txd0 and rxd0 */
  addr = GPIO_PB_CFG1;
  val = r_mem(addr);
  // config TX
  val = set(val, 0b0110, BITS(0, 3));
  w_mem(addr, val);

  val = r_mem(addr);
  // config RX
  val = set(val, 0b0110, BITS(4, 7));
  w_mem(addr, val);

  /* Open the clock gate for uart0 */
  addr = CCU_UART_BGR_REG;
  val = r_mem(addr);
  val = on(val, BIT(0));
  w_mem(addr, val);

  /* De-assert uart0 reset */
  addr = CCU_UART_BGR_REG;
  val = r_mem(addr);
  val = on(val, BIT(16));
  w_mem(addr, val);


  /* Config uart0 to 115200-8-1-0 */
  w_mem(UART_DLH(0), 0x0);      //disable all interrupt
  w_mem(UART_FCR(0), 0xf7);     //reset fifo
  w_mem(UART_MCR(0), 0x0);      //uart mode
  //set 115200
  val = r_mem(UART_LCR(0));
  val |= (1 << 7);                    //select Divisor Latch LS Register
  w_mem( UART_LCR(0), val);
  w_mem(UART_DLL(0), 0xd & 0xff);   // 0x0d=13 240000000/(13*16) = 115200 Divisor Latch Lows
  w_mem(UART_DLH(0), (0xd >> 8) & 0xff); //Divisor Latch High
  val = r_mem( UART_LCR(0));
  val &= ~(1 << 7);
  w_mem(UART_LCR(0), val);

  val = r_mem(UART_LCR(0));
  val &= ~0x1f;
  val |= (0x3 << 0) | (0 << 2) | (0x0 << 3); //8 bit, 1 stop bit,parity disabled
  w_mem(UART_LCR(0), val);
  w_mem(UART_IER(0), 1); // only enable RX IRQ
  // BUG:, system hangs when also enabling TX IRQ
}