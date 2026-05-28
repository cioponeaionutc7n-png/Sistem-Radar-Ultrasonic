#ifndef COMUNICARE_H
#define COMUNICARE_H

#include <stdint.h>

void Comunicare_Init(void);
void Comunicare_TrimiteDateRadar(uint8_t unghi, uint16_t distanta);

#endif // COMUNICARE_H