#ifndef __D1_H__
#define __D1_H__

#include "bitfields.h"

#define REFERENCE_CLOCK  24 // in MHz

//############################//
//                            //
//            CCU             //
//                            //
//############################//

#define CCU_BASE                        (0x02001000)    //D1 CCU

#define CCU_PLL_CPU_CTRL_REG               (CCU_BASE + 0x000)
#define CCU_PLL_DDR_CTRL_REG               (CCU_BASE + 0x010)
#define CCU_PLL_PERI0_CTRL_REG             (CCU_BASE + 0x020)
#define CCU_PLL_PERI1_CTRL_REG             (CCU_BASE + 0x028)         //NO USER
#define CCU_PLL_GPU_CTRL_REG               (CCU_BASE + 0x030)         //NO USER
#define CCU_PLL_VIDEO0_CTRL_REG            (CCU_BASE + 0x040)
#define CCU_PLL_VIDEO1_CTRL_REG            (CCU_BASE + 0x048)
#define CCU_PLL_VE_CTRL                    (CCU_BASE + 0x058)
#define CCU_PLL_DE_CTRL                    (CCU_BASE + 0x060)
#define CCU_PLL_HSIC_CTRL                  (CCU_BASE + 0x070)
#define CCU_PLL_AUDIO0_CTRL_REG            (CCU_BASE + 0x078)
#define CCU_PLL_AUDIO1_CTRL_REG            (CCU_BASE + 0x080)
#define CCU_PLL_DDR_PAT0_CTRL_REG          (CCU_BASE + 0x110)
#define CCU_PLL_DDR_PAT1_CTRL_REG          (CCU_BASE + 0x114)
#define CCU_PLL_PERI0_PAT0_CTRL_REG        (CCU_BASE + 0x120)
#define CCU_PLL_PERI0_PAT1_CTRL_REG        (CCU_BASE + 0x124)
#define CCU_PLL_PERI1_PAT0_CTRL_REG        (CCU_BASE + 0x128)
#define CCU_PLL_PERI1_PAT1_CTRL_REG        (CCU_BASE + 0x12c)
#define CCU_PLL_GPU_PAT0_CTRL_REG          (CCU_BASE + 0x130)
#define CCU_PLL_GPU_PAT1_CTRL_REG          (CCU_BASE + 0x134)
#define CCU_PLL_VIDEO0_PAT0_CTRL_REG       (CCU_BASE + 0x140)
#define CCU_PLL_VIDEO0_PAT1_CTRL_REG       (CCU_BASE + 0x144)
#define CCU_PLL_VIDEO1_PAT0_CTRL_REG       (CCU_BASE + 0x148)
#define CCU_PLL_VIDEO1_PAT1_CTRL_REG       (CCU_BASE + 0x14c)
#define CCU_PLL_VE_PAT0_CTRL_REG           (CCU_BASE + 0x158)
#define CCU_PLL_VE_PAT1_CTRL_REG           (CCU_BASE + 0x15c)
#define CCU_PLL_DE_PAT0_CTRL_REG           (CCU_BASE + 0x160)
#define CCU_PLL_DE_PAT1_CTRL_REG           (CCU_BASE + 0x164)
#define CCU_PLL_HSIC_PAT0_CTRL_REG         (CCU_BASE + 0x170)
#define CCU_PLL_HSIC_PAT1_CTRL_REG         (CCU_BASE + 0x174)
#define CCU_PLL_AUDIO0_PAT0_CTRL_REG       (CCU_BASE + 0x178)
#define CCU_PLL_AUDIO0_PAT1_CTRL_REG       (CCU_BASE + 0x17c)
#define CCU_PLL_AUDIO1_PAT0_CTRL_REG       (CCU_BASE + 0x180)
#define CCU_PLL_AUDIO1_PAT1_CTRL_REG       (CCU_BASE + 0x184)
#define CCU_PLL_CPU_BIAS_REG               (CCU_BASE + 0x300)
#define CCU_PLL_DDR_BIAS_REG               (CCU_BASE + 0x310)
#define CCU_PLL_PERI0_BIAS_REG             (CCU_BASE + 0x320)
#define CCU_PLL_PERI1_BIAS_REG             (CCU_BASE + 0x328)
#define CCU_PLL_GPU_BIAS_REG               (CCU_BASE + 0x330)
#define CCU_PLL_VIDEO0_BIAS_REG            (CCU_BASE + 0x340)
#define CCU_PLL_VIDEO1_BIAS_REG            (CCU_BASE + 0x348)
#define CCU_PLL_VE_BIAS_REG                (CCU_BASE + 0x358)
#define CCU_PLL_DE_BIAS_REG                (CCU_BASE + 0x360)
#define CCU_PLL_HSIC_BIAS_REG              (CCU_BASE + 0x370)
#define CCU_PLL_AUDIO0_BIAS_REG            (CCU_BASE + 0x378)
#define CCU_PLL_AUDIO1_BIAS_REG            (CCU_BASE + 0x380)
#define CCU_PLL_CPU_TUN_REG                (CCU_BASE + 0x400)
#define CCU_CPU_AXI_CFG_REG                (CCU_BASE + 0x500)
#define CCU_CPU_GATING_REG                 (CCU_BASE + 0x504)
#define CCU_PSI_CLK_REG                    (CCU_BASE + 0x510)
#define CCU_AHB3_CLK_REG                   (CCU_BASE + 0x51c)
#define CCU_APB0_CLK_REG                   (CCU_BASE + 0x520)
#define CCU_APB1_CLK_REG                   (CCU_BASE + 0x524)
#define CCU_MBUS_CLK_REG                   (CCU_BASE + 0x540)
#define CCU_DMA_BGR_REG                    (CCU_BASE + 0x70c)
#define CCU_DRAM_CLK_REG                   (CCU_BASE + 0x800)
#define CCU_MBUS_MAT_CLK_GATING_REG        (CCU_BASE + 0x804)
#define CCU_DRAM_BGR_REG                   (CCU_BASE + 0x80c)
#define CCU_UART_BGR_REG                   (CCU_BASE + 0x90C)
#define CCU_TWI_BGR_REG                    (CCU_BASE + 0x91C)
#define CCU_SPI0_BGR_REG                   (CCU_BASE + 0x940)
#define CCU_SPI1_BGR_REG                   (CCU_BASE + 0x944)
#define CCU_SPI_BGR_REG                    (CCU_BASE + 0x96C)
#define CCU_RISCV_CLK_REG                  (CCU_BASE + 0xd00)
#define CCU_RISCV_GATING_REG               (CCU_BASE + 0xd04)
#define CCU_RISCV_CFG_BGR_REG              (CCU_BASE + 0xd0c)

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

// 0:1    PLL_M.
// M = PLL_FACTOR_M + 1. PLL_FACTOR_M is from 0 to 3.
// Note: The M factor is only for testing.
#define CCU_PLL_CPU_CTRL_REG_0_1_PLL_M                BITS(0, 1)
// 2:4    -
// 5      PLL_LOCK_MDSEL
// PLL Lock Level 0: 24-26 Clock Cycles 1: 23-27 Clock Cycles
#define CCU_PLL_CPU_CTRL_REG_5_PLL_LOCK_MDSEL         BIT(5)
// 6:7    PLL_UNLOCK_MDSEL PLL
// Unlock Level 00: 21-29 Clock Cycles 01: 22-28 Clock Cycles 1X: 20-30 Clock Cycles
#define CCU_PLL_CPU_CTRL_REG_6_7_PLL_UNLOCK_MDSEL     BITS(6, 7)
// 8:15   PLL_N
// N= PLL_N +1 PLL_N is from 0 to 254. In application, PLL_N shall be more than or equal to 12.
#define CCU_PLL_CPU_CTRL_REG_8_15_PLL_N     BITS(8, 15)
// 16-23  -
// 24-26  PLL_LOCK_TIME.
// PLL Lock Time. The bit indicates the step amplitude from one frequency to another.
#define CCU_PLL_CPU_CTRL_REG_24_26_PLL_LOCK_TIME      BITS(24, 26)
// 27     PLL_OUTPUT_GATE.
// PLL Output Gating Enable. 0: Disable 1: Enable. The bit is used to control the output enable of the PLL.
#define CCU_PLL_CPU_CTRL_REG_27_PLL_OUTPUT_GATE       BIT(27)
// 28     LOCK. PLL
// Lock Status. 0: Unlocked. 1: Locked (It indicates that the PLL has been stable.)
#define CCU_PLL_CPU_CTRL_REG_28_LOCK                  BIT(28)
// 29     LOCK_ENABLE.
// Lock Enable. 0: Disable 1: Enable
#define CCU_PLL_CPU_CTRL_REG_29_LOCK_ENABLE           BIT(29)
// 30     PLL_LDO_EN.
// LDO Enable. 0: Disable 1: Enable
#define CCU_PLL_CPU_CTRL_REG_30_PLL_LDO_EN            BIT(30)
// 31     PLL_EN.
// PLL Enable. 0: Disable 1: Enable.
// PLL_CPU= InputFreq*N. The PLL_CPU output frequency must be in the range from 200 MHz to 3 GHz.
// And the default value of PLL_CPU is 408 MHz when the crystal oscillator is 24 MHz.
#define CCU_PLL_CPU_CTRL_REG_31_PLL_EN                BIT(31)


// PSI_CLK_REG
// 0:1    FACTOR_M.
// Factor M. M= FACTOR_M +1. FACTOR_M is from 0 to 3.
// Note: The clock division is lack of glitch switching and supports dynamic configuration.
#define CCU_PSI_CLK_REG_0_1_FACTOR_M                  BITS(0, 1)
// 2:7    -
// 8:9    FACTOR_N.
// Factor N. 00: 1 01: 2 10: 4 11: 8
// Note: The clock division is lack of glitch switching and supports dynamic configuration.
#define CCU_PSI_CLK_REG_8_9_FACTOR_N                  BITS(8, 9)
// 10:23  -
// 24:25  CLK_SRC_SEL.
// Clock Source Select. 000: HOSC 001: CLK32K 010: CLK16M_RC 011: PLL_PERI(1X) PSI_CLK = Clock Source/M/N.
// Note: The clock select is lack of glitch switching and supports dynamic configuration.
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
// 31     PLL_EN. PLL Enable.
// 0: Disable 1: Enable.
// PLL_PERI(2X) = 24 MHz*N/M/P0
// PLL_PERI(1X) = 24 MHz*N/M/P0/2
// PLL_PERI(800M) = 24 MHz*N/M/P1.
// When the crystal oscillator is 24 MHz, the default frequency of PLL_PERI(2X) is 1.2 GHz, the default frequency of PLL_PERI(1X) is 600 MHz,
// and the default frequency of PLL_PERI(800M) is 800 MHz. The output clock of PLL_PERI(2X) is fixed to 1.2 GHz and not suggested to change the parameter.
#define CCU_PLL_PERI0_CTRL_REG_31_PLL_EN              BIT(31)


//############################//
//                            //
//            GPIO            //
//                            //
//############################//

//d1 gpio base addr
#define GPIO_BASE    (0x02000000)

//PB 13 (0~12)
#define GPIO_PB_CFG0  (GPIO_BASE + 0x0030)
#define GPIO_PB_CFG1  (GPIO_BASE + 0x0034)
#define GPIO_PB_DAT   (GPIO_BASE + 0x0040)
#define GPIO_PB_DRV0  (GPIO_BASE + 0x0044)
#define GPIO_PB_DRV1  (GPIO_BASE + 0x0048)
#define GPIO_PB_PULL0 (GPIO_BASE + 0x0054)

//PC 8 (0~7)
#define GPIO_PC_CFG0  (GPIO_BASE + 0x0060)
#define GPIO_PC_DAT   (GPIO_BASE + 0x0070)
#define GPIO_PC_DRV0  (GPIO_BASE + 0x0074)
#define GPIO_PC_PULL0 (GPIO_BASE + 0x0084)

//PD 23 (0~22)
#define GPIO_PD_CFG0  (GPIO_BASE + 0x0090)
#define GPIO_PD_CFG1  (GPIO_BASE + 0x0094)
#define GPIO_PD_CFG2  (GPIO_BASE + 0x0098)
#define GPIO_PD_DAT   (GPIO_BASE + 0x00A0)
#define GPIO_PD_DRV0  (GPIO_BASE + 0x00A4)
#define GPIO_PD_DRV1  (GPIO_BASE + 0x00A8)
#define GPIO_PD_DRV2  (GPIO_BASE + 0x00AC)
#define GPIO_PD_PULL0 (GPIO_BASE + 0x00B4)
#define GPIO_PD_PULL1 (GPIO_BASE + 0x00B8)

//PE 18 (0~17)
#define GPIO_PE_CFG0  (GPIO_BASE + 0x00C0)
#define GPIO_PE_CFG1  (GPIO_BASE + 0x00C4)
#define GPIO_PE_DAT   (GPIO_BASE + 0x00D0)
#define GPIO_PE_DRV0  (GPIO_BASE + 0x00D4)
#define GPIO_PE_DRV1  (GPIO_BASE + 0x00D8)
#define GPIO_PE_PULL0 (GPIO_BASE + 0x00E4)

//PF 7  (0~7)
#define GPIO_PF_CFG0  (GPIO_BASE + 0x00F0)
#define GPIO_PF_DAT   (GPIO_BASE + 0x0100)
#define GPIO_PF_DRV0  (GPIO_BASE + 0x0104)
#define GPIO_PF_PULL0 (GPIO_BASE + 0x0114)

//PG 19 (0~18)
#define GPIO_PG_CFG0  (GPIO_BASE + 0x0120)
#define GPIO_PG_CFG1  (GPIO_BASE + 0x0124)
#define GPIO_PG_DAT   (GPIO_BASE + 0x0130)
#define GPIO_PG_DRV0  (GPIO_BASE + 0x0134)
#define GPIO_PG_DRV1  (GPIO_BASE + 0x0138)
#define GPIO_PG_DRV3  (GPIO_BASE + 0x0140)
#define GPIO_PG_PULL0 (GPIO_BASE + 0x0124)

//EINT
//PB
#define GPIO_PB_EINT_CFG0    (GPIO_BASE + 0x0220)
#define GPIO_PB_EINT_CTL     (GPIO_BASE + 0x0230)
#define GPIO_PB_EINT_STATUS  (GPIO_BASE + 0x0234)
#define GPIO_PB_EINT_DEB     (GPIO_BASE + 0x0238)

//PC
#define GPIO_PC_EINT_CFG0    (GPIO_BASE + 0x0240)
#define GPIO_PC_EINT_CTL     (GPIO_BASE + 0x0250)
#define GPIO_PC_EINT_STATUS  (GPIO_BASE + 0x0254)
#define GPIO_PC_EINT_DEB     (GPIO_BASE + 0x0258)

//PD
#define GPIO_PD_EINT_CFG0    (GPIO_BASE + 0x0260)
#define GPIO_PD_EINT_CFG1    (GPIO_BASE + 0x0264)
#define GPIO_PD_EINT_CFG2    (GPIO_BASE + 0x0268)
#define GPIO_PD_EINT_CTL     (GPIO_BASE + 0x0270)
#define GPIO_PD_EINT_STATUS  (GPIO_BASE + 0x0274)
#define GPIO_PD_EINT_DEB     (GPIO_BASE + 0x0278)

//PE
#define GPIO_PE_EINT_CFG0    (GPIO_BASE + 0x0280)
#define GPIO_PE_EINT_CFG1    (GPIO_BASE + 0x0284)
#define GPIO_PE_EINT_CTL     (GPIO_BASE + 0x0290)
#define GPIO_PE_EINT_STATUS  (GPIO_BASE + 0x0294)
#define GPIO_PE_EINT_DEB     (GPIO_BASE + 0x0298)

//PF
#define GPIO_PF_EINT_CFG0    (GPIO_BASE + 0x02A0)
#define GPIO_PF_EINT_CTL     (GPIO_BASE + 0x02B0)
#define GPIO_PF_EINT_STATUS  (GPIO_BASE + 0x02B4)
#define GPIO_PF_EINT_DEB     (GPIO_BASE + 0x02B8)

//PG
#define GPIO_PG_EINT_CFG0    (GPIO_BASE + 0x02C0)
#define GPIO_PG_EINT_CFG1    (GPIO_BASE + 0x02C4)
#define GPIO_PG_EINT_CTL     (GPIO_BASE + 0x02D0)
#define GPIO_PG_EINT_STATUS  (GPIO_BASE + 0x02D4)
#define GPIO_PG_EINT_DEB     (GPIO_BASE + 0x02D8)

#define PIO_POW_MOD_SEL         (GPIO_BASE + 0x0340)
#define PIO_POW_MS_CTL          (GPIO_BASE + 0x0344)
#define PIO_POW_VAL             (GPIO_BASE + 0x0348)
#define PIO_POW_VOL_SET_CTL     (GPIO_BASE + 0x0350)

#define     GPIO_PORT_B       (GPIO_PB_CFG0)
#define     GPIO_PORT_C       (GPIO_PC_CFG0)
#define     GPIO_PORT_D       (GPIO_PD_CFG0)
#define     GPIO_PORT_E       (GPIO_PE_CFG0)
#define     GPIO_PORT_F       (GPIO_PF_CFG0)
#define     GPIO_PORT_G       (GPIO_PG_CFG0)

#define     GPIO_PIN_0        (0)
#define     GPIO_PIN_1        (1)
#define     GPIO_PIN_2        (2)
#define     GPIO_PIN_3        (3)
#define     GPIO_PIN_4        (4)
#define     GPIO_PIN_5        (5)
#define     GPIO_PIN_6        (6)
#define     GPIO_PIN_7        (7)
#define     GPIO_PIN_8        (8)
#define     GPIO_PIN_9        (9)
#define     GPIO_PIN_10       (10)
#define     GPIO_PIN_11       (11)
#define     GPIO_PIN_12       (12)
#define     GPIO_PIN_13       (13)
#define     GPIO_PIN_14       (14)
#define     GPIO_PIN_15       (15)
#define     GPIO_PIN_16       (16)
#define     GPIO_PIN_17       (17)
#define     GPIO_PIN_18       (18)
#define     GPIO_PIN_19       (19)
#define     GPIO_PIN_20       (20)
#define     GPIO_PIN_21       (21)
#define     GPIO_PIN_22       (22)
#define     GPIO_PIN_23       (23)
#define     GPIO_PIN_24       (24)
#define     GPIO_PIN_25       (25)

//############################//
//                            //
//            UART            //
//                            //
//############################//

#define UART_BASE   (0X02500000)
#define UART(X)     (UART_BASE + 0x400 * (X))

#define UART0       UART(0)
#define UART1_BASE  UART(1)
#define UART2_BASE  UART(2)
#define UART3_BASE  UART(3)
#define UART4_BASE  UART(4)
#define UART5_BASE  UART(5)

#define UART_RBR(X)            (UART(X) + 0x0000)
#define UART_THR(X)            (UART(X) + 0x0000)
#define UART_DLL(X)            (UART(X) + 0x0000)
#define UART_DLH(X)            (UART(X) + 0x0004)
#define UART_IER(X)            (UART(X) + 0x0004)
#define UART_IIR(X)            (UART(X) + 0x0008)
#define UART_FCR(X)            (UART(X) + 0x0008)
#define UART_LCR(X)            (UART(X) + 0x000C)
#define UART_MCR(X)            (UART(X) + 0x0010)
#define UART_LSR(X)            (UART(X) + 0x0014)
#define UART_MSR(X)            (UART(X) + 0x0018)
#define UART_SCH(X)            (UART(X) + 0x001C)
#define UART_USR(X)            (UART(X) + 0x007C)
#define UART_TFL(X)            (UART(X) + 0x0080)
#define UART_RFL(X)            (UART(X) + 0x0084)
#define UART_HSK(X)            (UART(X) + 0x0088)
#define UART_DMA_REQ_EN(X)     (UART(X) + 0x008C)
#define UART_HALT(X)           (UART(X) + 0x00A4)
#define UART_DBG_DLL(X)        (UART(X) + 0x00B0)
#define UART_DBG_DLH(X)        (UART(X) + 0x00B4)
#define UART_A_FCC(X)          (UART(X) + 0x00F0)
#define UART_A_RXDMA_CTRL(X)   (UART(X) + 0x0100)
#define UART_A_RXDMA_STR(X)    (UART(X) + 0x0104)
#define UART_A_RXDMA_STA(X)    (UART(X) + 0x0108)
#define UART_A_RXDMA_LMT(X)    (UART(X) + 0x010C)
#define UART_A_RXDMA_SADDRL(X) (UART(X) + 0x0110)
#define UART_A_RXDMA_SADDRH(X) (UART(X) + 0x0114)
#define UART_A_RXDMA_BL(X)     (UART(X) + 0x0118)
#define UART_A_RXDMA_IE(X)     (UART(X) + 0x0120)
#define UART_A_RXDMA_IS(X)     (UART(X) + 0x0124)
#define UART_A_RXDMA_WADDRL(X) (UART(X) + 0x0128)
#define UART_A_RXDMA_WADDRH(X) (UART(X) + 0x012C)
#define UART_A_RXDMA_RADDRL(X) (UART(X) + 0x0130)
#define UART_A_RXDMA_RADDRH(X) (UART(X) + 0x0134)
#define UART_A_RXDMA_DCNT(X)   (UART(X) + 0x0138)

// 7 FIFOERR
// RX Data Error in FIFO
// When FIFOs are disabled, this bit is always 0. When FIFOs are enabled, this bit is set to “1” when there is at least one PE, FE, or BI in the RX FIFO. It is cleared by reading from the UART_LSR register, there are no subsequent errors in the FIFO.
#define UART_LSR_7_FIFOERR    BIT(7)    /* Fifo error */
// 6 TEMT
// Transmitter Empty
// If the FIFOs are disabled, this bit is set to "1" whenever the TX Holding Register (UART_THR) and the TX Shift Register are empty. If the FIFOs are enabled, this bit is set whenever the TX FIFO and the TX Shift Register are empty. In both cases, this bit is cleared when a byte is written to the TX data channel.
#define UART_LSR_6_TEMT		  BIT(6)    /* Transmitter empty */
// 5 THRE
// TX Holding Register Empty
// If the FIFOs are disabled, this bit is set to "1" when the TX Holding Register (UART_THR) is empty and ready to accept new data and it is cleared when the CPU writes to the TX Holding Register.
//If the FIFOs are enabled, this bit is set to "1" whenever the TX FIFO is empty and it is cleared when at least one byte is written to the TX FIFO.
#define UART_LSR_5_THRE        BIT(5)    /* Transmit-hold-register empty */
// 4 BI
// Break Interrupt
// This is used to indicate the detection of a break sequence on the serial input data.
//If in UART mode (SIR_MODE == Disabled), it is set when the serial input, sir_in, is held in a logic '0' state for longer than the sum of start time + data bits + parity + stop bits.
//If in infrared mode (SIR_MODE == Enabled), it is set when the serial input, sir_in, is continuously pulsed to logic '0' for longer than the sum of start time + data bits + parity + stop bits. A break condition on serial input causes one and only one character, consisting of all zeros, to be received by the UART.
//In the FIFO mode, the character associated with the break condition is carried through the FIFO and is revealed when the character is at the top of the FIFO. Reading the UART_LSR clears the BI bit. In the non-FIFO mode, the BI indication occurs immediately and persists until the UART_LSR is read.
#define UART_LSR_4_BI          BIT(4)    /* Break interrupt indicator */
//3 FE
// Framing Error
// This is used to indicate the occurrence of a framing error in the receiver. A framing error occurs when the receiver does not detect a valid STOP bit in the received data.
// In the FIFO mode, since the framing error is associated with a character received, it is revealed when the character with the framing error is at the top of the FIFO. When a framing error occurs, the UART tries to resynchronize. It does this by assuming that the error was due to the start bit of the next character and then continues receiving the other bit i.e. data, and/or parity and stop. It should be noted that the Framing Error (FE) bit (UART_LSR[3]) is set if a break interrupt has occurred, as indicated by Break Interrupt (BI) bit (UART_LSR[4]).
// 0: no framing error 1: framing error. Reading the UART_LSR clears the FE bit.
#define UART_LSR_3_FE        BIT(3)    /* Frame error indicator */
// 2 PE
// Parity Error
// This is used to indicate the occurrence of a parity error in the receiver if the Parity Enable (PEN) bit (UART_LCR[3]) is set. In the FIFO mode, since the parity error is associated with a character received, it is revealed when the character with the parity error arrives at the top of the FIFO. It should be noted that the Parity Error (PE) bit (UART_LSR[2]) is set if a break interrupt has occurred, as indicated by Break Interrupt (BI) bit (UART_LSR[4]).
// 0: no parity error 1: parity error. Reading the UART_LSR clears the PE bit.
#define UART_LSR_2_PE		 BIT(2)    /* Parity error indicator */
// 1 OE
// Overrun Error
// This occurs if a new data character was received before the previous data was read. In the non-FIFO mode, the OE bit is set when a new character arrives in the receiver before the previous character was read from the UART_RBR. When this happens, the data in the UART_RBR is overwritten. In the FIFO mode, an overrun error occurs when the FIFO is full and a new character arrives at the receiver. The data in the FIFO is retained and the data in the receive shift register is lost.
// 0: no overrun error 1: overrun error. Reading the UART_LSR clears the OE bit.
#define UART_LSR_1_OE		 BIT(1)    /* Overrun error indicator */
// 0 DR
// Data Ready
// This is used to indicate that the receiver contains at least one character in the UART_RBR or the receiver FIFO.
// 0: no data ready 1: data ready. This bit is cleared when the UART_RBR is read in non-FIFO mode, or when the receiver FIFO is empty, in FIFO mode.
// Note: Not use when the RXDMA master is enabled (rxdma_ctrl[0] is set to 1).
#define UART_LSR_0_DR		 BIT(0)    /* Receiver data ready */



#define UART_LSR_BRK_ERROR_BITS	0x1E    /* BI, FE, PE, OE bits */

#define UART0_MODE_TX   (6)
#define UART0_MODE_RX   (6)

#endif /* __D1_H__ */
