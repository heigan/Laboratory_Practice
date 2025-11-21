#include <stdint.h> 
#include <stdbool.h>
#include <init.h>
#include <init_dop.h> 
// 1 секунда = 1 000 000 счётчика (примерно)

/* 
порты группы B - для выхода на внешние светодиоды
    B6  - красный светодиод
    B7  - жёлтый светодиод
    B8  - зелёный светодиод
    B9  - голубой RGB светодиод
    B10 - зелёный RGB светодиод
    B12 - красный RGB светодиод
порты группы С - для работы с кнопка 
    С0 - кнопка включение светодиодов 
    С1 - кнопка выключение светодиодов 
    С2 - кнопка смены частоты 
    С3 - кнопка выбора настраиваемого светодиода (нажатие) и смены шага (удержание)
*/

// Объявления переменны

// флаги срабатывания "таймеров"
bool flag_1 = false;
bool flag_2 = false;

// счётчики "таймеров"
uint32_t count_1 = 0;
uint32_t count_2 = 0;

// флаги сохранения состояния нажатия кнопок
// функция антидребезга и различия нажатия и отпуская кнопки
uint8_t butt_0_state = 1;
uint8_t butt_1_state = 1; 
uint8_t butt_2_state = 1; 
uint8_t butt_3_state = 1;

// Переменные шага включеня/выключения
uint8_t step_min = 1;
uint8_t step_max = 6;
uint8_t step = 1;

uint8_t  cursor = 0;    // "курсор" для настройки частоты моргания
uint32_t butt_3_count;  // счётчик долгого нажатия кнопки 
uint32_t butt_3_long_push = 500000; // значение долгого нажатия кнопки


int8_t cur_led = -1;                        // переменная отслеживания включения/отключения светодиодов
                                            // начинаем отсчёт от -1 для того, чтобы первым нажатиям включать светодиод 1
uint8_t led[6] = {6, 7, 8, 9, 10, 12};      // массив портов светодиодов
bool led_state[6] = {false, false, false, 
                    false, false, false};   // массив состояний (вкл/выкл)
uint8_t led_blink[6] = {0, 0, 0, 0, 0, 0};  // массив состояний (скорость моргания
                                            // 0 - постоянное включение
                                            // 1 - моргание с частотой 0,5 Гц
                                            // 2 - моргание с частотой 0,25 Гц

// переменные для отслеживания состояний светодиодов в MCUViewer
bool led_0_state = false, led_1_state = false, led_2_state = false, 
    led_3_state = false, led_4_state = false, led_5_state = false;

uint8_t led_0_blink = 0,  led_1_blink = 0, led_2_blink = 0,
        led_3_blink = 0,  led_4_blink = 0, led_5_blink = 0;

int main(void){

    GPIO_init_dop();    //инициализация пинов

    while (1){
        // счётчики для реализации "таймера"
        count_1 ++;
        count_2 ++;

        // обрабока кнопки 0 (включение светодиодов)
        if ((READ_GPIOC(0) != butt_0_state) & (butt_0_state == 0) ) 
        {   
            DELAY_LOOP(25000);
            if ((READ_GPIOC(0) != butt_0_state) & (butt_0_state == 0)) 
            {
                // переводим курсов и включаем соответсвующий светодиод
                for (uint8_t i_0 = 0; i_0 < step; i_0++)
                {
                    cur_led += 1;
                    //защита  от обращения в несущетсвующим элементам массива
                    if (cur_led > 5) {cur_led = 5;}    
                    led_state[cur_led] = true;  
                }     
            } 
        }
        // // обрабока кнопки 1 (выключение светодиодов)
        if ((READ_GPIOC(1) != butt_1_state) & (butt_1_state == 0) ) 
        {   
            DELAY_LOOP(25000);
            if ((READ_GPIOC(1) != butt_1_state) & (butt_1_state == 0)) 
            {
                // выключаем светодиод и меняем курсор
                for (uint8_t i_1 = 0; i_1 < step; i_1++)
                {
                    //защита  от обращения в несущетсвующим элементам массива
                    if (cur_led < -1) {cur_led = -1; break;} 
                    led_state[cur_led] = false;
                    cur_led -= 1;
                }                 
            }
        }
        
        // Обработка нажатия кнопки 3 (изменения частоты моргания)
         if ((READ_GPIOC(2) != butt_2_state) & (butt_2_state == 0) ) 
        {   
            DELAY_LOOP(25000);
            if ((READ_GPIOC(2) != butt_2_state) & (butt_2_state == 0)) 
                {
                    led_blink[cursor] += 1;
                    if (led_blink[cursor] > 2) {led_blink[cursor] = 0;}
                }
 
        } 
        
        if ((READ_GPIOC(3) != butt_3_state) & (butt_3_state == 0) ) 
        {   
            butt_3_state = READ_GPIOC(3);

            for(volatile int i=0; i<25000; i++) // задержка от дребезга
            
            // пока кнопка зажата - работает счётчик
            while ((READ_GPIOC(3) != 0)) 
            {butt_3_count += 1;}

            // если счётчик соответсвует долгому - нажатию меняем шаг
            if (butt_3_count >= butt_3_long_push)   {step += 1;}
            // в если счётчик не дошёл дл=о порога и не равен нулю, то меняем курсор настройки частоты
            else if (butt_3_count !=0)              {cursor += 1;}
            // цикличное изменение шага и курсора
            if (step > step_max) {step = step_min;} 
            if (cursor > 5) {cursor = 0;}
            butt_3_count = 0;
        } 
        
        // обновление состояния кнопки
        butt_0_state = READ_GPIOC(0);
        butt_1_state = READ_GPIOC(1);
        butt_2_state = READ_GPIOC(2);
        butt_3_state = READ_GPIOC(3);

        // обработчик "таймера"
        // желаймая частота стабатывания делится на 2, т.к. моргание требует двух переключений состояния
        if (count_1 >= base_frequency / T_1 * 0.5) {count_1 = 0; flag_1 ^= 1;}
        if (count_2 >= base_frequency / T_2 * 0.5) {count_2 = 0; flag_2 ^= 1;}

        // цикл обработки состояний светдодиодов
        for (uint8_t i = 0; i < 6; i++)
        {
            if(led_state[i])    //проверка состояния включения светодиода
            {
                if (led_blink[i] == 0)
                {
                    WRITE_BIT(GPIOB_BSRR, led[i]);
                }
                else if (led_blink[i] == 1)
                {
                    if (flag_1) {WRITE_BIT(GPIOB_BSRR, led[i]);}
                    else        {REWRITE_BIT(GPIOB_BSRR, led[i]);}
                }
                else if (led_blink[i] == 2)
                {
                    if (flag_2) {WRITE_BIT(GPIOB_BSRR, led[i]);}
                    else        {REWRITE_BIT(GPIOB_BSRR, led[i]);}
                } 
            }
            else {REWRITE_BIT(GPIOB_BSRR, led[i]);}            
        }
        // обновление состояний светодиодов
        led_0_state = led_state[0];        led_1_state = led_state[1];        led_2_state = led_state[2];
        led_3_state = led_state[3];        led_4_state = led_state[4];        led_5_state = led_state[5];

        led_0_blink = led_blink[0];        led_1_blink = led_blink[1];        led_2_blink = led_blink[2];
        led_3_blink = led_blink[3];        led_4_blink = led_blink[4];        led_5_blink = led_blink[5];
    }
}