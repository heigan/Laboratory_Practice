#include <stdint.h> 
#include <init.h>
#include <stdbool.h> 
/*  порты группы B - для выхода на внешние светодиоды
    B13 - красный светодиод                 led_3_state   
    B14 - синий светодиод                   led_4_state
    B15 - зелёный светодиод                 led_5_state
    порты группы С - для работы с кнопка 
    С0 - кнопка 0 (кнопка режима)
    С1 - кнопка 1 (красный светодиод)       led_0_state
    С2 - кнопка 2 (жёлтый светодиод)        led_1_state
    С3 - кнопка 3 (зелёный светодиод)       led_2_state
*/

// счётчики кнопки режима
uint8_t butt_0_mode;    
uint8_t butt_0_mode_past;
// режим работы порта кнопки: 1 - вход, 0 - выход
bool butt_1_mode = true;   // режим кнопки 1
bool butt_2_mode = true;   // режим кнопки 2
bool butt_3_mode = true;   // режим кнопки 3

// состояние кнопок
bool butt_0_state = true, butt_1_state = true, butt_2_state = true, butt_3_state = true;
// состояние светодиодов
bool led_0_state, led_1_state, led_2_state, led_3_state, led_4_state, led_5_state;

int main(void){
    GPIO_init(); // инициализация портов
    
    while (1){
        // обработка кнопки смены режима
        if ((READ_GPIOC(0) != butt_0_state) & (butt_0_state == 0) ) 
        {   
            for(volatile int i=0; i<25000; i++);
            if ((READ_GPIOC(0) != butt_0_state)) 
                {butt_0_mode += 1; }
            if (butt_0_mode > 4) {butt_0_mode = 0;} 
        }       
        // Проверка, что счётчик режима работы кнопок изменился и установка соответсвующего режима
        if ((butt_0_mode != butt_0_mode_past) && (butt_0_mode == 0)){
            butt_1_mode = true;
            butt_2_mode = true;
            butt_3_mode = true;
        }

        if ((butt_0_mode != butt_0_mode_past) && (butt_0_mode == 1)) {
            butt_1_mode = false;
            butt_2_mode = true; 
            butt_3_mode = true;  
        }

        if ((butt_0_mode != butt_0_mode_past) && (butt_0_mode == 2)){
            butt_1_mode = true;
            butt_2_mode = false; 
            butt_3_mode = true;   
        }

        if ((butt_0_mode != butt_0_mode_past) && (butt_0_mode == 3)){ 
            butt_1_mode = true;
            butt_2_mode = true; 
            butt_3_mode = false;  
        }

        if ((butt_0_mode != butt_0_mode_past) && (butt_0_mode == 4)) {
            butt_1_mode = false; 
            butt_2_mode = false; 
            butt_3_mode = false;
        }
        
        if (!butt_1_mode)            {led_0_state = HIGH; led_3_state = LOW;}       
        else if (READ_GPIOC(1) != 0) {led_0_state = LOW; led_3_state = HIGH;}
        else                         {led_0_state = LOW; led_3_state = LOW;}

        if (!butt_2_mode)            {led_1_state = HIGH; led_4_state = LOW;}       
        else if (READ_GPIOC(2) != 0) {led_1_state = LOW; led_4_state = HIGH;}
        else                         {led_1_state = LOW; led_4_state = LOW;}

        if (!butt_3_mode)            {led_2_state = HIGH; led_5_state = LOW;}       
        else if (READ_GPIOC(3) != 0) {led_2_state = LOW; led_5_state = HIGH;}
        else                         {led_2_state = LOW; led_5_state = LOW;}

        // обновление состояния кнопок        
        butt_0_state = READ_GPIOC(0);
        butt_1_state = READ_GPIOC(1);
        butt_2_state = READ_GPIOC(2);
        butt_3_state = READ_GPIOC(3);
        butt_0_mode_past = butt_0_mode;

        digitalWrite(GPIOC_BSRR, 1, led_0_state);
        digitalWrite(GPIOC_BSRR, 2, led_1_state);
        digitalWrite(GPIOC_BSRR, 3, led_2_state);
        digitalWrite(GPIOB_BSRR, 13, led_3_state);
        digitalWrite(GPIOB_BSRR, 14, led_4_state);
        digitalWrite(GPIOB_BSRR, 15, led_5_state);
    }
}