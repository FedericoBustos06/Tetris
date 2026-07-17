#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include "GBT/gbt.h"
#include "pieza.h"
#include "config.h"

#define FILAS_VISIBLES  20
#define FILAS_OCULTAS   4
#define FILAS_TOTAL     (FILAS_VISIBLES + FILAS_OCULTAS)
#define COLUMNAS        10

typedef struct {
    int ancho;
    int alto;
    int8_t **celdas;
} Tablero;

Tablero* crear_tablero(int ancho, int alto);
void     inicializar_tablero(Tablero* t);
void     destruir_tablero(Tablero* t);

bool puede_moverse(const Tablero* t, const Pieza* p, int dx, int dy);

void fijar_pieza(Tablero* t, const Pieza* p);

int  limpiar_lineas(Tablero* t);

bool verificar_derrota(const Tablero* t);

void pintar_tablero(const Tablero* t, TipoResolucion resolucion);

void dibujar_mino(int posX, int posY, uint8_t colorMino, TipoResolucion resolucion);

void pintar_pieza(const Pieza* pieza, int posX, int posY, TipoResolucion resolucion);

void pintar_sombra(const Tablero* t, const Pieza* pieza, uint8_t posX, uint8_t posY, TipoResolucion resolucion);

#endif
