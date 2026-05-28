#include "sensor_ultrasonic.h"
#include "bsp/bsp.h"
#include "drivers/gpio/gpio.h"

#define PIN_TRIG D4
#define PIN_ECHO D5
#define MAX_TIMEOUT 5000 

void Ultrasonic_Init(void) {
    GPIO_Init(PIN_TRIG, GPIO_OUTPUT);
    GPIO_Init(PIN_ECHO, GPIO_INPUT);
}

// Funcție internă, face o singură "poză" cu sunetul
static uint16_t Citire_Singura(void) {
    GPIO_Write(PIN_TRIG, GPIO_HIGH);
    for (volatile uint8_t i = 0; i < 30; i++); 
    GPIO_Write(PIN_TRIG, GPIO_LOW);
    
    uint32_t timeout = MAX_TIMEOUT;
    while (GPIO_Read(PIN_ECHO) == GPIO_LOW && timeout > 0) timeout--;
    if (timeout == 0) return 999; 
    
    uint32_t durata = 0;
    while (GPIO_Read(PIN_ECHO) == GPIO_HIGH && durata < MAX_TIMEOUT) durata++;
    
    if (durata >= MAX_TIMEOUT) return 999; 
    
    return durata / 120;
}

// Aceasta este funcția pe care o apelează radarul tău
uint16_t Ultrasonic_CitesteDistanta(void) {
    
    // TRUC: Facem 2 măsurători ultrarapide pentru a "vâna" obiectele mici
    uint16_t distanta1 = Citire_Singura();
    
    // O foarte scurtă pauză (microsecunde) pentru a nu suprapune ecourile
    for (volatile uint16_t i = 0; i < 2000; i++); 
    
    uint16_t distanta2 = Citire_Singura();
    
    // Dacă ambele au ratat, spunem că e liber
    if (distanta1 == 999 && distanta2 == 999) return 999;
    
    // Dacă prima a ratat foarfeca dar a doua a prins-o, o returnăm pe a doua!
    if (distanta1 == 999) return distanta2;
    if (distanta2 == 999) return distanta1;
    
    // Dacă ambele au lovit ceva, alegem valoarea cea mai apropiată (cel mai sigur e obiectul nostru)
    if (distanta1 < distanta2) {
        return distanta1;
    } else {
        return distanta2;
    }
}