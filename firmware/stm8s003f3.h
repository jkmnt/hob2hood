#ifndef STM8S003F3_H
#define STM8S003F3_H

#include <stdint.h>

// Memory regions

#define RAM_ADDR_START 0x000000U
#define RAM_ADDR_END 0x0003FFU

#define FLASH_ADDR_START 0x008000U
#define FLASH_ADDR_END 0x009FFFU

#define SFR1_ADDR_START 0x005000U
#define SFR1_ADDR_END 0x0057FFU

#define SFR2_ADDR_START 0x007F00U
#define SFR2_ADDR_END 0x007FFFU

#define EEPROM_ADDR_START 0x004000U
#define EEPROM_ADDR_END 0x00407FU

#define OPTION_ADDR_START 0x004800U
#define OPTION_ADDR_END 0x00480AU


// Interrupts

// addr: 0x8008, enable: None, pending: None, prio: None
#define TLI_IRQN 0

// addr: 0x800C, enable: AWU_CSR1.AWUEN, pending: AWU_CSR1.AWUF, prio: ITC_SPR1.VECT1SPR
#define AWU_IRQN 1

// addr: 0x8010, enable: CLK_CSSR.CSSDIE, pending: CLK_CSSR.CSSD, prio: ITC_SPR1.VECT2SPR
#define CLK_CSS_IRQN 2

// addr: 0x8010, enable: CLK_SWCR.SWIEN, pending: CLK_SWCR.SWIF, prio: ITC_SPR1.VECT2SPR
#define CLK_SWITCH_IRQN 2

// addr: 0x8014, enable: PA_CR2.C20, pending: PA_IDR.IDR0, prio: ITC_SPR1.VECT3SPR
#define EXTI0_IRQN 3

// addr: 0x8018, enable: PB_CR2.C20, pending: PB_IDR.IDR0, prio: ITC_SPR2.VECT4SPR
#define EXTI1_IRQN 4

// addr: 0x801C, enable: PC_CR2.C20, pending: PC_IDR.IDR0, prio: ITC_SPR2.VECT5SPR
#define EXTI2_IRQN 5

// addr: 0x8020, enable: PD_CR2.C20, pending: PD_IDR.IDR0, prio: ITC_SPR2.VECT6SPR
#define EXTI3_IRQN 6

// addr: 0x8024, enable: PE_CR2.C20, pending: PE_IDR.IDR0, prio: ITC_SPR2.VECT7SPR
#define EXTI4_IRQN 7

// addr: 0x8030, enable: SPI_ICR.ERRIE, pending: SPI_SR.CRCERR, prio: ITC_SPR3.VECT10SPR
#define SPI_CRCERR_IRQN 10

// addr: 0x8030, enable: SPI_ICR.ERRIE, pending: SPI_SR.MODF, prio: ITC_SPR3.VECT10SPR
#define SPI_MODF_IRQN 10

// addr: 0x8030, enable: SPI_ICR.ERRIE, pending: SPI_SR.OVR, prio: ITC_SPR3.VECT10SPR
#define SPI_OVR_IRQN 10

// addr: 0x8030, enable: SPI_ICR.RXIE, pending: SPI_SR.RXNE, prio: ITC_SPR3.VECT10SPR
#define SPI_RXNE_IRQN 10

// addr: 0x8030, enable: SPI_ICR.TXIE, pending: SPI_SR.TXE, prio: ITC_SPR3.VECT10SPR
#define SPI_TXE_IRQN 10

// addr: 0x8030, enable: SPI_ICR.WKIE, pending: SPI_SR.WKUP, prio: ITC_SPR3.VECT10SPR
#define SPI_WKUP_IRQN 10

// addr: 0x8034, enable: TIM1_IER.BIE, pending: TIM1_SR1.BIF, prio: ITC_SPR3.VECT11SPR
#define TIM1_CAPCOM_BIF_IRQN 11

// addr: 0x8034, enable: TIM1_IER.TIE, pending: TIM1_SR1.TIF, prio: ITC_SPR3.VECT11SPR
#define TIM1_CAPCOM_TIF_IRQN 11

// addr: 0x8034, enable: TIM1_IER.UIE, pending: TIM1_SR1.UIF, prio: ITC_SPR3.VECT11SPR
#define TIM1_OVR_UIF_IRQN 11

// addr: 0x8038, enable: TIM1_IER.CC1IE, pending: TIM1_SR1.CC1IF, prio: ITC_SPR4.VECT12SPR
#define TIM1_CAPCOM_CC1IF_IRQN 12

// addr: 0x8038, enable: TIM1_IER.CC2IE, pending: TIM1_SR1.CC2IF, prio: ITC_SPR4.VECT12SPR
#define TIM1_CAPCOM_CC2IF_IRQN 12

// addr: 0x8038, enable: TIM1_IER.CC3IE, pending: TIM1_SR1.CC3IF, prio: ITC_SPR4.VECT12SPR
#define TIM1_CAPCOM_CC3IF_IRQN 12

// addr: 0x8038, enable: TIM1_IER.CC4IE, pending: TIM1_SR1.CC4IF, prio: ITC_SPR4.VECT12SPR
#define TIM1_CAPCOM_CC4IF_IRQN 12

// addr: 0x8038, enable: TIM1_IER.COMIE, pending: TIM1_SR1.COMIF, prio: ITC_SPR4.VECT12SPR
#define TIM1_CAPCOM_COMIF_IRQN 12

// addr: 0x803C, enable: TIM2_IER.UIE, pending: TIM2_SR1.UIF, prio: ITC_SPR4.VECT13SPR
#define TIM2_OVR_UIF_IRQN 13

// addr: 0x8040, enable: TIM2_IER.CC1IE, pending: TIM2_SR1.CC1IF, prio: ITC_SPR4.VECT14SPR
#define TIM2_CAPCOM_CC1IF_IRQN 14

// addr: 0x8040, enable: TIM2_IER.CC2IE, pending: TIM2_SR1.CC2IF, prio: ITC_SPR4.VECT14SPR
#define TIM2_CAPCOM_CC2IF_IRQN 14

// addr: 0x8040, enable: TIM2_IER.CC3IE, pending: TIM2_SR1.CC3IF, prio: ITC_SPR4.VECT14SPR
#define TIM2_CAPCOM_CC3IF_IRQN 14

// addr: 0x8040, enable: TIM2_IER.TIE, pending: TIM2_SR1.TIF, prio: ITC_SPR4.VECT14SPR
#define TIM2_CAPCOM_TIF_IRQN 14

// addr: 0x804C, enable: UART1_CR2.TCIEN, pending: UART1_SR.TC, prio: ITC_SPR5.VECT17SPR
#define UART1_T_TC_IRQN 17

// addr: 0x804C, enable: UART1_CR2.TIEN, pending: UART1_SR.TXE, prio: ITC_SPR5.VECT17SPR
#define UART1_T_TXE_IRQN 17

// addr: 0x8050, enable: UART1_CR2.ILIEN, pending: UART1_SR.IDLE, prio: ITC_SPR5.VECT18SPR
#define UART1_R_IDLE_IRQN 18

// addr: 0x8050, enable: UART1_CR4.LBDIEN, pending: UART1_CR4.LBDF, prio: ITC_SPR5.VECT18SPR
#define UART1_R_LBDF_IRQN 18

// addr: 0x8050, enable: UART1_CR2.RIEN, pending: UART1_SR.OR_LHE, prio: ITC_SPR5.VECT18SPR
#define UART1_R_OR_IRQN 18

// addr: 0x8050, enable: UART1_CR1.PIEN, pending: UART1_SR.PE, prio: ITC_SPR5.VECT18SPR
#define UART1_R_PE_IRQN 18

// addr: 0x8050, enable: UART1_CR2.RIEN, pending: UART1_SR.RXNE, prio: ITC_SPR5.VECT18SPR
#define UART1_R_RXNE_IRQN 18

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR1.ADD10, prio: ITC_SPR5.VECT19SPR
#define I2C_ADD10_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR1.ADDR, prio: ITC_SPR5.VECT19SPR
#define I2C_ADDR_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR2.AF, prio: ITC_SPR5.VECT19SPR
#define I2C_AF_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR2.ARLO, prio: ITC_SPR5.VECT19SPR
#define I2C_ARLO_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR2.BERR, prio: ITC_SPR5.VECT19SPR
#define I2C_BERR_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR1.BTF, prio: ITC_SPR5.VECT19SPR
#define I2C_BTF_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR2.OVR, prio: ITC_SPR5.VECT19SPR
#define I2C_OVR_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITBUFEN, pending: I2C_SR1.RXNE, prio: ITC_SPR5.VECT19SPR
#define I2C_RXNE_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR1.SB, prio: ITC_SPR5.VECT19SPR
#define I2C_SB_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR1.STOPF, prio: ITC_SPR5.VECT19SPR
#define I2C_STOPF_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITBUFEN, pending: I2C_SR1.TXE, prio: ITC_SPR5.VECT19SPR
#define I2C_TXE_IRQN 19

// addr: 0x8054, enable: I2C_ITR.ITEVTEN, pending: I2C_SR2.WUFH, prio: ITC_SPR5.VECT19SPR
#define I2C_WUFH_IRQN 19

// addr: 0x8060, enable: ADC_CSR.AWDIE, pending: ADC_CSR.AWD, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWDG_IRQN 22

// addr: 0x8060, enable: ADC_AWCRL.AWEN0, pending: ADC_AWSRL.AWS0, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS0_IRQN 22

// addr: 0x8060, enable: ADC_AWCRL.AWEN1, pending: ADC_AWSRL.AWS1, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS1_IRQN 22

// addr: 0x8060, enable: ADC_AWCRL.AWEN2, pending: ADC_AWSRL.AWS2, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS2_IRQN 22

// addr: 0x8060, enable: ADC_AWCRL.AWEN3, pending: ADC_AWSRL.AWS3, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS3_IRQN 22

// addr: 0x8060, enable: ADC_AWCRL.AWEN4, pending: ADC_AWSRL.AWS4, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS4_IRQN 22

// addr: 0x8060, enable: ADC_AWCRL.AWEN5, pending: ADC_AWSRL.AWS5, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS5_IRQN 22

// addr: 0x8060, enable: ADC_AWCRL.AWEN6, pending: ADC_AWSRL.AWS6, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS6_IRQN 22

// addr: 0x8060, enable: ADC_AWCRL.AWEN7, pending: ADC_AWSRL.AWS7, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS7_IRQN 22

// addr: 0x8060, enable: ADC_AWCRH.AWEN8, pending: ADC_AWSRH.AWS8, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS8_IRQN 22

// addr: 0x8060, enable: ADC_AWCRH.AWEN9, pending: ADC_AWSRH.AWS9, prio: ITC_SPR6.VECT22SPR
#define ADC1_AWS9_IRQN 22

// addr: 0x8060, enable: ADC_CSR.EOCIE, pending: ADC_CSR.EOC, prio: ITC_SPR6.VECT22SPR
#define ADC1_EOC_IRQN 22

// addr: 0x8064, enable: TIM4_IER.UIE, pending: TIM4_SR.UIF, prio: ITC_SPR6.VECT23SPR
#define TIM4_OVR_UIF_IRQN 23

// addr: 0x8068, enable: FLASH_CR1.IE, pending: FLASH_IAPSR.EOP, prio: ITC_SPR6.VECT24SPR
#define FLASH_EOP_IRQN 24

// addr: 0x8068, enable: FLASH_CR1.IE, pending: FLASH_IAPSR.WR_PG_DIS, prio: ITC_SPR6.VECT24SPR
#define FLASH_WR_PG_DIS_IRQN 24


// Registers

// ADC1
typedef struct
{
    volatile uint8_t DB0RH;  // ADC data buffer registers
    volatile uint8_t DB0RL;  // ADC data buffer registers
    volatile uint8_t DB1RH;  // ADC data buffer registers
    volatile uint8_t DB1RL;  // ADC data buffer registers
    volatile uint8_t DB2RH;  // ADC data buffer registers
    volatile uint8_t DB2RL;  // ADC data buffer registers
    volatile uint8_t DB3RH;  // ADC data buffer registers
    volatile uint8_t DB3RL;  // ADC data buffer registers
    volatile uint8_t DB4RH;  // ADC data buffer registers
    volatile uint8_t DB4RL;  // ADC data buffer registers
    volatile uint8_t DB5RH;  // ADC data buffer registers
    volatile uint8_t DB5RL;  // ADC data buffer registers
    volatile uint8_t DB6RH;  // ADC data buffer registers
    volatile uint8_t DB6RL;  // ADC data buffer registers
    volatile uint8_t DB7RH;  // ADC data buffer registers
    volatile uint8_t DB7RL;  // ADC data buffer registers
    volatile uint8_t DB8RH;  // ADC data buffer registers
    volatile uint8_t DB8RL;  // ADC data buffer registers
    volatile uint8_t DB9RH;  // ADC data buffer registers
    volatile uint8_t DB9RL;  // ADC data buffer registers
    uint8_t _res0[12];
    volatile uint8_t CSR;  // ADC control/status register
    volatile uint8_t CR1;  // ADC configuration register 1
    volatile uint8_t CR2;  // ADC configuration register 2
    volatile uint8_t CR3;  // ADC configuration register 3
    volatile uint8_t DRH;  // ADC data register high
    volatile uint8_t DRL;  // ADC data register low
    volatile uint8_t TDRH;  // ADC Schmitt trigger disable register high
    volatile uint8_t TDRL;  // ADC Schmitt trigger disable register low
    volatile uint8_t HTRH;  // ADC high threshold register high
    volatile uint8_t HTRL;  // ADC high threshold register low
    volatile uint8_t LTRH;  // ADC low threshold register high
    volatile uint8_t LTRL;  // ADC low threshold register low
    volatile uint8_t AWSRH;  // ADC analog watchdog status register high
    volatile uint8_t AWSRL;  // ADC analog watchdog status register low
    volatile uint8_t AWCRH;  // ADC analog watchdog control register high
    volatile uint8_t AWCRL;  // ADC analog watchdog control register low
} ADC1_t;


#define ADC1_CSR_AWDIE (1U << 4)
#define ADC1_CSR_EOCIE (1U << 5)
#define ADC1_CSR_AWD (1U << 6)
#define ADC1_CSR_EOC (1U << 7)

#define ADC1_CR1_ADON (1U << 0)
#define ADC1_CR1_CONT (1U << 1)

#define ADC1_CR2_SCAN (1U << 1)
#define ADC1_CR2_ALIGN (1U << 3)
#define ADC1_CR2_EXTTRIG (1U << 6)

#define ADC1_CR3_OVR (1U << 6)
#define ADC1_CR3_DBUF (1U << 7)

#define ADC1_AWSRH_AWS8 (1U << 0)
#define ADC1_AWSRH_AWS9 (1U << 1)

#define ADC1_AWSRL_AWS0 (1U << 0)
#define ADC1_AWSRL_AWS1 (1U << 1)
#define ADC1_AWSRL_AWS2 (1U << 2)
#define ADC1_AWSRL_AWS3 (1U << 3)
#define ADC1_AWSRL_AWS4 (1U << 4)
#define ADC1_AWSRL_AWS5 (1U << 5)
#define ADC1_AWSRL_AWS6 (1U << 6)
#define ADC1_AWSRL_AWS7 (1U << 7)

#define ADC1_AWCRH_AWEN8 (1U << 0)
#define ADC1_AWCRH_AWEN9 (1U << 1)

#define ADC1_AWCRL_AWEN0 (1U << 0)
#define ADC1_AWCRL_AWEN1 (1U << 1)
#define ADC1_AWCRL_AWEN2 (1U << 2)
#define ADC1_AWCRL_AWEN3 (1U << 3)
#define ADC1_AWCRL_AWEN4 (1U << 4)
#define ADC1_AWCRL_AWEN5 (1U << 5)
#define ADC1_AWCRL_AWEN6 (1U << 6)
#define ADC1_AWCRL_AWEN7 (1U << 7)

#define ADC1 ((ADC1_t *)0x53E0)


// AWU
typedef struct
{
    volatile uint8_t CSR1;  // AWU control/status register 1
    volatile uint8_t APR;  // AWU asynchronous prescaler buffer register
    volatile uint8_t TBR;  // AWU timebase selection register
} AWU_t;


#define AWU_CSR1_MSR (1U << 0)
#define AWU_CSR1_AWUEN (1U << 4)
#define AWU_CSR1_AWUF (1U << 5)

#define AWU ((AWU_t *)0x50F0)


// BEEP
typedef struct
{
    volatile uint8_t CSR;  // BEEP control/status register
} BEEP_t;


#define BEEP_CSR_BEEPEN (1U << 5)

#define BEEP ((BEEP_t *)0x50F3)


// CLK
typedef struct
{
    volatile uint8_t ICKR;  // Internal clock control register
    volatile uint8_t ECKR;  // External clock control register
    uint8_t _res0[1];
    volatile uint8_t CMSR;  // Clock master status register
    volatile uint8_t SWR;  // Clock master switch register
    volatile uint8_t SWCR;  // Clock switch control register
    volatile uint8_t CKDIVR;  // Clock divider register
    volatile uint8_t PCKENR1;  // Peripheral clock gating register 1
    volatile uint8_t CSSR;  // Clock security system register
    volatile uint8_t CCOR;  // Configurable clock control register
    volatile uint8_t PCKENR2;  // Peripheral clock gating register 2
    uint8_t _res1[1];
    volatile uint8_t HSITRIMR;  // HSI clock calibration trimming register
    volatile uint8_t SWIMCCR;  // SWIM clock control register
} CLK_t;


#define CLK_ICKR_HSIEN (1U << 0)
#define CLK_ICKR_HSIRDY (1U << 1)
#define CLK_ICKR_FHW (1U << 2)
#define CLK_ICKR_LSIEN (1U << 3)
#define CLK_ICKR_LSIRDY (1U << 4)
#define CLK_ICKR_REGAH (1U << 5)

#define CLK_ECKR_HSEEN (1U << 0)
#define CLK_ECKR_HSERDY (1U << 1)

#define CLK_SWCR_SWBSY (1U << 0)
#define CLK_SWCR_SWEN (1U << 1)
#define CLK_SWCR_SWIEN (1U << 2)
#define CLK_SWCR_SWIF (1U << 3)

#define CLK_CSSR_CSSEN (1U << 0)
#define CLK_CSSR_AUX (1U << 1)
#define CLK_CSSR_CSSDIE (1U << 2)
#define CLK_CSSR_CSSD (1U << 3)

#define CLK_CCOR_CCOEN (1U << 0)
#define CLK_CCOR_CCORDY (1U << 5)
#define CLK_CCOR_CC0BSY (1U << 6)

#define CLK_SWIMCCR_SWIMCLK (1U << 0)

#define CLK ((CLK_t *)0x50C0)


// CPU
typedef struct
{
    volatile uint8_t A;  // Accumulator
    volatile uint8_t PCE;  // Program counter extended
    volatile uint8_t PCH;  // Program counter high
    volatile uint8_t PCL;  // Program counter low
    volatile uint8_t XH;  // X index register high
    volatile uint8_t XL;  // X index register low
    volatile uint8_t YH;  // Y index register high
    volatile uint8_t YL;  // Y index register low
    volatile uint8_t SPH;  // Stack pointer high
    volatile uint8_t SPL;  // Stack pointer low
    volatile uint8_t CCR;  // Condition code register
    uint8_t _res0[85];
    volatile uint8_t CFG_GCR;  // Global configuration register
} CPU_t;


#define CPU_CCR_C (1U << 0)
#define CPU_CCR_Z (1U << 1)
#define CPU_CCR_NF (1U << 2)
#define CPU_CCR_I0 (1U << 3)
#define CPU_CCR_H (1U << 4)
#define CPU_CCR_I1 (1U << 5)
#define CPU_CCR_V (1U << 7)

#define CPU_CFG_GCR_SWO (1U << 0)
#define CPU_CFG_GCR_AL (1U << 1)

#define CPU ((CPU_t *)0x7F00)


// DM
typedef struct
{
    volatile uint8_t BK1RE;  // DM breakpoint 1 register extended byte
    volatile uint8_t BK1RH;  // DM breakpoint 1 register high byte
    volatile uint8_t BK1RL;  // DM breakpoint 1 register low byte
    volatile uint8_t BK2RE;  // DM breakpoint 2 register extended byte
    volatile uint8_t BK2RH;  // DM breakpoint 2 register high byte
    volatile uint8_t BK2RL;  // DM breakpoint 2 register low byte
    volatile uint8_t CR1;  // DM debug module control register 1
    volatile uint8_t CR2;  // DM debug module control register 2
    volatile uint8_t CSR1;  // DM debug module control/status register 1
    volatile uint8_t CSR2;  // DM debug module control/status register 2
    volatile uint8_t ENFCTR;  // DM enable function register
} DM_t;



#define DM ((DM_t *)0x7F90)


// FLASH
typedef struct
{
    volatile uint8_t CR1;  // Flash control register 1
    volatile uint8_t CR2;  // Flash control register 2
    volatile uint8_t NCR2;  // Flash complementary control register 2
    volatile uint8_t FPR;  // Flash protection register
    volatile uint8_t NFPR;  // Flash complementary protection register
    volatile uint8_t IAPSR;  // Flash in-application programming status register
    uint8_t _res0[2];
    volatile uint8_t PUKR;  // Flash program memory unprotection register
    uint8_t _res1[1];
    volatile uint8_t DUKR;  // Data EEPROM unprotection register
} FLASH_t;


#define FLASH_CR1_FIX (1U << 0)
#define FLASH_CR1_IE (1U << 1)
#define FLASH_CR1_AHALT (1U << 2)
#define FLASH_CR1_HALT (1U << 3)

#define FLASH_CR2_PRG (1U << 0)
#define FLASH_CR2_FPRG (1U << 4)
#define FLASH_CR2_ERASE (1U << 5)
#define FLASH_CR2_WPRG (1U << 6)
#define FLASH_CR2_OPT (1U << 7)

#define FLASH_NCR2_NPRG (1U << 0)
#define FLASH_NCR2_NFPRG (1U << 4)
#define FLASH_NCR2_NERASE (1U << 5)
#define FLASH_NCR2_NWPRG (1U << 6)
#define FLASH_NCR2_NOPT (1U << 7)

#define FLASH_FPR_WPB0 (1U << 0)
#define FLASH_FPR_WPB1 (1U << 1)
#define FLASH_FPR_WPB2 (1U << 2)
#define FLASH_FPR_WPB3 (1U << 3)
#define FLASH_FPR_WPB4 (1U << 4)
#define FLASH_FPR_WPB5 (1U << 5)

#define FLASH_NFPR_NWPB0 (1U << 0)
#define FLASH_NFPR_NWPB1 (1U << 1)
#define FLASH_NFPR_NWPB2 (1U << 2)
#define FLASH_NFPR_NWPB3 (1U << 3)
#define FLASH_NFPR_NWPB4 (1U << 4)
#define FLASH_NFPR_NWPB5 (1U << 5)

#define FLASH_IAPSR_WR_PG_DIS (1U << 0)
#define FLASH_IAPSR_PUL (1U << 1)
#define FLASH_IAPSR_EOP (1U << 2)
#define FLASH_IAPSR_DUL (1U << 3)
#define FLASH_IAPSR_HVOFF (1U << 6)

#define FLASH ((FLASH_t *)0x505A)


// I2C
typedef struct
{
    volatile uint8_t CR1;  // I2C control register 1
    volatile uint8_t CR2;  // I2C control register 2
    volatile uint8_t FREQR;  // I2C frequency register
    volatile uint8_t OARL;  // I2C Own address register low
    volatile uint8_t OARH;  // I2C Own address register high
    uint8_t _res0[1];
    volatile uint8_t DR;  // I2C data register
    volatile uint8_t SR1;  // I2C status register 1
    volatile uint8_t SR2;  // I2C status register 2
    volatile uint8_t SR3;  // I2C status register 3
    volatile uint8_t ITR;  // I2C interrupt control register
    volatile uint8_t CCRL;  // I2C Clock control register low
    volatile uint8_t CCRH;  // I2C Clock control register high
    volatile uint8_t TRISER;  // I2C TRISE register
    volatile uint8_t PECR;  // I2C packet error checking register
} I2C_t;


#define I2C_CR1_PE (1U << 0)
#define I2C_CR1_ENGC (1U << 6)
#define I2C_CR1_NOSTRETCH (1U << 7)

#define I2C_CR2_START (1U << 0)
#define I2C_CR2_STOP (1U << 1)
#define I2C_CR2_ACK (1U << 2)
#define I2C_CR2_POS (1U << 3)
#define I2C_CR2_SWRST (1U << 7)

#define I2C_OARL_ADD0 (1U << 0)

#define I2C_OARH_ADDCONF (1U << 6)
#define I2C_OARH_ADDMODE (1U << 7)

#define I2C_SR1_SB (1U << 0)
#define I2C_SR1_ADDR (1U << 1)
#define I2C_SR1_BTF (1U << 2)
#define I2C_SR1_ADD10 (1U << 3)
#define I2C_SR1_STOPF (1U << 4)
#define I2C_SR1_RXNE (1U << 6)
#define I2C_SR1_TXE (1U << 7)

#define I2C_SR2_BERR (1U << 0)
#define I2C_SR2_ARLO (1U << 1)
#define I2C_SR2_AF (1U << 2)
#define I2C_SR2_OVR (1U << 3)
#define I2C_SR2_WUFH (1U << 5)

#define I2C_SR3_MSL (1U << 0)
#define I2C_SR3_BUSY (1U << 1)
#define I2C_SR3_TRA (1U << 2)
#define I2C_SR3_GENCALL (1U << 4)

#define I2C_ITR_ITERREN (1U << 0)
#define I2C_ITR_ITEVTEN (1U << 1)
#define I2C_ITR_ITBUFEN (1U << 2)

#define I2C_CCRH_DUTY (1U << 6)
#define I2C_CCRH_F_S (1U << 7)

#define I2C ((I2C_t *)0x5210)


// ITC
typedef struct
{
    volatile uint8_t CR1;  // External interrupt control register 1
    volatile uint8_t CR2;  // External interrupt control register 2
    uint8_t _res0[17];
    volatile uint8_t RST_SR;  // Reset status register
    uint8_t _res1[11964];
    volatile uint8_t SPR1;  // Interrupt software priority register 1
    volatile uint8_t SPR2;  // Interrupt software priority register 2
    volatile uint8_t SPR3;  // Interrupt software priority register 3
    volatile uint8_t SPR4;  // Interrupt software priority register 4
    volatile uint8_t SPR5;  // Interrupt software priority register 5
    volatile uint8_t SPR6;  // Interrupt software priority register 6
    volatile uint8_t SPR7;  // Interrupt software priority register 7
    volatile uint8_t SPR8;  // Interrupt software priority register 8
} ITC_t;


#define ITC_CR2_TLIS (1U << 2)

#define ITC_RST_SR_WWDGF (1U << 0)
#define ITC_RST_SR_IWDGF (1U << 1)
#define ITC_RST_SR_ILLOPF (1U << 2)
#define ITC_RST_SR_SWIMF (1U << 3)
#define ITC_RST_SR_EMCF (1U << 4)

#define ITC ((ITC_t *)0x50A0)


// IWDG
typedef struct
{
    volatile uint8_t KR;  // IWDG key register
    volatile uint8_t PR;  // IWDG prescaler register
    volatile uint8_t RLR;  // IWDG reload register
} IWDG_t;



#define IWDG ((IWDG_t *)0x50E0)


// OPT
typedef struct
{
    volatile uint8_t OPT0;  // Read-out protection (ROP)
    volatile uint8_t OPT1;  // User boot code (UBC)
    volatile uint8_t NOPT1;  // User boot code (UBC) (complementary byte)
    volatile uint8_t OPT2;  // Alternate function remapping (AFR)
    volatile uint8_t NOPT2;  // Alternate function remapping (AFR) (complementary byte)
    volatile uint8_t OPT3;  // Misc. option
    volatile uint8_t NOPT3;  // Misc. option (complementary byte)
    volatile uint8_t OPT4;  // Clock option
    volatile uint8_t NOPT4;  // Clock option (complementary byte)
    volatile uint8_t OPT5;  // HSE clock startup
    volatile uint8_t NOPT5;  // HSE clock startup (complementary byte)
} OPT_t;



#define OPT ((OPT_t *)0x4800)


// PORTA
typedef struct
{
    volatile uint8_t ODR;  // Port A data output latch register
    volatile uint8_t IDR;  // Port A input pin value register
    volatile uint8_t DDR;  // Port A data direction register
    volatile uint8_t CR1;  // Port A control register 1
    volatile uint8_t CR2;  // Port A control register 2
} PORTA_t;


#define PORTA_ODR_ODR0 (1U << 0)
#define PORTA_ODR_ODR1 (1U << 1)
#define PORTA_ODR_ODR2 (1U << 2)
#define PORTA_ODR_ODR3 (1U << 3)
#define PORTA_ODR_ODR4 (1U << 4)
#define PORTA_ODR_ODR5 (1U << 5)
#define PORTA_ODR_ODR6 (1U << 6)
#define PORTA_ODR_ODR7 (1U << 7)

#define PORTA_IDR_IDR0 (1U << 0)
#define PORTA_IDR_IDR1 (1U << 1)
#define PORTA_IDR_IDR2 (1U << 2)
#define PORTA_IDR_IDR3 (1U << 3)
#define PORTA_IDR_IDR4 (1U << 4)
#define PORTA_IDR_IDR5 (1U << 5)
#define PORTA_IDR_IDR6 (1U << 6)
#define PORTA_IDR_IDR7 (1U << 7)

#define PORTA_DDR_DDR0 (1U << 0)
#define PORTA_DDR_DDR1 (1U << 1)
#define PORTA_DDR_DDR2 (1U << 2)
#define PORTA_DDR_DDR3 (1U << 3)
#define PORTA_DDR_DDR4 (1U << 4)
#define PORTA_DDR_DDR5 (1U << 5)
#define PORTA_DDR_DDR6 (1U << 6)
#define PORTA_DDR_DDR7 (1U << 7)

#define PORTA_CR1_C10 (1U << 0)
#define PORTA_CR1_C11 (1U << 1)
#define PORTA_CR1_C12 (1U << 2)
#define PORTA_CR1_C13 (1U << 3)
#define PORTA_CR1_C14 (1U << 4)
#define PORTA_CR1_C15 (1U << 5)
#define PORTA_CR1_C16 (1U << 6)
#define PORTA_CR1_C17 (1U << 7)

#define PORTA_CR2_C20 (1U << 0)
#define PORTA_CR2_C21 (1U << 1)
#define PORTA_CR2_C22 (1U << 2)
#define PORTA_CR2_C23 (1U << 3)
#define PORTA_CR2_C24 (1U << 4)
#define PORTA_CR2_C25 (1U << 5)
#define PORTA_CR2_C26 (1U << 6)
#define PORTA_CR2_C27 (1U << 7)

#define PORTA ((PORTA_t *)0x5000)


// PORTB
typedef struct
{
    volatile uint8_t ODR;  // Port B data output latch register
    volatile uint8_t IDR;  // Port B input pin value register
    volatile uint8_t DDR;  // Port B data direction register
    volatile uint8_t CR1;  // Port B control register 1
    volatile uint8_t CR2;  // Port B control register 2
} PORTB_t;


#define PORTB_ODR_ODR0 (1U << 0)
#define PORTB_ODR_ODR1 (1U << 1)
#define PORTB_ODR_ODR2 (1U << 2)
#define PORTB_ODR_ODR3 (1U << 3)
#define PORTB_ODR_ODR4 (1U << 4)
#define PORTB_ODR_ODR5 (1U << 5)
#define PORTB_ODR_ODR6 (1U << 6)
#define PORTB_ODR_ODR7 (1U << 7)

#define PORTB_IDR_IDR0 (1U << 0)
#define PORTB_IDR_IDR1 (1U << 1)
#define PORTB_IDR_IDR2 (1U << 2)
#define PORTB_IDR_IDR3 (1U << 3)
#define PORTB_IDR_IDR4 (1U << 4)
#define PORTB_IDR_IDR5 (1U << 5)
#define PORTB_IDR_IDR6 (1U << 6)
#define PORTB_IDR_IDR7 (1U << 7)

#define PORTB_DDR_DDR0 (1U << 0)
#define PORTB_DDR_DDR1 (1U << 1)
#define PORTB_DDR_DDR2 (1U << 2)
#define PORTB_DDR_DDR3 (1U << 3)
#define PORTB_DDR_DDR4 (1U << 4)
#define PORTB_DDR_DDR5 (1U << 5)
#define PORTB_DDR_DDR6 (1U << 6)
#define PORTB_DDR_DDR7 (1U << 7)

#define PORTB_CR1_C10 (1U << 0)
#define PORTB_CR1_C11 (1U << 1)
#define PORTB_CR1_C12 (1U << 2)
#define PORTB_CR1_C13 (1U << 3)
#define PORTB_CR1_C14 (1U << 4)
#define PORTB_CR1_C15 (1U << 5)
#define PORTB_CR1_C16 (1U << 6)
#define PORTB_CR1_C17 (1U << 7)

#define PORTB_CR2_C20 (1U << 0)
#define PORTB_CR2_C21 (1U << 1)
#define PORTB_CR2_C22 (1U << 2)
#define PORTB_CR2_C23 (1U << 3)
#define PORTB_CR2_C24 (1U << 4)
#define PORTB_CR2_C25 (1U << 5)
#define PORTB_CR2_C26 (1U << 6)
#define PORTB_CR2_C27 (1U << 7)

#define PORTB ((PORTB_t *)0x5005)


// PORTC
typedef struct
{
    volatile uint8_t ODR;  // Port C data output latch register
    volatile uint8_t IDR;  // Port C input pin value register
    volatile uint8_t DDR;  // Port C data direction register
    volatile uint8_t CR1;  // Port C control register 1
    volatile uint8_t CR2;  // Port C control register 2
} PORTC_t;


#define PORTC_ODR_ODR0 (1U << 0)
#define PORTC_ODR_ODR1 (1U << 1)
#define PORTC_ODR_ODR2 (1U << 2)
#define PORTC_ODR_ODR3 (1U << 3)
#define PORTC_ODR_ODR4 (1U << 4)
#define PORTC_ODR_ODR5 (1U << 5)
#define PORTC_ODR_ODR6 (1U << 6)
#define PORTC_ODR_ODR7 (1U << 7)

#define PORTC_IDR_IDR0 (1U << 0)
#define PORTC_IDR_IDR1 (1U << 1)
#define PORTC_IDR_IDR2 (1U << 2)
#define PORTC_IDR_IDR3 (1U << 3)
#define PORTC_IDR_IDR4 (1U << 4)
#define PORTC_IDR_IDR5 (1U << 5)
#define PORTC_IDR_IDR6 (1U << 6)
#define PORTC_IDR_IDR7 (1U << 7)

#define PORTC_DDR_DDR0 (1U << 0)
#define PORTC_DDR_DDR1 (1U << 1)
#define PORTC_DDR_DDR2 (1U << 2)
#define PORTC_DDR_DDR3 (1U << 3)
#define PORTC_DDR_DDR4 (1U << 4)
#define PORTC_DDR_DDR5 (1U << 5)
#define PORTC_DDR_DDR6 (1U << 6)
#define PORTC_DDR_DDR7 (1U << 7)

#define PORTC_CR1_C10 (1U << 0)
#define PORTC_CR1_C11 (1U << 1)
#define PORTC_CR1_C12 (1U << 2)
#define PORTC_CR1_C13 (1U << 3)
#define PORTC_CR1_C14 (1U << 4)
#define PORTC_CR1_C15 (1U << 5)
#define PORTC_CR1_C16 (1U << 6)
#define PORTC_CR1_C17 (1U << 7)

#define PORTC_CR2_C20 (1U << 0)
#define PORTC_CR2_C21 (1U << 1)
#define PORTC_CR2_C22 (1U << 2)
#define PORTC_CR2_C23 (1U << 3)
#define PORTC_CR2_C24 (1U << 4)
#define PORTC_CR2_C25 (1U << 5)
#define PORTC_CR2_C26 (1U << 6)
#define PORTC_CR2_C27 (1U << 7)

#define PORTC ((PORTC_t *)0x500A)


// PORTD
typedef struct
{
    volatile uint8_t ODR;  // Port D data output latch register
    volatile uint8_t IDR;  // Port D input pin value register
    volatile uint8_t DDR;  // Port D data direction register
    volatile uint8_t CR1;  // Port D control register 1
    volatile uint8_t CR2;  // Port D control register 2
} PORTD_t;


#define PORTD_ODR_ODR0 (1U << 0)
#define PORTD_ODR_ODR1 (1U << 1)
#define PORTD_ODR_ODR2 (1U << 2)
#define PORTD_ODR_ODR3 (1U << 3)
#define PORTD_ODR_ODR4 (1U << 4)
#define PORTD_ODR_ODR5 (1U << 5)
#define PORTD_ODR_ODR6 (1U << 6)
#define PORTD_ODR_ODR7 (1U << 7)

#define PORTD_IDR_IDR0 (1U << 0)
#define PORTD_IDR_IDR1 (1U << 1)
#define PORTD_IDR_IDR2 (1U << 2)
#define PORTD_IDR_IDR3 (1U << 3)
#define PORTD_IDR_IDR4 (1U << 4)
#define PORTD_IDR_IDR5 (1U << 5)
#define PORTD_IDR_IDR6 (1U << 6)
#define PORTD_IDR_IDR7 (1U << 7)

#define PORTD_DDR_DDR0 (1U << 0)
#define PORTD_DDR_DDR1 (1U << 1)
#define PORTD_DDR_DDR2 (1U << 2)
#define PORTD_DDR_DDR3 (1U << 3)
#define PORTD_DDR_DDR4 (1U << 4)
#define PORTD_DDR_DDR5 (1U << 5)
#define PORTD_DDR_DDR6 (1U << 6)
#define PORTD_DDR_DDR7 (1U << 7)

#define PORTD_CR1_C10 (1U << 0)
#define PORTD_CR1_C11 (1U << 1)
#define PORTD_CR1_C12 (1U << 2)
#define PORTD_CR1_C13 (1U << 3)
#define PORTD_CR1_C14 (1U << 4)
#define PORTD_CR1_C15 (1U << 5)
#define PORTD_CR1_C16 (1U << 6)
#define PORTD_CR1_C17 (1U << 7)

#define PORTD_CR2_C20 (1U << 0)
#define PORTD_CR2_C21 (1U << 1)
#define PORTD_CR2_C22 (1U << 2)
#define PORTD_CR2_C23 (1U << 3)
#define PORTD_CR2_C24 (1U << 4)
#define PORTD_CR2_C25 (1U << 5)
#define PORTD_CR2_C26 (1U << 6)
#define PORTD_CR2_C27 (1U << 7)

#define PORTD ((PORTD_t *)0x500F)


// PORTE
typedef struct
{
    volatile uint8_t ODR;  // Port E data output latch register
    volatile uint8_t IDR;  // Port E input pin value register
    volatile uint8_t DDR;  // Port E data direction register
    volatile uint8_t CR1;  // Port E control register 1
    volatile uint8_t CR2;  // Port E control register 2
} PORTE_t;


#define PORTE_ODR_ODR0 (1U << 0)
#define PORTE_ODR_ODR1 (1U << 1)
#define PORTE_ODR_ODR2 (1U << 2)
#define PORTE_ODR_ODR3 (1U << 3)
#define PORTE_ODR_ODR4 (1U << 4)
#define PORTE_ODR_ODR5 (1U << 5)
#define PORTE_ODR_ODR6 (1U << 6)
#define PORTE_ODR_ODR7 (1U << 7)

#define PORTE_IDR_IDR0 (1U << 0)
#define PORTE_IDR_IDR1 (1U << 1)
#define PORTE_IDR_IDR2 (1U << 2)
#define PORTE_IDR_IDR3 (1U << 3)
#define PORTE_IDR_IDR4 (1U << 4)
#define PORTE_IDR_IDR5 (1U << 5)
#define PORTE_IDR_IDR6 (1U << 6)
#define PORTE_IDR_IDR7 (1U << 7)

#define PORTE_DDR_DDR0 (1U << 0)
#define PORTE_DDR_DDR1 (1U << 1)
#define PORTE_DDR_DDR2 (1U << 2)
#define PORTE_DDR_DDR3 (1U << 3)
#define PORTE_DDR_DDR4 (1U << 4)
#define PORTE_DDR_DDR5 (1U << 5)
#define PORTE_DDR_DDR6 (1U << 6)
#define PORTE_DDR_DDR7 (1U << 7)

#define PORTE_CR1_C10 (1U << 0)
#define PORTE_CR1_C11 (1U << 1)
#define PORTE_CR1_C12 (1U << 2)
#define PORTE_CR1_C13 (1U << 3)
#define PORTE_CR1_C14 (1U << 4)
#define PORTE_CR1_C15 (1U << 5)
#define PORTE_CR1_C16 (1U << 6)
#define PORTE_CR1_C17 (1U << 7)

#define PORTE_CR2_C20 (1U << 0)
#define PORTE_CR2_C21 (1U << 1)
#define PORTE_CR2_C22 (1U << 2)
#define PORTE_CR2_C23 (1U << 3)
#define PORTE_CR2_C24 (1U << 4)
#define PORTE_CR2_C25 (1U << 5)
#define PORTE_CR2_C26 (1U << 6)
#define PORTE_CR2_C27 (1U << 7)

#define PORTE ((PORTE_t *)0x5014)


// PORTF
typedef struct
{
    volatile uint8_t ODR;  // Port F data output latch register
    volatile uint8_t IDR;  // Port F input pin value register
    volatile uint8_t DDR;  // Port F data direction register
    volatile uint8_t CR1;  // Port F control register 1
    volatile uint8_t CR2;  // Port F control register 2
} PORTF_t;


#define PORTF_ODR_ODR0 (1U << 0)
#define PORTF_ODR_ODR1 (1U << 1)
#define PORTF_ODR_ODR2 (1U << 2)
#define PORTF_ODR_ODR3 (1U << 3)
#define PORTF_ODR_ODR4 (1U << 4)
#define PORTF_ODR_ODR5 (1U << 5)
#define PORTF_ODR_ODR6 (1U << 6)
#define PORTF_ODR_ODR7 (1U << 7)

#define PORTF_IDR_IDR0 (1U << 0)
#define PORTF_IDR_IDR1 (1U << 1)
#define PORTF_IDR_IDR2 (1U << 2)
#define PORTF_IDR_IDR3 (1U << 3)
#define PORTF_IDR_IDR4 (1U << 4)
#define PORTF_IDR_IDR5 (1U << 5)
#define PORTF_IDR_IDR6 (1U << 6)
#define PORTF_IDR_IDR7 (1U << 7)

#define PORTF_DDR_DDR0 (1U << 0)
#define PORTF_DDR_DDR1 (1U << 1)
#define PORTF_DDR_DDR2 (1U << 2)
#define PORTF_DDR_DDR3 (1U << 3)
#define PORTF_DDR_DDR4 (1U << 4)
#define PORTF_DDR_DDR5 (1U << 5)
#define PORTF_DDR_DDR6 (1U << 6)
#define PORTF_DDR_DDR7 (1U << 7)

#define PORTF_CR1_C10 (1U << 0)
#define PORTF_CR1_C11 (1U << 1)
#define PORTF_CR1_C12 (1U << 2)
#define PORTF_CR1_C13 (1U << 3)
#define PORTF_CR1_C14 (1U << 4)
#define PORTF_CR1_C15 (1U << 5)
#define PORTF_CR1_C16 (1U << 6)
#define PORTF_CR1_C17 (1U << 7)

#define PORTF_CR2_C20 (1U << 0)
#define PORTF_CR2_C21 (1U << 1)
#define PORTF_CR2_C22 (1U << 2)
#define PORTF_CR2_C23 (1U << 3)
#define PORTF_CR2_C24 (1U << 4)
#define PORTF_CR2_C25 (1U << 5)
#define PORTF_CR2_C26 (1U << 6)
#define PORTF_CR2_C27 (1U << 7)

#define PORTF ((PORTF_t *)0x5019)


// SPI
typedef struct
{
    volatile uint8_t CR1;  // SPI control register 1
    volatile uint8_t CR2;  // SPI control register 2
    volatile uint8_t ICR;  // SPI interrupt control register
    volatile uint8_t SR;  // SPI status register
    volatile uint8_t DR;  // SPI data register
    volatile uint8_t CRCPR;  // SPI CRC polynomial register
    volatile uint8_t RXCRCR;  // SPI Rx CRC register
    volatile uint8_t TXCRCR;  // SPI Tx CRC register
} SPI_t;


#define SPI_CR1_CPHA (1U << 0)
#define SPI_CR1_CPOL (1U << 1)
#define SPI_CR1_MSTR (1U << 2)
#define SPI_CR1_SPE (1U << 6)
#define SPI_CR1_LSBFIRST (1U << 7)

#define SPI_CR2_SSI (1U << 0)
#define SPI_CR2_SSM (1U << 1)
#define SPI_CR2_RXONLY (1U << 2)
#define SPI_CR2_CRCNEXT (1U << 4)
#define SPI_CR2_CECEN (1U << 5)
#define SPI_CR2_BDOE (1U << 6)
#define SPI_CR2_BDM (1U << 7)

#define SPI_ICR_WKIE (1U << 4)
#define SPI_ICR_ERRIE (1U << 5)
#define SPI_ICR_RXIE (1U << 6)
#define SPI_ICR_TXIE (1U << 7)

#define SPI_SR_RXNE (1U << 0)
#define SPI_SR_TXE (1U << 1)
#define SPI_SR_WKUP (1U << 3)
#define SPI_SR_CRCERR (1U << 4)
#define SPI_SR_MODF (1U << 5)
#define SPI_SR_OVR (1U << 6)
#define SPI_SR_BSY (1U << 7)

#define SPI ((SPI_t *)0x5200)


// SWIM
typedef struct
{
    volatile uint8_t CSR;  // SWIM control status register
} SWIM_t;



#define SWIM ((SWIM_t *)0x7F80)


// TIM1
typedef struct
{
    volatile uint8_t CR1;  // TIM1 control register 1
    volatile uint8_t CR2;  // TIM1 control register 2
    volatile uint8_t SMCR;  // TIM1 slave mode control register
    volatile uint8_t ETR;  // TIM1 external trigger register
    volatile uint8_t IER;  // TIM1 interrupt enable register
    volatile uint8_t SR1;  // TIM1 status register 1
    volatile uint8_t SR2;  // TIM1 status register 2
    volatile uint8_t EGR;  // TIM1 event generation register
    volatile uint8_t CCMR1;  // TIM1 capture/compare mode register 1
    volatile uint8_t CCMR2;  // TIM1 capture/compare mode register 2
    volatile uint8_t CCMR3;  // TIM1 capture/compare mode register 3
    volatile uint8_t CCMR4;  // TIM1 capture/compare mode register 4
    volatile uint8_t CCER1;  // TIM1 capture/compare enable register 1
    volatile uint8_t CCER2;  // TIM1 capture/compare enable register 2
    volatile uint8_t CNTRH;  // TIM1 counter high
    volatile uint8_t CNTRL;  // TIM1 counter low
    volatile uint8_t PSCRH;  // TIM1 prescaler register high
    volatile uint8_t PSCRL;  // TIM1 prescaler register low
    volatile uint8_t ARRH;  // TIM1 auto-reload register high
    volatile uint8_t ARRL;  // TIM1 auto-reload register low
    volatile uint8_t RCR;  // TIM1 repetition counter register
    volatile uint8_t CCR1H;  // TIM1 capture/compare register 1 high
    volatile uint8_t CCR1L;  // TIM1 capture/compare register 1 low
    volatile uint8_t CCR2H;  // TIM1 capture/compare register 2 high
    volatile uint8_t CCR2L;  // TIM1 capture/compare register 2 low
    volatile uint8_t CCR3H;  // TIM1 capture/compare register 3 high
    volatile uint8_t CCR3L;  // TIM1 capture/compare register 3 low
    volatile uint8_t CCR4H;  // TIM1 capture/compare register 4 high
    volatile uint8_t CCR4L;  // TIM1 capture/compare register 4 low
    volatile uint8_t BKR;  // TIM1 break register
    volatile uint8_t DTR;  // TIM1 dead-time register
    volatile uint8_t OISR;  // TIM1 output idle state register
} TIM1_t;


#define TIM1_CR1_CEN (1U << 0)
#define TIM1_CR1_UDIS (1U << 1)
#define TIM1_CR1_URS (1U << 2)
#define TIM1_CR1_OPM (1U << 3)
#define TIM1_CR1_DIR (1U << 4)
#define TIM1_CR1_ARPE (1U << 7)

#define TIM1_CR2_CCPG (1U << 0)
#define TIM1_CR2_COMS (1U << 2)

#define TIM1_SMCR_MSM (1U << 7)

#define TIM1_ETR_ECE (1U << 6)
#define TIM1_ETR_ETP (1U << 7)

#define TIM1_IER_UIE (1U << 0)
#define TIM1_IER_CC1IE (1U << 1)
#define TIM1_IER_CC2IE (1U << 2)
#define TIM1_IER_CC3IE (1U << 3)
#define TIM1_IER_CC4IE (1U << 4)
#define TIM1_IER_COMIE (1U << 5)
#define TIM1_IER_TIE (1U << 6)
#define TIM1_IER_BIE (1U << 7)

#define TIM1_SR1_UIF (1U << 0)
#define TIM1_SR1_CC1IF (1U << 1)
#define TIM1_SR1_CC2IF (1U << 2)
#define TIM1_SR1_CC3IF (1U << 3)
#define TIM1_SR1_CC4IF (1U << 4)
#define TIM1_SR1_COMIF (1U << 5)
#define TIM1_SR1_TIF (1U << 6)
#define TIM1_SR1_BIF (1U << 7)

#define TIM1_SR2_CC1OF (1U << 1)
#define TIM1_SR2_CC2OF (1U << 2)
#define TIM1_SR2_CC3OF (1U << 3)
#define TIM1_SR2_CC4OF (1U << 4)

#define TIM1_EGR_UG (1U << 0)
#define TIM1_EGR_CC1G (1U << 1)
#define TIM1_EGR_CC2G (1U << 2)
#define TIM1_EGR_CC3G (1U << 3)
#define TIM1_EGR_CC4G (1U << 4)
#define TIM1_EGR_COMG (1U << 5)
#define TIM1_EGR_TG (1U << 6)
#define TIM1_EGR_BG (1U << 7)

#define TIM1_CCMR1_OC1FE (1U << 2)
#define TIM1_CCMR1_OC1PE (1U << 3)
#define TIM1_CCMR1_OC1CE (1U << 7)

#define TIM1_CCMR2_OC2FE (1U << 2)
#define TIM1_CCMR2_OC2PE (1U << 3)
#define TIM1_CCMR2_OC2CE (1U << 7)

#define TIM1_CCMR3_OC3FE (1U << 2)
#define TIM1_CCMR3_OC3PE (1U << 3)
#define TIM1_CCMR3_OC3CE (1U << 7)

#define TIM1_CCMR4_OC4FE (1U << 2)
#define TIM1_CCMR4_OC4PE (1U << 3)
#define TIM1_CCMR4_OC4CE (1U << 7)

#define TIM1_CCER1_CC1E (1U << 0)
#define TIM1_CCER1_CC1P (1U << 1)
#define TIM1_CCER1_CC1NE (1U << 2)
#define TIM1_CCER1_CC1NP (1U << 3)
#define TIM1_CCER1_CC2E (1U << 4)
#define TIM1_CCER1_CC2P (1U << 5)
#define TIM1_CCER1_CC2NE (1U << 6)
#define TIM1_CCER1_CC2NP (1U << 7)

#define TIM1_CCER2_CC3E (1U << 0)
#define TIM1_CCER2_CC3P (1U << 1)
#define TIM1_CCER2_CC3NE (1U << 2)
#define TIM1_CCER2_CC3NP (1U << 3)
#define TIM1_CCER2_CC4E (1U << 4)
#define TIM1_CCER2_CC4P (1U << 5)

#define TIM1_BKR_OSSI (1U << 2)
#define TIM1_BKR_OSSR (1U << 3)
#define TIM1_BKR_BKE (1U << 4)
#define TIM1_BKR_BKP (1U << 5)
#define TIM1_BKR_AOE (1U << 6)
#define TIM1_BKR_MOE (1U << 7)

#define TIM1_OISR_OIS1 (1U << 0)
#define TIM1_OISR_OIS1N (1U << 1)
#define TIM1_OISR_OIS2 (1U << 2)
#define TIM1_OISR_OIS2N (1U << 3)
#define TIM1_OISR_OIS3 (1U << 4)
#define TIM1_OISR_OIS3N (1U << 5)
#define TIM1_OISR_OIS4 (1U << 6)

#define TIM1 ((TIM1_t *)0x5250)


// TIM2
typedef struct
{
    volatile uint8_t CR1;  // TIM2 control register 1
    uint8_t _res0[2];
    volatile uint8_t IER;  // TIM2 Interrupt enable register
    volatile uint8_t SR1;  // TIM2 status register 1
    volatile uint8_t SR2;  // TIM2 status register 2
    volatile uint8_t EGR;  // TIM2 event generation register
    volatile uint8_t CCMR1;  // TIM2 capture/compare mode register 1
    volatile uint8_t CCMR2;  // TIM2 capture/compare mode register 2
    volatile uint8_t CCMR3;  // TIM2 capture/compare mode register 3
    volatile uint8_t CCER1;  // TIM2 capture/compare enable register 1
    volatile uint8_t CCER2;  // TIM2 capture/compare enable register 2
    volatile uint8_t CNTRH;  // TIM2 counter high
    volatile uint8_t CNTRL;  // TIM2 counter low
    volatile uint8_t PSCR;  // TIM2 prescaler register
    volatile uint8_t ARRH;  // TIM2 auto-reload register high
    volatile uint8_t ARRL;  // TIM2 auto-reload register low
    volatile uint8_t CCR1H;  // TIM2 capture/compare register 1 high
    volatile uint8_t CCR1L;  // TIM2 capture/compare register 1 low
    volatile uint8_t CCR2H;  // TIM2 capture/compare reg
    volatile uint8_t CCR2L;  // TIM2 capture/compare register 2 low
    volatile uint8_t CCR3H;  // TIM2 capture/compare register 3 high
    volatile uint8_t CCR3L;  // TIM2 capture/compare register 3 low
} TIM2_t;


#define TIM2_CR1_CEN (1U << 0)
#define TIM2_CR1_UDIS (1U << 1)
#define TIM2_CR1_URS (1U << 2)
#define TIM2_CR1_OPM (1U << 3)
#define TIM2_CR1_ARPE (1U << 7)

#define TIM2_IER_UIE (1U << 0)
#define TIM2_IER_CC1IE (1U << 1)
#define TIM2_IER_CC2IE (1U << 2)
#define TIM2_IER_CC3IE (1U << 3)
#define TIM2_IER_TIE (1U << 6)

#define TIM2_SR1_UIF (1U << 0)
#define TIM2_SR1_CC1IF (1U << 1)
#define TIM2_SR1_CC2IF (1U << 2)
#define TIM2_SR1_CC3IF (1U << 3)
#define TIM2_SR1_TIF (1U << 6)

#define TIM2_SR2_CC1OF (1U << 1)
#define TIM2_SR2_CC2OF (1U << 2)
#define TIM2_SR2_CC3OF (1U << 3)

#define TIM2_EGR_UG (1U << 0)
#define TIM2_EGR_CC1G (1U << 1)
#define TIM2_EGR_CC2G (1U << 2)
#define TIM2_EGR_CC3G (1U << 3)
#define TIM2_EGR_TG (1U << 6)

#define TIM2_CCMR1_OC1PE (1U << 3)

#define TIM2_CCMR2_OC2PE (1U << 3)

#define TIM2_CCMR3_OC3PE (1U << 3)

#define TIM2_CCER1_CC1E (1U << 0)
#define TIM2_CCER1_CC1P (1U << 1)
#define TIM2_CCER1_CC2E (1U << 4)
#define TIM2_CCER1_CC2P (1U << 5)

#define TIM2_CCER2_CC3E (1U << 0)
#define TIM2_CCER2_CC3P (1U << 1)

#define TIM2 ((TIM2_t *)0x5300)


// TIM4
typedef struct
{
    volatile uint8_t CR1;  // TIM4 control register 1
    uint8_t _res0[2];
    volatile uint8_t IER;  // TIM4 interrupt enable register
    volatile uint8_t SR;  // TIM4 status register
    volatile uint8_t EGR;  // TIM4 event generation register
    volatile uint8_t CNTR;  // TIM4 counter
    volatile uint8_t PSCR;  // TIM4 prescaler register
    volatile uint8_t ARR;  // TIM4 auto-reload register
} TIM4_t;


#define TIM4_CR1_CEN (1U << 0)
#define TIM4_CR1_UDIS (1U << 1)
#define TIM4_CR1_URS (1U << 2)
#define TIM4_CR1_OPM (1U << 3)
#define TIM4_CR1_ARPE (1U << 7)

#define TIM4_IER_UIE (1U << 0)
#define TIM4_IER_TIE (1U << 6)

#define TIM4_SR_UIF (1U << 0)
#define TIM4_SR_TIF (1U << 6)

#define TIM4_EGR_UG (1U << 0)
#define TIM4_EGR_TG (1U << 6)

#define TIM4 ((TIM4_t *)0x5340)


// UART1
typedef struct
{
    volatile uint8_t SR;  // UART1 status register
    volatile uint8_t DR;  // UART1 data register
    volatile uint8_t BRR1;  // UART1 baud rate register 1
    volatile uint8_t BRR2;  // UART1 baud rate register 2
    volatile uint8_t CR1;  // UART1 control register 1
    volatile uint8_t CR2;  // UART1 control register 2
    volatile uint8_t CR3;  // UART1 control register 3
    volatile uint8_t CR4;  // UART1 control register 4
    volatile uint8_t CR5;  // UART1 control register 5
    volatile uint8_t GTR;  // UART1 guard time register
    volatile uint8_t PSCR;  // UART1 prescaler register
} UART1_t;


#define UART1_SR_PE (1U << 0)
#define UART1_SR_FE (1U << 1)
#define UART1_SR_NF (1U << 2)
#define UART1_SR_OR_LHE (1U << 3)
#define UART1_SR_IDLE (1U << 4)
#define UART1_SR_RXNE (1U << 5)
#define UART1_SR_TC (1U << 6)
#define UART1_SR_TXE (1U << 7)

#define UART1_CR1_PIEN (1U << 0)
#define UART1_CR1_PS (1U << 1)
#define UART1_CR1_PCEN (1U << 2)
#define UART1_CR1_WAKE (1U << 3)
#define UART1_CR1_M (1U << 4)
#define UART1_CR1_UART0 (1U << 5)
#define UART1_CR1_T8 (1U << 6)
#define UART1_CR1_R8 (1U << 7)

#define UART1_CR2_SBK (1U << 0)
#define UART1_CR2_RWU (1U << 1)
#define UART1_CR2_REN (1U << 2)
#define UART1_CR2_TEN (1U << 3)
#define UART1_CR2_ILIEN (1U << 4)
#define UART1_CR2_RIEN (1U << 5)
#define UART1_CR2_TCIEN (1U << 6)
#define UART1_CR2_TIEN (1U << 7)

#define UART1_CR3_LBCL (1U << 0)
#define UART1_CR3_CPHA (1U << 1)
#define UART1_CR3_CPOL (1U << 2)
#define UART1_CR3_CKEN (1U << 3)
#define UART1_CR3_LINEN (1U << 7)

#define UART1_CR4_LBDF (1U << 4)
#define UART1_CR4_LBDL (1U << 5)
#define UART1_CR4_LBDIEN (1U << 6)

#define UART1_CR5_IREN (1U << 1)
#define UART1_CR5_IRLP (1U << 2)
#define UART1_CR5_HDSEL (1U << 3)
#define UART1_CR5_NACK (1U << 4)
#define UART1_CR5_SCEN (1U << 5)

#define UART1 ((UART1_t *)0x5230)


// WWDG
typedef struct
{
    volatile uint8_t CR;  // WWDG control register
    volatile uint8_t WR;  // WWDR window register
} WWDG_t;


#define WWDG_CR_T0 (1U << 0)
#define WWDG_CR_T1 (1U << 1)
#define WWDG_CR_T2 (1U << 2)
#define WWDG_CR_T3 (1U << 3)
#define WWDG_CR_T4 (1U << 4)
#define WWDG_CR_T5 (1U << 5)
#define WWDG_CR_T6 (1U << 6)
#define WWDG_CR_WDGA (1U << 7)

#define WWDG_WR_W0 (1U << 0)
#define WWDG_WR_W1 (1U << 1)
#define WWDG_WR_W2 (1U << 2)
#define WWDG_WR_W3 (1U << 3)
#define WWDG_WR_W4 (1U << 4)
#define WWDG_WR_W5 (1U << 5)
#define WWDG_WR_W6 (1U << 6)

#define WWDG ((WWDG_t *)0x50D1)



#endif
