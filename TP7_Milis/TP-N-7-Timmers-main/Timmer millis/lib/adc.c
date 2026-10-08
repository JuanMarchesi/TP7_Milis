#include "adc.h"
#include "stm32f103xb.h"

void adc_init (int pin){
    RCC -> APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN | RCC_CFGR_ADCPRE ; 

    GPIOA -> CRL &= ~(0xF << pin * 4); 
    GPIOA -> CRL |= (0000 << pin * 4);

    ADC1 -> CR2 |= ADC_CR2_ADON; 
    for(int i = 0; i <= 1000; i++); 

    ADC1 -> CR2 |= ADC_CR2_RSTCAL; 
    while(ADC1 -> CR2 & ADC_CR2_RSTCAL); 

    ADC1 -> CR2 |= ADC_CR2_CAL; 
    while(ADC1 -> CR2 & ADC_CR2_CAL);

}

void adc_read (unsigned int Canal){
    
    ADC1 -> SQR3 |= (1111 << Canal); 

    ADC1 -> SMPR2 |= (111 << Canal * 3); 

    while(ADC1 -> SR & ADC_SR_EOC); 

    return ADC1 -> DR; 

}
