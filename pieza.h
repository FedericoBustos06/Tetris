#ifndef PIEZA_H_INCLUDED
#define PIEZA_H_INCLUDED

#include <stdint.h>

#define CANT_TIPOS_PIEZA 7

typedef struct {
    int matriz[4][4];
    int x, y;
    int tipo;
    uint8_t color;
} Pieza;

Pieza crear_pieza(int tipo, int ancho_tablero);

Pieza spawn_random(int ancho_tablero);

void rotar_pieza_derecha(Pieza* p);

void rotar_pieza_izquierda(Pieza* p);

uint8_t color_de_tipo(int tipo);

#endif
