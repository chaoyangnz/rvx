#include "clk.h"
#include "riscv.h"
#include "defs.h"
#include "bits.h"

static void set_pll_cpux_axi(void) {
  uint32 val;
//  uint32 val1;

  // CCU_RISCV_CLK_REG
  // 0:4    RISC-V_DIV_CFG. Factor M. M = FACTOR_M +1. FACTOR_M is from 0 to 31.
  // 5:7    -
  // 8:9    RISC-V_AXI_DIV_CFG. Factor N. N = FACTOR_N +1. FACTOR_N is from 1 to 3. Note: The clock division is lack of glitch switching and supports dynamic configuration.
  // 10:23  -
  // 24:26  RISC-V_CLK_SEL. Clock Source Select, 000: HOSC 001: CLK32K 010: CLK16M_RC 011: PLL_PERI(800M) 100: PLL_PERI(1X) 101: PLL_CPU 110: PLL_AUDIO1(DIV2) RISC-V Clock = Clock Source/M. RISC-V_AXI Clock = RISC-V Clock/N.
  // 27:31  -

  /* Select cpux clock src (24:26) to OSC24mhz, axi divide ratio N (8:9) is 3, system apb clk ratio M (0:4) is 4 */
//  w_mem(CCU_RISCV_CLK_REG, (0 << 24) | (3 << 8) | (1 << 0));
  val = bits(0b000, 24, 26) | bits(0b11, 8, 9) | bits(0b00001, 0, 4);
  w_mem(CCU_RISCV_CLK_REG, val);
  delay(1);

  // CCU_PLL_CPU_CTRL_REG
  // 0:1    PLL_M. M = PLL_FACTOR_M + 1. PLL_FACTOR_M is from 0 to 3. Note: The M factor is only for testing.
  // 2:4    -
  // 5      PLL_LOCK_MDSEL PLL Lock Level 0: 24-26 Clock Cycles 1: 23-27 Clock Cycles
  // 6:7    PLL_UNLOCK_MDSEL PLL Unlock Level 00: 21-29 Clock Cycles 01: 22-28 Clock Cycles 1X: 20-30 Clock Cycles
  // 8:15   PLL_N N= PLL_N +1 PLL_N is from 0 to 254. In application, PLL_N shall be more than or equal to 12.
  // 16-23  -
  // 24-26  PLL_LOCK_TIME. PLL Lock Time. The bit indicates the step amplitude from one frequency to another.
  // 27     PLL_OUTPUT_GATE. PLL Output Gating Enable. 0: Disable 1: Enable. The bit is used to control the output enable of the PLL.
  // 28     LOCK. PLL Lock Status. 0: Unlocked. 1: Locked (It indicates that the PLL has been stable.)
  // 29     LOCK_ENABLE. Lock Enable. 0: Disable 1: Enable
  // 30     PLL_LDO_EN. LDO Enable. 0: Disable 1: Enable
  // 31     PLL_EN. PLL Enable. 0: Disable 1: Enable. PLL_CPU= InputFreq*N. The PLL_CPU output frequency must be in the range from 200 MHz to 3 GHz. And the default value of PLL_CPU is 408 MHz when the crystal oscillator is 24 MHz.

  /* Disable PLL gating */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = off_bit(val, 27);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Enable PLL LDO */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = on_bit(val, 30);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);
  delay(5);

  /* Set default clk to 1008mhz */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = set_bits(val, 0b00, 16, 17);
  val = set_bits(val, 0b00101001, 8, 15);
  val = set_bits(val, 0b00, 0, 1);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Lock enable */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = set_bit(val, 1, 29);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Enable pll */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = on_bit(val, 31);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Wait pll stable */
  while (!(r_mem(CCU_PLL_CPU_CTRL_REG) & (0x1 << 28)));
  delay(20);

  /* Enable pll gating */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = on_bit(val, 27);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Lock disable */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = off_bit(val, 29);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);
  delay(1);

  /* Set and change cpu clk src */
  val = r_mem(CCU_RISCV_CLK_REG);
  val = set_bits(val, 0b101, 24, 26);
  val = set_bits(val, 0b01, 8, 9);
  val = set_bits(val, 0b00000u, 0, 4);
  w_mem(CCU_RISCV_CLK_REG, val);
  delay(1);
}

static void set_pll_periph0(void) {
  uint32 val;

  // PLL_PERI0_CTRL_REG
  // 0      -
  // 1      PLL_INPUT_DIV2. PLL Input Div M. M1=PLL_INPUT_DIV2 + 1. PLL_INPUT_DIV2 is from 0 to 1.
  // 2:4    -
  // 5      PLL_LOCK_MDSEL. PLL Lock Level. 0: 24-26 Clock Cycles 1: 23-27 Clock Cycles
  // 6:7    PLL_UNLOCK_MDSEL. PLL Unlock Level. 00: 21-29 Clock Cycles 01: 22-28 Clock Cycles 1X: 20-30 Clock Cycles
  // 8:15   PLL_N. PLL N. N= PLL_N +1. PLL_N is from 0 to 254. In application, PLL_N shall be more than or equal to 12.
  // 16:18  PLL_P0. PLL Output Div P0. P0=PLL_OUTPUT_DIV_P0 + 1. PLL_OUTPUT_DIV_P0 is from 0 to 7.
  // 19     -
  // 20:22  PLL_P1. PLL Output Div P1. P1=PLL_OUTPUT_DIV_P1 + 1. PLL_OUTPUT_DIV_P1 is from 0 to 7.
  // 23     -
  // 24     PLL_SDM_EN. PLL SDM Enable. 0: Disable 1: Enable. Enable spread spectrum and decimal division.
  // 25:26  -
  // 27     PLL_OUTPUT_GATE. PLL Output Gating Enable. 0: Disable 1: Enable. The bit is used to control the output enable of PLL.
  // 28     LOCK. PLL Lock. 0: Unlocked 1: Locked (It indicates that the PLL has been stable.)
  // 29     LOCK_ENABLE. Lock Enable. 0: Disable 1: Enable
  // 30     PLL_LDO_EN. LDO Enable. 0: Disable 1: Enable
  // 31     PLL_EN. PLL Enable. 0: Disable 1: Enable. PLL_PERI(2X) = 24 MHz*N/M/P0 PLL_PERI(1X) = 24 MHz*N/M/P0/2 PLL_PERI(800M) = 24 MHz*N/M/P1. When the crystal oscillator is 24 MHz, the default frequency of PLL_PERI(2X) is 1.2 GHz, the default frequency of PLL_PERI(1X) is 600 MHz, and the default frequency of PLL_PERI(800M) is 800 MHz. The output clock of PLL_PERI(2X) is fixed to 1.2 GHz and not suggested to change the parameter.

  /* Periph0 has been enabled */
  if (get_bit(r_mem(CCU_PLL_PERI0_CTRL_REG), 31))
    return;

  // PSI_CLK_REG
  // 0:1    FACTOR_M. Factor M. M= FACTOR_M +1. FACTOR_M is from 0 to 3.Note: The clock division is lack of glitch switching and supports dynamic configuration.
  // 2:7    -
  // 8:9    FACTOR_N. Factor N. 00: 1 01: 2 10: 4 11: 8 Note: The clock division is lack of glitch switching and supports dynamic configuration.
  // 10:23  -
  // 24:25  CLK_SRC_SEL. Clock Source Select. 000: HOSC 001: CLK32K 010: CLK16M_RC 011: PLL_PERI(1X) PSI_CLK = Clock Source/M/N. Note: The clock select is lack of glitch switching and supports dynamic configuration.
  // 26:31  -

  /* Change psi src to osc24m */
  val = r_mem(CCU_PSI_CLK_REG);
  clear_bits(val, 24, 25);
  w_mem(val, CCU_PSI_CLK_REG);

  /* Set default val */
//  w_mem(CCU_PLL_PERI0_CTRL_REG, 0x63 << 8);
  w_mem(CCU_PLL_PERI0_CTRL_REG, bits(0b01100011, 8, 15));

  /* Lock enable */
  val = r_mem(CCU_PLL_PERI0_CTRL_REG);
  on_bit(val, 29);
  w_mem(CCU_PLL_PERI0_CTRL_REG, val);

  /* Enabe pll 600m(1x) 1200m(2x) */
  val = r_mem(CCU_PLL_PERI0_CTRL_REG);
  on_bit(val, 31);
  w_mem(CCU_PLL_PERI0_CTRL_REG, val);

  /* Wait pll stable */
  while (!get_bit(r_mem(CCU_PLL_PERI0_CTRL_REG), 28));
  delay(20);

  /* Lock disable */
  val = r_mem(CCU_PLL_PERI0_CTRL_REG);
  off_bit(val, 29);
  w_mem(CCU_PLL_PERI0_CTRL_REG, val);
}

static void set_ahb(void) {
  w_mem(CCU_PSI_CLK_REG, (2 << 0) | (0 << 8));
  w_mem(CCU_PSI_CLK_REG, r_mem(CCU_PSI_CLK_REG) | (0x03 << 24));
  delay(1);
}

static void set_apb(void) {
  w_mem(CCU_APB0_CLK_REG, (2 << 0) | (1 << 8));
  w_mem(CCU_APB0_CLK_REG, (0x03 << 24) | r_mem(CCU_APB0_CLK_REG));
  delay(1);
}

static void set_dma(void) {
  /* Dma reset */
  w_mem(CCU_DMA_BGR_REG, r_mem(CCU_DMA_BGR_REG) | (1 << 16));
  delay(20);
  /* Enable gating clock for dma */
  w_mem(CCU_DMA_BGR_REG, r_mem(CCU_DMA_BGR_REG) | (1 << 0));
}

static void set_mbus(void) {
  uint32 val;

  /* Reset mbus domain */
  val = r_mem(CCU_MBUS_CLK_REG);
  val |= (0x1 << 30);
  w_mem(CCU_MBUS_CLK_REG, val);
  delay(1);
}

static void set_module(virtual_addr_t addr) {
  uint32 val;

  if (!(r_mem(addr) & (1 << 31))) {
    val = r_mem(addr);
    w_mem(addr, val | (1 << 31) | (1 << 30));

    /* Lock enable */
    val = r_mem(addr);
    val |= (1 << 29);
    w_mem(addr, val);

    /* Wait pll stable */
    while (!(r_mem(addr) & (0x1 << 28)));
    delay(20);

    /* Lock disable */
    val = r_mem(addr);
    val &= ~(1 << 29);
    w_mem(addr, val);
  }
}

void clk_enable_module_uart(virtual_addr_t addr, uint8 uart_num) {
  uint32 val;
  /* Open the clock gate for uart */
  val = r_mem(addr);
  val |= 1 << (0 + uart_num);
  w_mem(addr, val);

  /* Deassert uart reset */
  val = r_mem(addr);
  val |= 1 << (16 + uart_num);
  w_mem(addr, val);
}

void sys_clock_init(void) {
  set_pll_cpux_axi();
  set_pll_periph0();
  set_ahb();
  set_apb();
  set_dma();
  set_mbus();
  set_module(CCU_PLL_PERI0_CTRL_REG);
  set_module(CCU_PLL_VIDEO0_CTRL_REG);
  set_module(CCU_PLL_VIDEO1_CTRL_REG);
  set_module(CCU_PLL_VE_CTRL);
  set_module(CCU_PLL_AUDIO0_CTRL_REG);
  set_module(CCU_PLL_AUDIO1_CTRL_REG);
}

// delay in microseconds
// 1μs = 1MHz: our CPU reference clock frequency is 24MHz which is used by mtime, so 1 CPU cycle is 1/24 μs
// For 1μs, we need 24 CPU cycles
void delay(unsigned long μs)
{
  uint64 cycle1 = r_mtime();
  uint64 cycle2 = cycle1 + μs * D1_REFERENCE_CLOCK;
  do {
    cycle1 = r_mtime();
  } while(cycle2 >= cycle1);
}