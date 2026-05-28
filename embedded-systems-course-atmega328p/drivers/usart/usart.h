#ifndef USART_H
#define USART_H

#include <stdint.h>

#define USART_Init_Default() USART_Init(16000000, 57600)
#define MAX_SIZE_RECEIVE_USART 50
#define TIMEOUT_USART 1000

void USART_Init(unsigned long fosc, unsigned int baud);
void USART_Transmit(void* data, uint8_t size);
int USART_Receive(void* data);

#endif // USART_H