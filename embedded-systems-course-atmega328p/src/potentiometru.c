#include "potentiometru.h"
#include "drivers/adc/adc.h"

#define CH_POT 0 

void Potentiometru_Init(void) {
}

uint32_t Potentiometru_CitesteVitezaScanare(void) {
    uint16_t valoare_adc = ADC_Read(CH_POT);
    
    // Pauză între 15ms (foarte rapid) și 75ms (lent și precis)
    uint32_t delay_ms = ((uint32_t)valoare_adc * 60) / 1023;
    
    return delay_ms;
}