#include "clk.h"
#include "riscv.h"
#include "defs.h"
#include "bitfields.h"

static void set_pll_cpux_axi(void) {
  uint32 val;

  /* Select cpux clock src (24:26) to OSC24mhz, axi divide ratio N (8:9) is 3, system apb clk ratio M (0:4) is 4 */
  val = build(0b000, CCU_RISCV_CLK_REG_24_26_CLK_SEL) | build(0b11, CCU_RISCV_CLK_REG_8_9_AVX_DIV_CFG) | build(0b00001, CCU_RISCV_CLK_REG_0_4_DIV_CFG);
  w_mem(CCU_RISCV_CLK_REG, val);
  delay(1);

  /* Disable PLL gating */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = off(val, CCU_PLL_CPU_CTRL_REG_27_PLL_OUTPUT_GATE);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Enable PLL LDO */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = on(val, CCU_PLL_CPU_CTRL_REG_30_PLL_LDO_EN);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);
  delay(5);

  /* Set default clk to 1008mhz */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = clear(val, BITS(16, 17));
  val = set(val, 0b00101001, CCU_PLL_CPU_CTRL_REG_8_15_PLL_N);
  val = set(val, 0b00, CCU_PLL_CPU_CTRL_REG_0_1_PLL_M);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Lock enable */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = on(val, CCU_PLL_CPU_CTRL_REG_29_LOCK_ENABLE);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Enable pll */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = on(val, CCU_PLL_CPU_CTRL_REG_31_PLL_EN);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Wait pll stable */
  while (!get(r_mem(CCU_PLL_CPU_CTRL_REG), CCU_PLL_CPU_CTRL_REG_28_LOCK));
  delay(20);

  /* Enable pll gating */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = on(val, CCU_PLL_CPU_CTRL_REG_27_PLL_OUTPUT_GATE);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);

  /* Lock disable */
  val = r_mem(CCU_PLL_CPU_CTRL_REG);
  val = off(val, CCU_PLL_CPU_CTRL_REG_29_LOCK_ENABLE);
  w_mem(CCU_PLL_CPU_CTRL_REG, val);
  delay(1);

  /* Set and change cpu clk src */
  val = r_mem(CCU_RISCV_CLK_REG);
  val = set(val, 0b101, CCU_RISCV_CLK_REG_24_26_CLK_SEL);
  val = set(val, 0b01, CCU_RISCV_CLK_REG_8_9_AVX_DIV_CFG);
  val = set(val, 0b00000u, CCU_RISCV_CLK_REG_0_4_DIV_CFG);
  w_mem(CCU_RISCV_CLK_REG, val);
  delay(1);
}

static void set_pll_periph0(void) {
  uint32 val;

  /* Periph0 has been enabled */
  if (get(r_mem(CCU_PLL_PERI0_CTRL_REG), CCU_PLL_PERI0_CTRL_REG_31_PLL_EN))
    return;

  /* Change psi src to osc24m */
  val = r_mem(CCU_PSI_CLK_REG);
  clear(val, CCU_PSI_CLK_REG_24_25_CLK_SRC_SEL);
  w_mem(val, CCU_PSI_CLK_REG);

  /* Set default val */
  w_mem(CCU_PLL_PERI0_CTRL_REG, build(0b01100011, CCU_PLL_PERI0_CTRL_REG_8_15_PLL_N));

  /* Lock enable */
  val = r_mem(CCU_PLL_PERI0_CTRL_REG);
  on(val, CCU_PLL_PERI0_CTRL_REG_29_LOCK_ENABLE);
  w_mem(CCU_PLL_PERI0_CTRL_REG, val);

  /* Enabe pll 600m(1x) 1200m(2x) */
  val = r_mem(CCU_PLL_PERI0_CTRL_REG);
  on(val, CCU_PLL_PERI0_CTRL_REG_31_PLL_EN);
  w_mem(CCU_PLL_PERI0_CTRL_REG, val);

  /* Wait pll stable */
  while (!get(r_mem(CCU_PLL_PERI0_CTRL_REG), CCU_PLL_PERI0_CTRL_REG_28_PLL_LOCK));
  delay(20);

  /* Lock disable */
  val = r_mem(CCU_PLL_PERI0_CTRL_REG);
  off(val, CCU_PLL_PERI0_CTRL_REG_29_LOCK_ENABLE);
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