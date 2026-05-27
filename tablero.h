#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include <stdint.h>
#include "GBT/gbt.h"
#include "pieza.h"

#define FILAS_VISIBLES  20
#define FILAS_OCULTAS   4
#define FILAS_TOTAL     (FILAS_VISIBLES + FILAS_OCULTAS)
#define COLUMNAS        10

typedef struct {
    int ancho;
    int alto;
    int **celdas;
} Tablero;

Tablero* crear_tablero(int ancho, int alto);
void     inicializar_tablero(Tablero* t);
void     destruir_tablero(Tablero* t);

int  pieza_es_valida(const Tablero* t, const Pieza* p, int dx, int dy);

void fijar_pieza(Tablero* t, const Pieza* p);

int  limpiar_lineas(Tablero* t);

int  tablero_game_over(const Tablero* t); // Devuelve 1 si alguna celda de las filas ocultas esta ocupada

void pintar_tablero(const Tablero* t, int origen_x, int origen_y, int tam_bloque);

void pintar_pieza(const Pieza* p, int origen_x, int origen_y, int tam_bloque);

void pintar_sombra(const Tablero* t, const Pieza* p,int origen_x, int origen_y, int tam_bloque);

#endif
