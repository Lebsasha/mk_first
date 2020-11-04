//
// Created by alexander on 01/11/2020.
//

#include "main.h"
#include "main_target.h"
#include <assert.h>

const int MY_FREQ = 100;
extern const int DETAILYTY_1;
extern const int DETAILYTY_2;
extern const int DETAILYTY_3;
extern TIM_HandleTypeDef htim1;

void my_delay(int mc_s)
{
    if (mc_s <= 0)
        return;
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (__HAL_TIM_GET_COUNTER(&htim1) < mc_s)
    {}
}

void soft_glow(GPIO_TypeDef *port, int pin, int duty_cycle, int mc_s, int detailyty)
{
    assert(duty_cycle >= 0 && duty_cycle < detailyty + 1);
    static const int TIME = 1000000 / MY_FREQ;// 10000
    while ((mc_s -= TIME) >= 0)
    {
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);//on
        my_delay(duty_cycle * TIME / detailyty);
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);//off
        my_delay((detailyty - duty_cycle) * TIME / detailyty);
    }
}


void calc_1()
{
    static int counter = 0;
    static int i = 0;
    static int ampl = 0;
    static enum STEP curr_step = UP;
    ++counter;
    switch (curr_step)
    {
        case UP:
            if (counter == 100)// DETAILYTY_1
            {
                ++i;
                ampl = (int) (100 * (sin((double) (i) / 100 * M_PI - M_PI_2) + 1) / 2);
                //        100 ticks per 10^-4      DETAILYTY_1
                counter = 0;
            }
            if (i == 100)
            {
//                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                curr_step = LIGHT;
                i = 0;
                counter = 0;//Unused? TODO
            }
            if (counter < ampl)// 100 ticks per 10^-4
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
            }
            break;
        case LIGHT:
            if (counter == 100)
            {
                ++i;
                counter = 0;
            }
            if (i == 100)
            {
                curr_step = DOWN;
                i = 100;//Why? TODO x2
                counter = 0;//Unused?
            }
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
            break;
        case DOWN:
            if (counter == 100)// DETAILYTY_1
            {
                --i;
                ampl = (int) (100 * (sin((double) (i) / 100 * M_PI - M_PI_2) + 1) / 2);
                //        100 ticks per 10^-4      DETAILYTY_1
                counter = 0;
            }
            if (i == 0)
            {
                curr_step = UP;
                i = 0;//Why? TODO x2
                counter = 0;//Unused?
            }
            if (counter < ampl)// 100 ticks per 10^-4
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
            }
            break;
    }
}

/**
 * @note 100 ticks per 10^-4 * DETAILYTY_1 = 1 s
 * @note 100 ticks per 10^-4 * DETAILYTY_2 = 1.3 s
 * @note 100 ticks per 10^-4 * DETAILYTY_3 = 1.7 s
 */
void calc_2()
{
    static int counter = 0;
    static int i = 0;
    static int ampl = 0;
    static enum STEP curr_step = UP;
    ++counter;
    switch (curr_step)
    {
        case UP:
            if (counter == 100)// DETAILYTY_1
            {
                ++i;
                ampl = (int) (100 * (sin((double) (i) / 130 * M_PI - M_PI_2) + 1) / 2);
                //        100 ticks per 10^-4      DETAILYTY_1
                counter = 0;
            }
            if (i == 130)
            {
//                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                curr_step = LIGHT;
                i = 0;
                counter = 0;//Unused? TODO
            }
            if (counter < ampl)// 100 ticks per 10^-4
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
            }
            break;
        case LIGHT:
            if (counter == 100)
            {
                ++i;
                counter = 0;
            }
            if (i == 130)
            {
                curr_step = DOWN;
                i = 130;// Why? TODO x2
                counter = 0;//Unused?
            }
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
            break;
        case DOWN:
            if (counter == 100)// DETAILYTY_1
            {
                --i;
                ampl = (int) (100 * (sin((double) (i) / 130 * M_PI - M_PI_2) + 1) / 2);
                counter = 0;
                //        100 ticks per 10^-4      DETAILYTY_1
            }
            if (i == 0)
            {
                curr_step = UP;
                i = 0;//Why?
                counter = 0;//Unused? TODO x2
            }
            if (counter < ampl)// 100 ticks per 10^-4
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
            }
            break;
    }
}

void calc_3()
{
    static int counter = 0;
    static int i = 0;
    static int ampl = 0;
    static enum STEP curr_step = UP;
    ++counter;
    switch (curr_step)
    {
        case UP:
            if (counter == 100)// DETAILYTY_1
            {
                ++i;
                ampl = (int) (100 * (sin((double) (i) / 170 * M_PI - M_PI_2) + 1) / 2);
                //        100 ticks per 10^-4      DETAILYTY_1
                counter = 0;
            }
            if (i == 170)
            {
//                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                curr_step = LIGHT;
                i = 0;
                counter = 0;//Unused? TODO
            }
            if (counter < ampl)// 100 ticks per 10^-4
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
            }
            break;
        case LIGHT:
            if (counter == 100)
            {
                ++i;
                counter = 0;
            }
            if (i == 170)
            {
                curr_step = DOWN;
                i = 170;// Why? TODO x2
                counter = 0;//Unused?
            }
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
            break;
        case DOWN:
            if (counter == 100)// DETAILYTY_1
            {
                --i;
                ampl = (int) (100 * (sin((double) (i) / 170 * M_PI - M_PI_2) + 1) / 2);
                counter = 0;
                //        100 ticks per 10^-4      DETAILYTY_1
            }
            if (i == 0)
            {
                curr_step = UP;
                i = 0;//Why?
                counter = 0;//Unused? TODO x2
            }
            if (counter < ampl)// 100 ticks per 10^-4
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
            }
            break;
    }
}