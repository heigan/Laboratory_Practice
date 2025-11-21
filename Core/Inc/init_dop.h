#include <stdint.h>
#include <init.h>

#define base_frequency 1000000             //базовая частота цилка (взято примерно, по прямым измерениям)
#define T_1    20          // Период моргания светодиода 
#define T_2    50        // Период моргания светодиода 
#define T_3    100        // Период моргания светодиода
#define k      1 

#define DELAY_LOOP(count) for(volatile uint32_t i = 0; i < count; i++)

void GPIO_init_dop(void);
void GPIOX_INIT(uint32_t GPIOX, 
                uint8_t mode, 
                uint8_t type, 
                uint8_t speed,
                uint8_t PUPDR,
                uint8_t n);