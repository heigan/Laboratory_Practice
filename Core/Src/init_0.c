#include <stdint.h>
#include <C:\Users\Asus\MC & Mc\LB_1\Core\Inc\init_0.h> 
/*
        
        if ((butt_1_mode == 1 &&  READ_GPIOC(1)!= 0)){WRITE_BIT(GPIOB_BSRR, 15);}
        if ((butt_2_mode == 1 &&  READ_GPIOC(2)!= 0)){WRITE_BIT(GPIOB_BSRR, 14);}
        if ((butt_3_mode == 1 &&  READ_GPIOC(2)!= 0)){WRITE_BIT(GPIOB_BSRR, 13);}

        if (butt_1_mode == 0) {WRITE_BIT(GPIOC_BSRR, 1);}
        if (butt_2_mode == 0) {WRITE_BIT(GPIOC_BSRR, 2);}
        if (butt_3_mode == 0) {WRITE_BIT(GPIOC_BSRR, 3);}
*/


// функции для инициализации конкретных портов и их комбинаций (устарело)
void GPIO_PB3_init(void)
{
    *(uint32_t*)(0x40023800UL + 0x30UL) |= 0x02;    // Подключение тактивраония GPIOBEN
    *(uint32_t*)(0x40020400UL + 0x00UL) |= 0x40;  // В регистре мода GPIO для  (Moder) устанавливаем последоватьльность 01 - пин  рабоатет в режиме GPIO порта
    *(uint32_t*)(0x40020400UL + 0x04UL) |= 0x00;    // Выобр типа выхода. Оставляем без изменения - Output Push-Pull
    *(uint32_t*)(0x40020400UL + 0x08UL) |= 0x40;  // В регистр скорости работы GPIOB для пина PB7 устанавливаем комбинацию 01 - средняя скорсоть
    *(uint32_t*)(0x40020400UL + 0x0CUL) |= 0x00;    // Выобр типа подтяжки. Оставляем выбираем No pull-up, pull-down (00) 
}

void GPIO_PB4_init(void)
{
    RCC_GPIO_EN     |= RCC_GPIOB_EN;     
    GPIOB_MODER     |= GPIO_MODE_PIN4_OUT;  
    GPIOB_OTYPER    |= GPIO_MODE_PIN4_PP;    
    GPIOB_OSPEED    |= GPIO_MODE_PIN4_MID;  
    GPIOB_PUPDR     |= GPIO_MODE_PIN4_NOPUPD;    
}

void GPIO_PB5_init(void)
{
    ENE_RCC_GPIO(RCC_GPIOB_EN);    
    *(uint32_t*)(0x40020400UL + 0x00UL) |= 0x400;  
    *(uint32_t*)(0x40020400UL + 0x04UL) |= 0x00;    
    *(uint32_t*)(0x40020400UL + 0x08UL) |= 0x400;  
    *(uint32_t*)(0x40020400UL + 0x0CUL) |= 0x00;    
}

void GPIO_init(void)
{
    *(uint32_t*)(0x40020400UL + 0x00UL) |= 0x54000000; 
    *(uint32_t*)(0x40020400UL + 0x04UL) |= 0x00;
    *(uint32_t*)(0x40020400UL + 0x08UL) |= (0x54000000);  
    *(uint32_t*)(0x40020400UL + 0x0CUL) |= 0x00;
}

// функция для общей настрйоки пинов (устарело, используеться для ограниченного количества групп пинов)
void GPIOX_INIT(uint32_t GPIOX, 
                uint8_t mode, 
                uint8_t type, 
                uint8_t speed,
                uint8_t PUPDR,
                uint8_t n)
{
    if (GPIOX == GPIOA_start_adres){
        SET_MODE_GPIO   (GPIOA_MODER,   mode,   n);
        SET_OTYPER_GPIO (GPIOA_MODER,   type,   n);
        SET_OSPEED_GPIO (GPIOA_MODER,   speed,  n);
        SET_PUPDR_GPIO  (GPIOA_MODER,   PUPDR,  n);
    }
    else if (GPIOX == GPIOB_start_adres)
    {
        SET_MODE_GPIO   (GPIOB_MODER,   mode,   n);
        SET_OTYPER_GPIO (GPIOB_MODER,   type,   n);
        SET_OSPEED_GPIO (GPIOB_MODER,   speed,  n);
        SET_PUPDR_GPIO  (GPIOB_MODER,   PUPDR,  n);
    }
    else if (GPIOX == GPIOC_start_adres)
    {
        SET_MODE_GPIO   (GPIOC_MODER,   mode,   n);
        SET_OTYPER_GPIO (GPIOC_MODER,   type,   n);
        SET_OSPEED_GPIO (GPIOC_MODER,   speed,  n);
        SET_PUPDR_GPIO  (GPIOC_MODER,   PUPDR,  n);
    } 

}