#include <stdint.h>
#include <init.h>
#include <init_dop.h>  

void GPIOX_INIT(uint32_t GPIOX, 
                uint8_t mode, 
                uint8_t type, 
                uint8_t speed,
                uint8_t PUPDR,
                uint8_t n)

                
{
    SET_MODE_GPIO   (GPIOX_MODER(GPIOX),   mode,   n);
    SET_OTYPER_GPIO (GPIOX_OTYPER(GPIOX),   type,   n);
    SET_OSPEED_GPIO (GPIOX_OSPEED(GPIOX),   speed,  n);
    SET_PUPDR_GPIO  (GPIOX_PUPDR(GPIOX),   PUPDR,  n);

}

void GPIO_init_dop(void)
{
    RCC_GPIO_EN |= (RCC_GPIOB_EN + RCC_GPIOC_EN); 
    
    
    GPIOX_INIT(GPIOB, GPIO_Mode, GPIO_OPP, GPIO_MS, GPIO_NN, 6);
    GPIOX_INIT(GPIOB, GPIO_Mode, GPIO_OPP, GPIO_MS, GPIO_NN, 7);
    GPIOX_INIT(GPIOB, GPIO_Mode, GPIO_OPP, GPIO_MS, GPIO_NN, 8);
    GPIOX_INIT(GPIOB, GPIO_Mode, GPIO_OPP, GPIO_MS, GPIO_NN, 9);
    GPIOX_INIT(GPIOB, GPIO_Mode, GPIO_OPP, GPIO_MS, GPIO_NN, 10);
    GPIOX_INIT(GPIOB, GPIO_Mode, GPIO_OPP, GPIO_MS, GPIO_NN, 12);

}
