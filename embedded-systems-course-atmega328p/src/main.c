#include <stdint.h>
#include "utils/delay.h"
#include "drivers/adc/adc.h"

#include "servo_motor.h"
#include "sensor_ultrasonic.h"
#include "alarma.h"
#include "potentiometru.h"
#include "comunicare.h"

int main(void) {
    ADC_Init(); 
    Servo_Init();
    Ultrasonic_Init();
    Alarma_Init();
    Potentiometru_Init();
    Comunicare_Init();
    
    // Pornim de la gradul 10, în "zona sigură" a motorului
    int16_t unghi_curent = 10;
    // Trecem la pas de 2 grade ca să aibă viteză și să nu mai "gâfâie"
    int8_t directie = 2; 
    
    while (1) {
        uint32_t viteza_delay = Potentiometru_CitesteVitezaScanare();
        
        Servo_SeteazaUnghi((uint8_t)unghi_curent);
        
        Delay(viteza_delay); 
        
        uint16_t distanta = Ultrasonic_CitesteDistanta();
        Alarma_Actualizeaza(distanta);
        Comunicare_TrimiteDateRadar((uint8_t)unghi_curent, distanta);
        
        unghi_curent += directie;
        
        // Evităm complet marginile de 0 și 180 ca să nu mai lovească plasticele din interior!
        if (unghi_curent >= 170) {
            unghi_curent = 170;
            directie = -2;
        } 
        else if (unghi_curent <= 10) {
            unghi_curent = 10;
            directie = 2;
        }
    }
    return 0;
}