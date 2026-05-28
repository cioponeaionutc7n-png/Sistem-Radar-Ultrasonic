#include "alarma.h"
#include "bsp/bsp.h"
#include "drivers/gpio/gpio.h"
#include "drivers/pwm/pwm.h" 

// AM INVERSAT PINII CA SĂ SE POTRIVEASCĂ CU REALITATEA:
#define PIN_LED_VERDE D6 
#define PIN_LED_ROSU  D7 
#define PIN_BUZZER    D3 

static uint8_t mentine_alarma = 0;

void Alarma_Init(void) {
    GPIO_Init(PIN_LED_VERDE, GPIO_OUTPUT);
    GPIO_Init(PIN_LED_ROSU, GPIO_OUTPUT);
    
    // Inițializăm buzzer-ul pe D3 la 1000 Hz
    PWM_Init(PIN_BUZZER, 1000); 
    PWM_SetDutyCycle(PIN_BUZZER, 0); 
}

void Alarma_Actualizeaza(uint16_t distanta_cm) {
    if (distanta_cm > 0 && distanta_cm <= 30) {
        mentine_alarma = 4; 
    }
    
    if (mentine_alarma > 0) {
      
        GPIO_Write(PIN_LED_VERDE, GPIO_LOW);  
        
        GPIO_Write(PIN_LED_ROSU, GPIO_HIGH);  
        PWM_SetDutyCycle(PIN_BUZZER, 0);     
        
        mentine_alarma--; 
    } else {
       
        GPIO_Write(PIN_LED_ROSU, GPIO_LOW);   
        PWM_SetDutyCycle(PIN_BUZZER, 10);      
        
        GPIO_Write(PIN_LED_VERDE, GPIO_HIGH); 
    }
}