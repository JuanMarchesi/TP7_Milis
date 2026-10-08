#include "timer.h"
#include "stm32f103xb.h"

void timer_init(){
     RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
     TIM2->CR1 &= ~ (TIM_CR1_CEN);
     TIM2 -> PSC = 7;
     TIM2 -> ARR = 0xFFFF;
     TIM2 -> CNT = 0;
     TIM2 -> DIER |= (TIM_DIER_UIE);
     TIM2 -> EGR |= (TIM_EGR_UG);
     TIM2 -> SR |= (TIM_SR_UIF);
     NVIC_EnableIRQ(TIM2_IRQn);
     TIM2->CR1 |= (TIM_CR1_CEN);

}

void delay_init(){
    RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2 -> PSC = 100;
    TIM2 -> ARR = 0xFFFF;
    TIM2 -> CR1 |= (TIM_CR1_CEN); 
    while (!(TIM2->SR & TIM_SR_UIF));
}

void delay_us(uint32_t us){
    TIM2 -> CNT = 0;
    while (TIM2 -> CNT < us);
}

void delay_ms(uint32_t ms) {
    for(int i=0;i<ms;i++){
        delay_us(1000);
    }
}

volatile int overflow = 0;

uint32_t timer_millis(){
    TIM2 -> CR1 |= TIM_CR1_CEN;

    int time = (overflow + (TIM2 -> CNT)) / 1000; 
};

TIM2_IRQHandler(){
        if (TIM2->SR & TIM_SR_UIF){
        TIM2->SR &= ~TIM_SR_UIF;
    }
}