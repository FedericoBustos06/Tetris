#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pieza.h"

static const int plantillas[CANT_TIPOS_PIEZA][4][4] = {
    /* I */
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* O */
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* T */
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* L */
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* J */
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* Z */
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    },
    /* S */
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }
};

#define COLOR_PIEZA_BASE 13

Pieza crear_pieza(int tipo, int ancho_tablero){
    Pieza p;
    p.tipo = tipo;
    p.color = color_de_tipo(tipo);

    p.x = ancho_tablero / 2 - 2;

    p.y = 0;
    memcpy(p.matriz, plantillas[tipo], sizeof(p.matriz));
    return p;
}

Pieza spawn_random(int ancho_tablero){
    return crear_pieza(rand() % CANT_TIPOS_PIEZA, ancho_tablero);
}

void rotar_pieza_derecha(Pieza* p){
    int tmp[4][4];
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tmp[j][3 - i] = p->matriz[i][j];
        }
    }
    memcpy(p->matriz, tmp, sizeof(tmp));
}

void rotar_pieza_izquierda(Pieza* p){
    int tmp[4][4];
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tmp[3 - j][i] = p->matriz[i][j];
        }
    }
    memcpy(p->matriz, tmp, sizeof(tmp));
}

uint8_t color_de_tipo(int tipo){
    return (uint8_t)(COLOR_PIEZA_BASE + tipo);
}
