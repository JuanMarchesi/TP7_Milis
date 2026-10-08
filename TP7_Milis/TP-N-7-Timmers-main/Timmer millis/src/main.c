#include "stm32f103xb.h"  
#include "pwm.h"          
#include "adc.h"          

int potenciometro = 1;             
int led = 2;              
int conversion;           
int valor;                

int main()
{
    // habilito el clock del puerto A
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    adc_init();            // inicio el ADC
    pwm_init(1, 1000);     // inicio el PWM

    while (1)
    {
        // Leo el valor del potenciometro
        conversion = adc_read(potenciometro);

        // lo convierto a un valor entre 0-100
        valor = (conversion * 100) / 4095;

        // le pongo el valor al pwm
        pwm(1, valor);
    }
}