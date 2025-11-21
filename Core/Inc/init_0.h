#include <stdint.h>
// макрос для устанвоки бита в регистр
#define SET_BIT(REG, BIT) (REG |= BIT)

// макросы для установки конкретного бита в конкретный порт (устарело)
#define SET_GPIO_B3 (*(uint32_t*)(0x40020400UL + 0x18UL) |= 0x08UL)
#define RESET_GPIO_B3 (*(uint32_t*)(0x40020400UL + 0x18UL) |= 0x080000UL)

#define SET_GPIO_B4 (*(uint32_t*)(0x40020400UL + 0x18UL) |= 0x10UL)
#define RESET_GPIO_B4 (*(uint32_t*)(0x40020400UL + 0x18UL) |= 0x100000UL)

#define SET_GPIO_B5 (*(uint32_t*)(0x40020400UL + 0x18UL) |= 0x20UL)
#define RESET_GPIO_B5 (*(uint32_t*)(0x40020400UL + 0x18UL) |= 0x200000UL)

// макрос для адресов битов для записи их в регистр выхода (устаренло) [заменено]
#define GPIO_BSRR_PIN3_SET 0x08UL
#define GPIO_BSRR_PIN4_SET 0x10UL
#define GPIO_BSRR_PIN5_SET 0x20UL

#define GPIO_BSRR_PIN3_RESET 0x080000UL
#define GPIO_BSRR_PIN4_RESET 0x100000UL
#define GPIO_BSRR_PIN5_RESET 0x200000UL

// Дерективы для настройки GPIO портов (устарели)
#define GPIOB_MODER  (*(uint32_t*)(0x40020400UL + 0x00UL))
#define GPIOB_OTYPER (*(uint32_t*)(0x40020400UL + 0x04UL))
#define GPIOB_OSPEED (*(uint32_t*)(0x40020400UL + 0x08UL))
#define GPIOB_PUPDR  (*(uint32_t*)(0x40020400UL + 0x0CUL))

#define GPIO_MODE_PIN4_OUT 0x100UL
#define GPIO_MODE_PIN4_PP 0x00UL
#define GPIO_MODE_PIN4_MID 0x100UL
#define GPIO_MODE_PIN4_NOPUPD 0x00UL


// Дерективы для чтения битов (устарело)
#define READ_GPIO_C0 (*(uint32_t*)(GPIOC_start_adres + adr_GPIOx_IDR) & 0x01UL)
#define READ_GPIO_C1 (*(uint32_t*)(GPIOC_start_adres + adr_GPIOx_IDR) & 0x02UL)
#define READ_GPIO_C2 (*(uint32_t*)(GPIOC_start_adres + adr_GPIOx_IDR) & 0x04UL)
#define READ_GPIO_C3 (*(uint32_t*)(GPIOC_start_adres + adr_GPIOx_IDR) & 0x08UL)