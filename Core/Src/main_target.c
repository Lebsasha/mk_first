//
// Created by alexander on 01/11/2020.
//

#include "main.h"
#include <assert.h>

const int MY_FREQ=100;
extern const int DETAILYTY_1;
extern const int DETAILYTY_2;
extern const int DETAILYTY_3;
extern TIM_HandleTypeDef htim1;

void my_delay(int mc_s)
{
    if(mc_s<=0)
        return;
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (__HAL_TIM_GET_COUNTER(&htim1) < mc_s)
    {}
}

void soft_glow(GPIO_TypeDef *port, int pin, int duty_cycle, int mc_s, int detailyty)
{
    assert(duty_cycle >=0 && duty_cycle < detailyty + 1);
    static const int TIME= 1000000 / MY_FREQ;// 10000
    while((mc_s-=TIME) >= 0)
    {
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);//on
        my_delay(duty_cycle * TIME / detailyty);
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);//off
        my_delay((detailyty - duty_cycle) * TIME / detailyty);
    }
}

void calc_1()
{
    static int counter=0;
    static int i=0;
    static int ampl=0;
    ++counter;
    if (counter < 10000)// 0-1s
    {
        if (!(counter % 100))// DETAILYTY_1
        {
            ++i;
            ampl=(int) (100*(sin((double) (i) / 100 * M_PI - M_PI_2) + 1) / 2);
            //        100 ticks per 10^-4      DETAILYTY_1
        }
        if(counter%100<ampl)// 100 ticks per 10^-4
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
        }
    }
    else if (counter == 10000)// 1-2s
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
    }
    else if (counter >=20000 && counter < 30000)// 2-3s
    {
        if (!(counter % 100))// DETAILYTY_1
        {
            --i;
            ampl=(int) (100*(sin((double) (i) / 100 * M_PI - M_PI_2) + 1) / 2);
            //        100 ticks per 10^-4      DETAILYTY_1
        }
        if(counter%100<ampl)// 100 ticks per 10^-4
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
        }
    }
    else if (counter == 30000)
        counter-=30000+1;//because above ++counter;
}
