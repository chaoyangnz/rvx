#ifndef __D1_REG_CCU_H__
#define __D1_REG_CCU_H__

#include "bitfields.h"

#define D1_REFERENCE_CLOCK  24 // in MHz

#define D1_CCU_BASE                        (0x02001000)    //D1 CCU

#define CCU_PLL_CPU_CTRL_REG               (D1_CCU_BASE + 0x000)
#define CCU_PLL_DDR_CTRL_REG               (D1_CCU_BASE + 0x010)
#define CCU_PLL_PERI0_CTRL_REG             (D1_CCU_BASE + 0x020)
#define CCU_PLL_PERI1_CTRL_REG             (D1_CCU_BASE + 0x028)         //NO USER
#define CCU_PLL_GPU_CTRL_REG               (D1_CCU_BASE + 0x030)         //NO USER
#define CCU_PLL_VIDEO0_CTRL_REG            (D1_CCU_BASE + 0x040)
#define CCU_PLL_VIDEO1_CTRL_REG            (D1_CCU_BASE + 0x048)
#define CCU_PLL_VE_CTRL                    (D1_CCU_BASE + 0x058)
#define CCU_PLL_DE_CTRL                    (D1_CCU_BASE + 0x060)
#define CCU_PLL_HSIC_CTRL                  (D1_CCU_BASE + 0x070)
#define CCU_PLL_AUDIO0_CTRL_REG            (D1_CCU_BASE + 0x078)
#define CCU_PLL_AUDIO1_CTRL_REG            (D1_CCU_BASE + 0x080)
#define CCU_PLL_DDR_PAT0_CTRL_REG          (D1_CCU_BASE + 0x110)
#define CCU_PLL_DDR_PAT1_CTRL_REG          (D1_CCU_BASE + 0x114)
#define CCU_PLL_PERI0_PAT0_CTRL_REG        (D1_CCU_BASE + 0x120)
#define CCU_PLL_PERI0_PAT1_CTRL_REG        (D1_CCU_BASE + 0x124)
#define CCU_PLL_PERI1_PAT0_CTRL_REG        (D1_CCU_BASE + 0x128)
#define CCU_PLL_PERI1_PAT1_CTRL_REG        (D1_CCU_BASE + 0x12c)
#define CCU_PLL_GPU_PAT0_CTRL_REG          (D1_CCU_BASE + 0x130)
#define CCU_PLL_GPU_PAT1_CTRL_REG          (D1_CCU_BASE + 0x134)
#define CCU_PLL_VIDEO0_PAT0_CTRL_REG       (D1_CCU_BASE + 0x140)
#define CCU_PLL_VIDEO0_PAT1_CTRL_REG       (D1_CCU_BASE + 0x144)
#define CCU_PLL_VIDEO1_PAT0_CTRL_REG       (D1_CCU_BASE + 0x148)
#define CCU_PLL_VIDEO1_PAT1_CTRL_REG       (D1_CCU_BASE + 0x14c)
#define CCU_PLL_VE_PAT0_CTRL_REG           (D1_CCU_BASE + 0x158)
#define CCU_PLL_VE_PAT1_CTRL_REG           (D1_CCU_BASE + 0x15c)
#define CCU_PLL_DE_PAT0_CTRL_REG           (D1_CCU_BASE + 0x160)
#define CCU_PLL_DE_PAT1_CTRL_REG           (D1_CCU_BASE + 0x164)
#define CCU_PLL_HSIC_PAT0_CTRL_REG         (D1_CCU_BASE + 0x170)
#define CCU_PLL_HSIC_PAT1_CTRL_REG         (D1_CCU_BASE + 0x174)
#define CCU_PLL_AUDIO0_PAT0_CTRL_REG       (D1_CCU_BASE + 0x178)
#define CCU_PLL_AUDIO0_PAT1_CTRL_REG       (D1_CCU_BASE + 0x17c)
#define CCU_PLL_AUDIO1_PAT0_CTRL_REG       (D1_CCU_BASE + 0x180)
#define CCU_PLL_AUDIO1_PAT1_CTRL_REG       (D1_CCU_BASE + 0x184)
#define CCU_PLL_CPU_BIAS_REG               (D1_CCU_BASE + 0x300)
#define CCU_PLL_DDR_BIAS_REG               (D1_CCU_BASE + 0x310)
#define CCU_PLL_PERI0_BIAS_REG             (D1_CCU_BASE + 0x320)
#define CCU_PLL_PERI1_BIAS_REG             (D1_CCU_BASE + 0x328)
#define CCU_PLL_GPU_BIAS_REG               (D1_CCU_BASE + 0x330)
#define CCU_PLL_VIDEO0_BIAS_REG            (D1_CCU_BASE + 0x340)
#define CCU_PLL_VIDEO1_BIAS_REG            (D1_CCU_BASE + 0x348)
#define CCU_PLL_VE_BIAS_REG                (D1_CCU_BASE + 0x358)
#define CCU_PLL_DE_BIAS_REG                (D1_CCU_BASE + 0x360)
#define CCU_PLL_HSIC_BIAS_REG              (D1_CCU_BASE + 0x370)
#define CCU_PLL_AUDIO0_BIAS_REG            (D1_CCU_BASE + 0x378)
#define CCU_PLL_AUDIO1_BIAS_REG            (D1_CCU_BASE + 0x380)
#define CCU_PLL_CPU_TUN_REG                (D1_CCU_BASE + 0x400)
#define CCU_CPU_AXI_CFG_REG                (D1_CCU_BASE + 0x500)
#define CCU_CPU_GATING_REG                 (D1_CCU_BASE + 0x504)
#define CCU_PSI_CLK_REG                    (D1_CCU_BASE + 0x510)
#define CCU_AHB3_CLK_REG                   (D1_CCU_BASE + 0x51c)
#define CCU_APB0_CLK_REG                   (D1_CCU_BASE + 0x520)
#define CCU_APB1_CLK_REG                   (D1_CCU_BASE + 0x524)
#define CCU_MBUS_CLK_REG                   (D1_CCU_BASE + 0x540)
#define CCU_DMA_BGR_REG                    (D1_CCU_BASE + 0x70c)
#define CCU_DRAM_CLK_REG                   (D1_CCU_BASE + 0x800)
#define CCU_MBUS_MAT_CLK_GATING_REG        (D1_CCU_BASE + 0x804)
#define CCU_DRAM_BGR_REG                   (D1_CCU_BASE + 0x80c)
#define CCU_UART_BGR_REG                   (D1_CCU_BASE + 0x90C)
#define CCU_TWI_BGR_REG                    (D1_CCU_BASE + 0x91C)
#define CCU_SPI0_BGR_REG                   (D1_CCU_BASE + 0x940)
#define CCU_SPI1_BGR_REG                   (D1_CCU_BASE + 0x944)
#define CCU_SPI_BGR_REG                    (D1_CCU_BASE + 0x96C)
#define CCU_RISCV_CLK_REG                  (D1_CCU_BASE + 0xd00)
#define CCU_RISCV_GATING_REG               (D1_CCU_BASE + 0xd04)
#define CCU_RISCV_CFG_BGR_REG              (D1_CCU_BASE + 0xd0c)

// CCU_RISCV_CLK_REG
// 0:4    RISC-V_DIV_CFG. Factor M. M = FACTOR_M +1. FACTOR_M is from 0 to 31.
#define CCU_RISCV_CLK_REG_0_4_DIV_CFG                 BITS(0, 4)
// 5:7    -
// 8:9    RISC-V_AXI_DIV_CFG. Factor N. N = FACTOR_N +1. FACTOR_N is from 1 to 3. Note: The clock division is lack of glitch switching and supports dynamic configuration.
#define CCU_RISCV_CLK_REG_8_9_AVX_DIV_CFG             BITS(8, 9)
// 10:23  -
// 24:26  RISC-V_CLK_SEL. Clock Source Select, 000: HOSC 001: CLK32K 010: CLK16M_RC 011: PLL_PERI(800M) 100: PLL_PERI(1X) 101: PLL_CPU 110: PLL_AUDIO1(DIV2) RISC-V Clock = Clock Source/M. RISC-V_AXI Clock = RISC-V Clock/N.
#define CCU_RISCV_CLK_REG_24_26_CLK_SEL               BITS(24, 26)
// 27:31  -


// CCU_PLL_CPU_CTRL_REG
// 0:1    PLL_M. M = PLL_FACTOR_M + 1. PLL_FACTOR_M is from 0 to 3. Note: The M factor is only for testing.
#define CCU_PLL_CPU_CTRL_REG_0_1_PLL_M                BITS(0, 1)
// 2:4    -
// 5      PLL_LOCK_MDSEL PLL Lock Level 0: 24-26 Clock Cycles 1: 23-27 Clock Cycles
#define CCU_PLL_CPU_CTRL_REG_5_PLL_LOCK_MDSEL         BIT(5)
// 6:7    PLL_UNLOCK_MDSEL PLL Unlock Level 00: 21-29 Clock Cycles 01: 22-28 Clock Cycles 1X: 20-30 Clock Cycles
#define CCU_PLL_CPU_CTRL_REG_6_7_PLL_UNLOCK_MDSEL     BITS(6, 7)
// 8:15   PLL_N N= PLL_N +1 PLL_N is from 0 to 254. In application, PLL_N shall be more than or equal to 12.
#define CCU_PLL_CPU_CTRL_REG_8_15_PLL_N     BITS(8, 15)
// 16-23  -
// 24-26  PLL_LOCK_TIME. PLL Lock Time. The bit indicates the step amplitude from one frequency to another.
#define CCU_PLL_CPU_CTRL_REG_24_26_PLL_LOCK_TIME      BITS(24, 26)
// 27     PLL_OUTPUT_GATE. PLL Output Gating Enable. 0: Disable 1: Enable. The bit is used to control the output enable of the PLL.
#define CCU_PLL_CPU_CTRL_REG_27_PLL_OUTPUT_GATE       BIT(27)
// 28     LOCK. PLL Lock Status. 0: Unlocked. 1: Locked (It indicates that the PLL has been stable.)
#define CCU_PLL_CPU_CTRL_REG_28_LOCK                  BIT(28)
// 29     LOCK_ENABLE. Lock Enable. 0: Disable 1: Enable
#define CCU_PLL_CPU_CTRL_REG_29_LOCK_ENABLE           BIT(29)
// 30     PLL_LDO_EN. LDO Enable. 0: Disable 1: Enable
#define CCU_PLL_CPU_CTRL_REG_30_PLL_LDO_EN            BIT(30)
// 31     PLL_EN. PLL Enable. 0: Disable 1: Enable. PLL_CPU= InputFreq*N. The PLL_CPU output frequency must be in the range from 200 MHz to 3 GHz. And the default value of PLL_CPU is 408 MHz when the crystal oscillator is 24 MHz.
#define CCU_PLL_CPU_CTRL_REG_31_PLL_EN                BIT(31)


// PSI_CLK_REG
// 0:1    FACTOR_M. Factor M. M= FACTOR_M +1. FACTOR_M is from 0 to 3.Note: The clock division is lack of glitch switching and supports dynamic configuration.
#define CCU_PSI_CLK_REG_0_1_FACTOR_M                  BITS(0, 1)
// 2:7    -
// 8:9    FACTOR_N. Factor N. 00: 1 01: 2 10: 4 11: 8 Note: The clock division is lack of glitch switching and supports dynamic configuration.
#define CCU_PSI_CLK_REG_8_9_FACTOR_N                  BITS(8, 9)
// 10:23  -
// 24:25  CLK_SRC_SEL. Clock Source Select. 000: HOSC 001: CLK32K 010: CLK16M_RC 011: PLL_PERI(1X) PSI_CLK = Clock Source/M/N. Note: The clock select is lack of glitch switching and supports dynamic configuration.
#define CCU_PSI_CLK_REG_24_25_CLK_SRC_SEL             BITS(24, 25)
// 26:31  -


// PLL_PERI0_CTRL_REG
// 0      -
// 1      PLL_INPUT_DIV2. PLL Input Div M. M1=PLL_INPUT_DIV2 + 1. PLL_INPUT_DIV2 is from 0 to 1.
#define CCU_PLL_PERI0_CTRL_REG_1_PLL_INPUT_DIV2       BIT(1)
// 2:4    -
// 5      PLL_LOCK_MDSEL. PLL Lock Level. 0: 24-26 Clock Cycles 1: 23-27 Clock Cycles
#define CCU_PLL_PERI0_CTRL_REG_5_PLL_LOCK_MDSEL       BIT(5)
// 6:7    PLL_UNLOCK_MDSEL. PLL Unlock Level. 00: 21-29 Clock Cycles 01: 22-28 Clock Cycles 1X: 20-30 Clock Cycles
#define CCU_PLL_PERI0_CTRL_REG_6_7_PLL_UNLOCK_MDSEL   BITS(6, 7)
// 8:15   PLL_N. PLL N. N= PLL_N +1. PLL_N is from 0 to 254. In application, PLL_N shall be more than or equal to 12.
#define CCU_PLL_PERI0_CTRL_REG_8_15_PLL_N             BITS(8, 15)
// 16:18  PLL_P0. PLL Output Div P0. P0=PLL_OUTPUT_DIV_P0 + 1. PLL_OUTPUT_DIV_P0 is from 0 to 7.
#define CCU_PLL_PERI0_CTRL_REG_16_18_PLL_P0           BITS(16, 18)
// 19     -
// 20:22  PLL_P1. PLL Output Div P1. P1=PLL_OUTPUT_DIV_P1 + 1. PLL_OUTPUT_DIV_P1 is from 0 to 7.
#define CCU_PLL_PERI0_CTRL_REG_20_22_PLL_P1           BITS(20, 22)
// 23     -
// 24     PLL_SDM_EN. PLL SDM Enable. 0: Disable 1: Enable. Enable spread spectrum and decimal division.
#define CCU_PLL_PERI0_CTRL_REG_24_PLL_SDM_EN          BIT(24)
// 25:26  -
// 27     PLL_OUTPUT_GATE. PLL Output Gating Enable. 0: Disable 1: Enable. The bit is used to control the output enable of PLL.
#define CCU_PLL_PERI0_CTRL_REG_27_PLL_OUTPUT_GATE     BIT(27)
// 28     LOCK. PLL Lock. 0: Unlocked 1: Locked (It indicates that the PLL has been stable.)
#define CCU_PLL_PERI0_CTRL_REG_28_PLL_LOCK            BIT(28)
// 29     LOCK_ENABLE. Lock Enable. 0: Disable 1: Enable
#define CCU_PLL_PERI0_CTRL_REG_29_LOCK_ENABLE         BIT(29)
// 30     PLL_LDO_EN. LDO Enable. 0: Disable 1: Enable
#define CCU_PLL_PERI0_CTRL_REG_30_PLL_LDO_EN          BIT(30)
// 31     PLL_EN. PLL Enable. 0: Disable 1: Enable. PLL_PERI(2X) = 24 MHz*N/M/P0 PLL_PERI(1X) = 24 MHz*N/M/P0/2 PLL_PERI(800M) = 24 MHz*N/M/P1. When the crystal oscillator is 24 MHz, the default frequency of PLL_PERI(2X) is 1.2 GHz, the default frequency of PLL_PERI(1X) is 600 MHz, and the default frequency of PLL_PERI(800M) is 800 MHz. The output clock of PLL_PERI(2X) is fixed to 1.2 GHz and not suggested to change the parameter.
#define CCU_PLL_PERI0_CTRL_REG_31_PLL_EN              BIT(31)

#endif /* __D1_REG_CCU_H__ */
