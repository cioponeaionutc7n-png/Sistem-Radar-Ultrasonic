#include "servo_motor.h"
#include "bsp/bsp.h"
#include "drivers/pwm/pwm.h"
#include "drivers/timer/timer1.h" 

#define PIN_SERVO D9

void Servo_Init(void) {
    // Initializam PWM-ul generic la 50Hz
    PWM_Init(PIN_SERVO, 50); 
    Servo_SeteazaUnghi(0);
}

void Servo_SeteazaUnghi(uint8_t unghi) {
    if (unghi > 180) unghi = 180;
    
    // Convertim unghiul (0-180) in semnal PWM de inalta precizie (1000 - 4800) pe 16 biti
    uint16_t puls = 1000 + ((uint32_t)unghi * 3800) / 180;
    
    // Trimitem semnalul de inalta precizie catre Timer1
    Timer1_SetDutyCycleA(puls);
}