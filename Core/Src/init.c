#include <stdint.h>
#include <init.h> 
#include <stdbool.h> 
void GPIO_PC1_init(void)
{
    *(uint32_t*)(0x40020800UL + 0x00UL) |= 0x04;    // В регистре мода GPIO (Moder) устанавливаем последоватьльность 01 в регистры пина PC1 - пин  рабоатет в режиме GPIO порта
    *(uint32_t*)(0x40020800UL + 0x04UL) |= 0x00;    // Выбор типа выхода. Оставляем без изменения - Output Push-Pull
    *(uint32_t*)(0x40020800UL + 0x08UL) |= 0x04;    // В регистр скорости работы GPIO устанавливаем комбинацию 01 в регистры пина PC1  - средняя скорсоть
    *(uint32_t*)(0x40020800UL + 0x0CUL) |= 0x00;    // Выобр типа подтяжки. Выбираем No pull-up, pull-down (00) 
}

void GPIO_PC2_init(void)
{
    *(uint32_t*)(GPIOC_start_adres + MODER_adr)  |= (GPIO_Mode << (2*2));    
    *(uint32_t*)(GPIOC_start_adres + OTYPER_adr) |= (GPIO_OPP  << (2*2));    
    *(uint32_t*)(GPIOC_start_adres + OSPEED_adr) |= (GPIO_MS   << (2*2));    
    *(uint32_t*)(GPIOC_start_adres + PUPDR_adr)  |= (GPIO_NN   << (2*2));    
}


void GPIO_PC3_init(void)
{
    SET_MODE_GPIO   (GPIOC_MODER,   GPIO_Mode,  3);
    SET_OTYPER_GPIO (GPIOC_OTYPER,  GPIO_OPP,   3);
    SET_OSPEED_GPIO (GPIOC_OSPEED,  GPIO_MS,    3);
    SET_PUPDR_GPIO  (GPIOC_PUPDR,   GPIO_NN,    3);   
}

void GPIO_init(void)
{
    RCC_GPIO_EN |= (RCC_GPIOB_EN + RCC_GPIOC_EN); 
    //Инициализация пинов группы B (через макросы)

    SET_MODE_GPIO   (GPIOB_MODER,   GPIO_Mode,  13);
    SET_OTYPER_GPIO (GPIOB_OTYPER,  GPIO_OPP,   13); 
    SET_OSPEED_GPIO (GPIOB_OSPEED,  GPIO_MS,    13);
    SET_PUPDR_GPIO  (GPIOB_PUPDR,   GPIO_NN,    13);
    
    SET_MODE_GPIO   (GPIOB_MODER,   GPIO_Mode,  14);
    SET_OTYPER_GPIO (GPIOB_OTYPER,  GPIO_OPP,   14); 
    SET_OSPEED_GPIO (GPIOB_OSPEED,  GPIO_MS,    14);
    SET_PUPDR_GPIO  (GPIOB_PUPDR,   GPIO_NN,    14); 
    
    SET_MODE_GPIO   (GPIOB_MODER,   GPIO_Mode,  15);
    SET_OTYPER_GPIO (GPIOB_OTYPER,  GPIO_OPP,   15); 
    SET_OSPEED_GPIO (GPIOB_OSPEED,  GPIO_MS,    15);
    SET_PUPDR_GPIO  (GPIOB_PUPDR,   GPIO_NN,    15); 

    //Инициализация пинов группы C
    // PC1 инициализированн с помощью прямой записи битов в регистры (оформленно в отдельной функции)
    // PC2 инициализированн с помощью записи битов в регистры с помощью макросов макросы  
    // PC3 инициализированн c мопощью функции и макросов
    GPIO_PC1_init();
    GPIO_PC2_init();
    GPIO_PC3_init();   
}