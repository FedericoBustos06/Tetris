#ifndef FUENTES_H_INCLUDED
#define FUENTES_H_INCLUDED

#include <stdint.h>
#include "GBT/gbt.h"

void dibujar_caracter(char c, uint16_t oX, uint16_t oY, uint8_t color_indice);
void dibujar_texto(const char* texto, uint16_t oX, uint16_t oY, uint8_t color_indice);

void dibujar_caracter_8x16(char c, uint16_t oX, uint16_t oY, uint8_t color_indice);
void dibujar_texto_8x16(const char* texto, uint16_t oX, uint16_t oY, uint8_t color_indice);

#endif

