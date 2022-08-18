/*
 * sys-clock.c
 *
 * Copyright(c) 2007-2021 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#include "clk.h"
#include "riscv.h"

static void set_pll_cpux_axi(void) {
  uint32_t val;

  /* Select cpux clock src to osc24m, axi divide ratio is 3, system apb clk ratio is 4 */
  w_mem(D1_CCU_BASE + CCU_RISCV_CLK_REG, (0 << 24) | (3 << 8) | (1 << 0));
  delay(1);

  /* Disable pll gating */
  val = r_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG);
  val &= ~(1 << 27);
  w_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG, val);

  /* Enable pll ldo */
  val = r_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG);
  val |= (1 << 30);
  w_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG, val);
  delay(5);

  /* Set default clk to 1008mhz */
  val = r_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG);
  val &= ~((0x3 << 16) | (0xff << 8) | (0x3 << 0));
  val |= (41 << 8);
  w_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG, val);

  /* Lock enable */
  val = r_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG);
  val |= (1 << 29);
  w_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG, val);

  /* Enable pll */
  val = r_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG);
  val |= (1 << 31);
  w_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG, val);

  /* Wait pll stable */
  while (!(r_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG) & (0x1 << 28)));
  delay(20);

  /* Enable pll gating */
  val = r_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG);
  val |= (1 << 27);
  w_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG, val);

  /* Lock disable */
  val = r_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG);
  val &= ~(1 << 29);
  w_mem(D1_CCU_BASE + CCU_PLL_CPU_CTRL_REG, val);
  delay(1);

  /* Set and change cpu clk src */
  val = r_mem(D1_CCU_BASE + CCU_RISCV_CLK_REG);
  val &= ~(0x07 << 24 | 0x3 << 8 | 0xf << 0);
  val |= (0x05 << 24 | 0x1 << 8);
  w_mem(D1_CCU_BASE + CCU_RISCV_CLK_REG, val);
  delay(1);
}

static void set_pll_periph0(void) {
  uint32_t val;

  /* Periph0 has been enabled */
  if (r_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG) & (1 << 31))
    return;

  /* Change psi src to osc24m */
  val = r_mem(D1_CCU_BASE + CCU_PSI_CLK_REG);
  val &= (~(0x3 << 24));
  w_mem(val, D1_CCU_BASE + CCU_PSI_CLK_REG);

  /* Set default val */
  w_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG, 0x63 << 8);

  /* Lock enable */
  val = r_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG);
  val |= (1 << 29);
  w_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG, val);

  /* Enabe pll 600m(1x) 1200m(2x) */
  val = r_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG);
  val |= (1 << 31);
  w_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG, val);

  /* Wait pll stable */
  while (!(r_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG) & (0x1 << 28)));
  delay(20);

  /* Lock disable */
  val = r_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG);
  val &= ~(1 << 29);
  w_mem(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG, val);
}

static void set_ahb(void) {
  w_mem(D1_CCU_BASE + CCU_PSI_CLK_REG, (2 << 0) | (0 << 8));
  w_mem(D1_CCU_BASE + CCU_PSI_CLK_REG, r_mem(D1_CCU_BASE + CCU_PSI_CLK_REG) | (0x03 << 24));
  delay(1);
}

static void set_apb(void) {
  w_mem(D1_CCU_BASE + CCU_APB0_CLK_REG, (2 << 0) | (1 << 8));
  w_mem(D1_CCU_BASE + CCU_APB0_CLK_REG, (0x03 << 24) | r_mem(D1_CCU_BASE + CCU_APB0_CLK_REG));
  delay(1);
}

static void set_dma(void) {
  /* Dma reset */
  w_mem(D1_CCU_BASE + CCU_DMA_BGR_REG, r_mem(D1_CCU_BASE + CCU_DMA_BGR_REG) | (1 << 16));
  delay(20);
  /* Enable gating clock for dma */
  w_mem(D1_CCU_BASE + CCU_DMA_BGR_REG, r_mem(D1_CCU_BASE + CCU_DMA_BGR_REG) | (1 << 0));
}

static void set_mbus(void) {
  uint32_t val;

  /* Reset mbus domain */
  val = r_mem(D1_CCU_BASE + CCU_MBUS_CLK_REG);
  val |= (0x1 << 30);
  w_mem(D1_CCU_BASE + CCU_MBUS_CLK_REG, val);
  delay(1);
}

static void set_module(virtual_addr_t addr) {
  uint32_t val;

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

void clk_enable_module_uart(virtual_addr_t addr, uint8_t uart_num) {
  uint32_t val;
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
  set_module(D1_CCU_BASE + CCU_PLL_PERI0_CTRL_REG);
  set_module(D1_CCU_BASE + CCU_PLL_VIDEO0_CTRL_REG);
  set_module(D1_CCU_BASE + CCU_PLL_VIDEO1_CTRL_REG);
  set_module(D1_CCU_BASE + CCU_PLL_VE_CTRL);
  set_module(D1_CCU_BASE + CCU_PLL_AUDIO0_CTRL_REG);
  set_module(D1_CCU_BASE + CCU_PLL_AUDIO1_CTRL_REG);
}

// delay in microseconds
// 1μs = 1MHz: our CPU clock frequency is 24MHz, so 1 CPU cycle is 1/24 μs
// For 1μs, we need 24 CPU cycles
void delay(unsigned long μs)
{
  uint64_t cycle1 = r_mtime();
  uint64_t cycle2 = cycle1 + μs * 24;
  do {
    cycle1 = r_mtime();
  } while(cycle2 >= cycle1);
}