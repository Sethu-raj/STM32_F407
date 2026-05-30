/*
 * stm32f407xx.h
 *
 *  Created on: May 15, 2026
 *      Author: Sethu
 *      Editing Date: 16.05.2026
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>



/* Defining Base Address of Flash and SRAM Memory*/

#define FLASH_BASEADDR        0x08000000U   //This is the Starting Address of Flash Memory
#define SRAM1_BASEADDR        0x20000000U   //This is the Starting Address of SRAM1
#define SRAM2_BASEADDR        0x20001C00U   //This is the Starting Address of SRAM2 ( SRAM1 Base_Addr + SRAM1 SIZE 112kb )
#define RAM                   0x1FFF0000U   //This is the Starting Address of RAM
#define SRAM                 SRAM1_BASEADDR

/* Defining Pheripheral Base Address of Bus Interface - APB and AHB Bus) */

#define PERIPH_BASE           0x40000000U   //This is the starting address of peripheral(Tim2)
#define APB1PERIPH_BASE       PERIPH_BASE   // Starting Address of APB1
#define APB2PERIPH_BASE       0x40010000U   // Starting Address of APB2
#define AHB1PERIPH_BASE       0x40020000U   // Starting Address of AHB1
#define AHB2PERIPH_BASE       0x50000000U   // Starting Address of AHB2

/* Pheripheral which are hanging to AHB1 */

#define GPIOA_BASEADDR        (AHB1PERIPH_BASE + 0x0000)    // Base Address of GPIOA : 0x40020000U   + OFFSET
#define GPIOB_BASEADDR        (AHB1PERIPH_BASE + 0x0400)    // Base Address of GPIOB : 0x40020000U   + OFFSET
#define GPIOC_BASEADDR        (AHB1PERIPH_BASE + 0x0800)    // Base Address of GPIOC :  0x40020000U  + OFFSET
#define GPIOD_BASEADDR        (AHB1PERIPH_BASE + 0x0C00)    // Base Address of GPIOD :  0x40020000U  + OFFSET
#define GPIOE_BASEADDR        (AHB1PERIPH_BASE + 0x1000)    // Base Address of GPIOE :  0x40020000U  + OFFSET
#define GPIOF_BASEADDR        (AHB1PERIPH_BASE + 0x1400)    // Base Address of GPIOF :  0x40020000U  + OFFSET
#define GPIOG_BASEADDR        (AHB1PERIPH_BASE + 0x1800)    // Base Address of GPIOG :  0x40020000U  + OFFSET
#define GPIOH_BASEADDR        (AHB1PERIPH_BASE + 0x1C00)    // Base Address of GPIOH :  0x40020000U  + OFFSET
#define GPIOI_BASEADDR        (AHB1PERIPH_BASE + 0x2000)    // Base Address of GPIOI :  0x40020000U  + OFFSET

#define RCC_BASEADDR         (AHB1PERIPH_BASE + 0x3800)    // Base Address of RCC :  0x40020000U  + OFFSET


/*Pheripheral which are hanging to APB1*/

#define I2C1_BASEADDR      (APB1PERIPH_BASEADDR + 0x5400)  // Base Address of I2C1 : 0x40000000U   + OFFSET
#define I2C2_BASEADDR      (APB1PERIPH_BASEADDR + 0x5800)  // Base Address of I2C2 : 0x40000000U   + OFFSET
#define I2C3_BASEADDR      (APB1PERIPH_BASEADDR + 0x5C00)  // Base Address of I2C3 : 0x40000000U   + OFFSET

#define SPI2_BASEADDR      (APB1PERIPH_BASEADDR + 0x3800)  // Base Address of SPI2 : 0x40000000U   + OFFSET
#define SPI3_BASEADDR      (APB1PERIPH_BASEADDR + 0x3C00)  // Base Address of SPI3 : 0x40000000U   + OFFSET

#define USART2_BASEADDR    (APB1PERIPH_BASEADDR + 0x4400)  // Base Address of USART2 : 0x40000000U   + OFFSET
#define USART3_BASEADDR    (APB1PERIPH_BASEADDR + 0x4800)  // Base Address of USART3 : 0x40000000U   + OFFSET
#define UART4_BASEADDR     (APB1PERIPH_BASEADDR + 0x4C00)  // Base Address of UART4  : 0x40000000U   + OFFSET
#define UART5_BASEADDR     (APB1PERIPH_BASEADDR + 0x5000)  // Base Address of UART5  : 0x40000000U   + OFFSET

/*Pheripheral which are hanging to APB2 */

#define EXTI_BASEADDR      (APB2PERIPH_BASE + 0x3C00)     // Base Address of EXTI   : 0x40010000U   + OFFSET

#define SPI1_BASEADDR      (APB2PERIPH_BASE + 0x3000)     // Base Address of SPI1   : 0x40010000U   + OFFSET

#define SYSCFG_BASEADDR    (APB2PERIPH_BASE + 0x3800)     // Base Address of SYSCFG : 0x40010000U   + OFFSET

#define USART1_BASEADDR    (APB2PERIPH_BASE + 0x1000)    // Base Address of USART1  : 0x40010000U   + OFFSET
#define USART6_BASEADDR    (APB2PERIPH_BASE + 0x1400     // Base Address of USART6  : 0x40010000U   + OFFSET


/*Defining Based Address of pherpheral registers by using structures - Gpio*/
typedef struct {
	volatile uint32_t MODER;                   // GPIO port mode register, Address offset: 0x00
	volatile uint32_t OTYPER;                  // GPIO port output type register, Address offset: 0x04
	volatile uint32_t OSPEEDR;                // GPIO port output speed register, Address offset: 0x08
	volatile uint32_t PUPDR;                  // GPIO port pull-up/pull-down reg, Address offset: 0x0C
	volatile uint32_t IDR;                    // GPIO port input data register, Address offset: 0x10
	volatile uint32_t ODR;                    // GPIO port output data register, Address offset: 0x14
	volatile uint32_t BSRR;                   // GPIO port bit set/reset register, Address offset: 0x18
	volatile uint32_t LCKR;                   // GPIO port configuration lock reg, Address offset: 0x1C
	volatile uint32_t AFR[2];                 // GPIO alternate function regs, Address offset: 0x20-0x24  && afrl & afrh so array
} GPIO_RegDef_t;
typedef struct {
    volatile uint32_t CR;                // RCC_CR: Clock Control Register, Offset: 0x00
    volatile uint32_t PLLCFGR;           // RCC_PLLCFGR: PLL Configuration Register, Offset: 0x04
    volatile uint32_t CFGR;              // RCC_CFGR: Clock Configuration Register, Offset: 0x08
    volatile uint32_t CIR;               // RCC_CIR: Clock Interrupt Register, Offset: 0x0C
    volatile uint32_t AHB1RSTR;          // RCC_AHB1RSTR: AHB1 Peripheral Reset Register, Offset: 0x10
    volatile uint32_t AHB2RSTR;          // RCC_AHB2RSTR: AHB2 Peripheral Reset Register, Offset: 0x14
    volatile uint32_t AHB3RSTR;          // RCC_AHB3RSTR: AHB3 Peripheral Reset Register, Offset: 0x18
    uint32_t RESERVED0;                  // Reserved, Offset: 0x1C
    volatile uint32_t APB1RSTR;          // RCC_APB1RSTR: APB1 Peripheral Reset Register, Offset: 0x20
    volatile uint32_t APB2RSTR;          // RCC_APB2RSTR: APB2 Peripheral Reset Register, Offset: 0x24
    uint32_t RESERVED1[2];               // Reserved, Offset: 0x28-0x2C
    volatile uint32_t AHB1ENR;           // RCC_AHB1ENR: AHB1 Peripheral Clock Enable Register, Offset: 0x30
    volatile uint32_t AHB2ENR;           // RCC_AHB2ENR: AHB2 Peripheral Clock Enable Register, Offset: 0x34
    volatile uint32_t AHB3ENR;           // RCC_AHB3ENR: AHB3 Peripheral Clock Enable Register, Offset: 0x38
    uint32_t RESERVED2;                  // Reserved, Offset: 0x3C
    volatile uint32_t APB1ENR;           // RCC_APB1ENR: APB1 Peripheral Clock Enable Register, Offset: 0x40
    volatile uint32_t APB2ENR;           // RCC_APB2ENR: APB2 Peripheral Clock Enable Register, Offset: 0x44
    uint32_t RESERVED3[2];               // Reserved, Offset: 0x48-0x4C
    volatile uint32_t AHB1LPENR;         // RCC_AHB1LPENR: AHB1 Low Power Clock Enable Register, Offset: 0x50
    volatile uint32_t AHB2LPENR;         // RCC_AHB2LPENR: AHB2 Low Power Clock Enable Register, Offset: 0x54
    volatile uint32_t AHB3LPENR;         // RCC_AHB3LPENR: AHB3 Low Power Clock Enable Register, Offset: 0x58
    uint32_t RESERVED4;                  // Reserved, Offset: 0x5C
    volatile uint32_t APB1LPENR;         // RCC_APB1LPENR: APB1 Low Power Clock Enable Register, Offset: 0x60
    volatile uint32_t APB2LPENR;         // RCC_APB2LPENR: APB2 Low Power Clock Enable Register, Offset: 0x64
    uint32_t RESERVED5[2];               // Reserved, Offset: 0x68-0x6C
    volatile uint32_t BDCR;              // RCC_BDCR: Backup Domain Control Register, Offset: 0x70
    volatile uint32_t CSR;               // RCC_CSR: Clock Control & Status Register, Offset: 0x74
    uint32_t RESERVED6[2];               // Reserved, Offset: 0x78-0x7C
    volatile uint32_t SSCGR;             // RCC_SSCGR: Spread Spectrum Clock Generation Register, Offset: 0x80
    volatile uint32_t PLLI2SCFGR;        // RCC_PLLI2SCFGR: PLLI2S Configuration Register, Offset: 0x84
} RCC_RegDef_t;

/* Peripheral definitions - Peripheral based address type casted to register*/


#define GPIOA    ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB    ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC    ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD    ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE    ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF    ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG    ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH    ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI    ((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC      ((RCC_RegDef_t*)RCC_BASEADDR)


/*Clock Enable Macros for GPIOx Peripherals */
#define GPIOA_PCLK_EN()   (RCC->AHB1ENR |=(1<<0))  // GPIOA - AHB1ENR -  Clock enable register - Zeroth position
#define GPIOB_PCLK_EN()   (RCC->AHB1ENR |= (1<<1)) // GPIOB - AHB1ENR -  Clock enable register - First position
#define GPIOC_PCLK_EN()   (RCC->AHB1ENR |= (1<<2)) // GPIOC - AHB1ENR -  Clock enable register - Second position
#define GPIOD_PCLK_EN()   (RCC->AHB1ENR |= (1<<3)) // GPIOD - AHB1ENR -  Clock enable register - Third position
#define GPIOE_PCLK_EN()   (RCC->AHB1ENR |= (1<<4)) // GPIOE - AHB1ENR -  Clock enable register - Fourth position
#define GPIOF_PCLK_EN()   (RCC->AHB1ENR |= (1<<5)) // GPIOF - AHB1ENR -  Clock enable register - Fifth position
#define GPIOG_PCLK_EN()   (RCC->AHB1ENR |= (1<<6)) // GPIOG - AHB1ENR -  Clock enable register - Sixth position
#define GPIOH_PCLK_EN()   (RCC->AHB1ENR |= (1<<7)) // GPIOH - AHB1ENR -  Clock enable register - Seventh position
#define GPIOI_PCLK_EN()   (RCC->AHB1ENR |= (1<<8)) // GPIOI - AHB1ENR -  Clock enable register - Eighth position



/*Clock Disable Peripheral Macros for GPIOx Peripherals */

#define GPIOA_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<0))   // GPIOA - AHB1ENR -  Clock disable register - Zeroth position
#define GPIOB_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<1))   // GPIOB - AHB1ENR -  Clock disable register - First position
#define GPIOC_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<2))   // GPIOC - AHB1ENR -  Clock disable register - Second position
#define GPIOD_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<3))   // GPIOD - AHB1ENR -  Clock disable register - Third position
#define GPIOE_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<4))   // GPIOE - AHB1ENR -  Clock disable register - Fourth position
#define GPIOF_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<5))   // GPIOF - AHB1ENR -  Clock disable register - Fifth position
#define GPIOG_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<6))   // GPIOG - AHB1ENR -  Clock disable register - Sixth position
#define GPIOH_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<7))   // GPIOH - AHB1ENR -  Clock disable register - Seventh position
#define GPIOI_PCLK_DI()   (RCC->AHB1ENR &= ~(1<<8))   // GPIOI - AHB1ENR -  Clock disable register - Eighth position

/*
 * Clock enable macros for USARTx peripherals
 */
#define USART1_PCLK_EN()    (RCC->APB2ENR |= (1<<4))
#define USART2_PCLK_EN()    (RCC->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()    (RCC->APB1ENR |= (1<<18))
#define UART4_PCLK_EN()     (RCC->APB1ENR |= (1<<19))
#define UART5_PCLK_EN()     (RCC->APB1ENR |= (1<<20))
#define USART6_PCLK_EN()    (RCC->APB2ENR |= (1<<6))


/*
 * Clock disable macros for USARTx peripherals
 */
#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1<<4))
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1<<17))
#define USART3_PCLK_DI()    (RCC->APB1ENR &= ~(1<<18))
#define UART4_PCLK_DI()     (RCC->APB1ENR &= ~(1<<19))
#define UART5_PCLK_DI()     (RCC->APB1ENR &= ~(1<<20))
#define USART6_PCLK_DI()    (RCC->APB2ENR &= ~(1<<6))


/*
 * Clock enable macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()    (RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()    (RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()    (RCC->APB1ENR |= (1<<15))



/*
 * Clock disable macros for SPIx peripherals
 */
#define SPI1_PCLK_DI()    (RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()    (RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI()    (RCC->APB1ENR &= ~(1<<15))


/*
 * Clock enable macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN()    (RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()    (RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()    (RCC->APB1ENR |= (1<<23))

/*
 * Clock disable macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()    (RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()    (RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI()    (RCC->APB1ENR &= ~(1<<23))


/*
 * Clock enable macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_EN()    (RCC->APB2ENR |= (1<<14))

/*
 * Clock disable macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= ~(1<<14))


/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~(1<<0)); }while(0)
#define GPIOB_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~(1<<1)); }while(0)
#define GPIOC_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~(1<<2)); }while(0)
#define GPIOD_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<3)); (RCC->AHB1RSTR &= ~(1<<3)); }while(0)
#define GPIOE_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~(1<<4)); }while(0)
#define GPIOF_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<5)); (RCC->AHB1RSTR &= ~(1<<5)); }while(0)
#define GPIOG_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<6)); (RCC->AHB1RSTR &= ~(1<<6)); }while(0)
#define GPIOH_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<7)); (RCC->AHB1RSTR &= ~(1<<7)); }while(0)
#define GPIOI_REG_RESET()   do{ (RCC->AHB1RSTR |= (1<<8)); (RCC->AHB1RSTR &= ~(1<<8)); }while(0)



/*
 * Some generic macros
 */
#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET
#define FLAG_RESET          RESET
#define FLAG_SET            SET



///GPIO_RegDef_t *PGPIOA = GPIOA;   //delete later by video added

#endif /* INC_STM32F407XX_H_ */
