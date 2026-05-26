#ifndef DIBUJOS_H_INCLUDED
#define DIBUJOS_H_INCLUDED

#include <stdint.h>

extern const uint8_t logo_unlam[40][40];
extern const uint8_t exclamacion[16][16];
extern const uint8_t estadisticas[16][16];
extern const uint8_t configuracion[16][16];
extern const uint8_t cerrar[16][16];
extern const uint8_t borde_tl[10][10];
extern const uint8_t borde_tr[10][10];
extern const uint8_t borde_ll[10][10];
extern const uint8_t borde_lr[10][10];

void dibujar_elemento(const uint8_t *matriz, uint16_t ancho, uint16_t alto, uint16_t posX, uint16_t posY, uint8_t color_indice);

#endif // DIBUJOS_H_INCLUDED
