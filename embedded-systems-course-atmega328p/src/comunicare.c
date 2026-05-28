#include "comunicare.h"
#include "drivers/usart/usart.h" 
#include <stdio.h>
#include <string.h> 

void Comunicare_Init(void) {
    USART_Init(16000000UL, 9600); 
}

void Comunicare_TrimiteDateRadar(uint8_t unghi, uint16_t distanta) {
    char buffer[32]; 
    // Format simplu: "unghi,distanta"
    sprintf(buffer, "%d,%d\n", unghi, distanta);
    
    // Trimitem tot mesajul cu lungimea sa (strlen)
    USART_Transmit(buffer, strlen(buffer)); 
}