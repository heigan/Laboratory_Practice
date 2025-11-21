#include <stdint.h>
#include <stdbool.h> 
void GPIO_PC1_init(void);
void GPIO_PC2_init(void);
void GPIO_PC3_init(void);
void GPIO_init(void);

// объявление стартового адреса регисторв
#define GPIOA_start_adres 0x40020000UL
#define GPIOB_start_adres 0x40020400UL
#define GPIOC_start_adres 0x40020800UL

#define GPIOA GPIOA_start_adres
#define GPIOB GPIOB_start_adres
#define GPIOC GPIOC_start_adres

// объявление смещение адресов
#define adr_GPIOx_BSRR 0x18UL
#define adr_GPIOx_IDR  0x10UL

// Макросы для установки бита в регистр ODR //
#define GPIOA_BSRR (*(uint32_t*)(GPIOA_start_adres + adr_GPIOx_BSRR))
#define GPIOB_BSRR (*(uint32_t*)(GPIOB_start_adres + adr_GPIOx_BSRR))
#define GPIOC_BSRR (*(uint32_t*)(GPIOC_start_adres + adr_GPIOx_BSRR))

#define WRITE_BIT(REG, NUM)     (REG |= (0x01 << NUM))
#define REWRITE_BIT(REG, NUM)   (REG |= (0x01 << (NUM + 16)))

#define HIGH true
#define LOW false
#define digitalWrite(REG, NUM, a)   if (a){WRITE_BIT(REG, NUM);} else {REWRITE_BIT(REG, NUM);}

// Дерективы для чтения битов
// В общем виде
#define READ_GPIO(ADR, NUM) (*(uint32_t*)(ADR + adr_GPIOx_IDR) & (0x01 << NUM))
// В частом виде
#define READ_GPIOA(NUM) (*(uint32_t*)(GPIOA_start_adres + adr_GPIOx_IDR) & (0x01 << NUM))
#define READ_GPIOB(NUM) (*(uint32_t*)(GPIOB_start_adres + adr_GPIOx_IDR) & (0x01 << NUM))
#define READ_GPIOC(NUM) (*(uint32_t*)(GPIOC_start_adres + adr_GPIOx_IDR) & (0x01 << NUM))

//Макрос для подключения линии GPIO к тактированию
#define RCC_GPIO_EN (*(uint32_t*)(0x40023800UL + 0x30UL))
#define RCC_GPIOA_EN 0x01UL
#define RCC_GPIOB_EN 0x02UL 
#define RCC_GPIOC_EN 0x04UL

#define ENE_RCC_GPIO(REG) (RCC_GPIO_EN |= REG)

//Дерективы для настройки GPIO портов
#define MODER_adr  0x00UL
#define OTYPER_adr 0x04UL
#define OSPEED_adr 0x08UL
#define PUPDR_adr  0x0CUL

// частные случаии
#define GPIOA_MODER   (*(uint32_t*)(GPIOA_start_adres + MODER_adr))
#define GPIOA_OTYPER  (*(uint32_t*)(GPIOA_start_adres + OTYPER_adr))
#define GPIOA_OSPEED  (*(uint32_t*)(GPIOA_start_adres + OSPEED_adr))
#define GPIOA_PUPDR   (*(uint32_t*)(GPIOA_start_adres + PUPDR_adr))

#define GPIOB_MODER   (*(uint32_t*)(GPIOB_start_adres + MODER_adr))
#define GPIOB_OTYPER  (*(uint32_t*)(GPIOB_start_adres + OTYPER_adr))
#define GPIOB_OSPEED  (*(uint32_t*)(GPIOB_start_adres + OSPEED_adr))
#define GPIOB_PUPDR   (*(uint32_t*)(GPIOB_start_adres + PUPDR_adr))

#define GPIOC_MODER   (*(uint32_t*)(GPIOC_start_adres + MODER_adr))
#define GPIOC_OTYPER  (*(uint32_t*)(GPIOC_start_adres + OTYPER_adr))
#define GPIOC_OSPEED  (*(uint32_t*)(GPIOC_start_adres + OSPEED_adr))
#define GPIOC_PUPDR   (*(uint32_t*)(GPIOC_start_adres + PUPDR_adr))

// общий вид
#define GPIOX_MODER(REG)  (*(uint32_t*)(REG + MODER_adr))
#define GPIOX_OTYPER(REG)  (*(uint32_t*)(REG + OTYPER_adr))
#define GPIOX_OSPEED(REG)  (*(uint32_t*)(REG + OSPEED_adr))
#define GPIOX_PUPDR(REG)  (*(uint32_t*)(REG + PUPDR_adr))

//настройки мода
#define input_Mode  0x00
#define GPIO_Mode   0x01
#define alter_Mode  0x02
#define analog_Mode 0x03

#define SET_MODE_GPIO(REG, MOD, NUM) (REG |= (MOD << (NUM*2)))

//настройка типа
#define GPIO_OPP 0x00
#define GPIO_OOD 0x01

#define SET_OTYPER_GPIO(REG, TYPE, NUM) (REG |= (TYPE << NUM))

//настройка скорости
#define GPIO_LS 0x00
#define GPIO_MS 0x01
#define GPIO_FS 0x02
#define GPIO_HS 0x04

#define SET_OSPEED_GPIO(REG, SPEED, NUM) (REG |= (SPEED << (NUM*2)))

//настройка подтяжки
#define GPIO_NN 0x00
#define GPIO_Pp 0x01
#define GPIO_Pd 0x02
#define GPIO_RE 0x04

#define SET_PUPDR_GPIO(REG, PUPD, NUM) (REG |= (PUPD << (NUM*2)))