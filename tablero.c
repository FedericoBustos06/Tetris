#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tablero.h"
#include "GBT/gbt.h"
#include "funciones.h"

Tablero* crear_tablero(int ancho, int alto)
{
    Tablero* t = malloc(sizeof(Tablero));
    if (!t) return NULL;

    t->alto  = FILAS_TOTAL;
    t->ancho = COLUMNAS;

    t->celdas = malloc(sizeof(int*) * FILAS_TOTAL);
    if (!t->celdas){
        free(t);
        return NULL;
    }

    int i;
    for (i = 0; i < FILAS_TOTAL; i++) {
        t->celdas[i] = calloc(COLUMNAS, sizeof(int));
        if (!t->celdas[i]){
            int j;
            for (j = 0; j < i; j++)
                free(t->celdas[j]);
            free(t->celdas);
            free(t);
            return NULL;
        }
    }
    return t;
}

void inicializar_tablero(Tablero* t)
{
    int i, j;
    for (i = 0; i < t->alto; i++)
        for (j = 0; j < t->ancho; j++)
            t->celdas[i][j] = 0;
}

void destruir_tablero(Tablero* t)
{
    int i;
    if (!t) return;
    for (i = 0; i < t->alto; i++)
        free(t->celdas[i]);
    free(t->celdas);
    free(t);
}

bool puede_moverse(const Tablero* t, const Pieza* p, int dx, int dy)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (!p->matriz[i][j])
            {
                continue;
            }
            int nx = p->x + j + dx;
            int ny = p->y + i + dy;
            if (nx < 0 || nx >= t->ancho)
            {
                return false;
            }
            if (ny >= t->alto)
            {
                return false;
            }
            if (ny < 0)
            {
                continue;
            }
            if (t->celdas[ny][nx] != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void fijar_pieza(Tablero* t, const Pieza* p)
{
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (!p->matriz[i][j]) continue;
            int nx = p->x + j;
            int ny = p->y + i;
            if (ny >= 0 && ny < t->alto && nx >= 0 && nx < t->ancho)
                t->celdas[ny][nx] = p->color;
        }
    }
}

bool fila_completa(const Tablero* t, int fila)
{
    for (int j = 0; j < t->ancho; j++)
    {
        if (t->celdas[fila][j] == 0)
        {
            return false;
        }
    }
    return true;
}

int limpiar_lineas(Tablero* t)
{
    int eliminadas = 0;
    for (int fila = t->alto - 1; fila > 0; fila--)
    {
        if (fila_completa(t, fila) == false)
        {
           continue;
        }
        int8_t* filaVaciada = t->celdas[fila];
        for (int k = fila; k > 0; k--)
        {
            t->celdas[k] = t->celdas[k - 1];
        }
        memset(filaVaciada, 0, sizeof(int) * t->ancho);
        t->celdas[0] = filaVaciada;
        eliminadas++;
        fila++;
    }
    return eliminadas;
}

bool verificar_derrota(const Tablero* t)
{
    for(int i = 0; i < FILAS_OCULTAS; i++)
    {
        for(int j = 0; j < t->ancho; j++)
        {
            if(t->celdas[i][j] != 0)
            {
                return true;
            }
        }
    }
    return false;
}

void dibujar_mino(int posX, int posY, uint8_t colorMino, TipoResolucion resolucion)
{
    uint8_t tamMino = (resolucion == RES_320x200) ? 8 : 22;
    uint8_t tamBorde = (resolucion == RES_320x200) ? 1 : 3;

    uint8_t colorLuz = (colorMino==40) ? 3 : colorMino + 1;
    uint8_t colorSombra = (colorMino==40) ? 3 : colorMino + 2;

    dibujar_rectangulo(posX + tamBorde, tamMino - tamBorde, posY + tamBorde, tamMino - tamBorde, colorMino);
    dibujar_rectangulo(posX, tamMino, posY, tamBorde, colorLuz);
    dibujar_rectangulo(posX, tamBorde, posY + tamBorde, tamMino - (tamBorde * 2), colorLuz);
    dibujar_rectangulo(posX, tamMino, posY + tamMino - tamBorde, tamBorde, colorSombra);
    dibujar_rectangulo(posX + tamMino - tamBorde, tamBorde, posY + tamBorde, tamMino - (tamBorde * 2), colorSombra);
}

void pintar_tablero(const Tablero* t, TipoResolucion resolucion)
{
    uint8_t posX = (resolucion == RES_320x200) ? 120 : 210;
    uint8_t posY = 20;
    uint8_t tamMino = (resolucion == RES_320x200) ? 8 : 22;

    for(int fila = FILAS_OCULTAS; fila < t->alto; fila++)
    {
        for(int columna = 0; columna < t->ancho; columna++)
        {
            uint8_t color = t->celdas[fila][columna];
            if(color != 0)
            {
                dibujar_mino(posX + (columna * tamMino), posY + ((fila - FILAS_OCULTAS) * tamMino), color, resolucion);
            }
            else
            {
                dibujar_mino(posX + (columna * tamMino), posY + ((fila - FILAS_OCULTAS) * tamMino), 7, resolucion);
            }
        }
    }
}

void pintar_pieza(const Pieza* pieza, int posX, int posY, TipoResolucion resolucion)
{
    uint8_t tamMino = (resolucion == RES_320x200) ? 8 : 22;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(!pieza->matriz[i][j])
            {
                continue;
            }
            int8_t fila = (int8_t)pieza->y + i;
            int8_t columna = (int8_t)pieza->x + j;
            if(fila < FILAS_OCULTAS)
            {
                continue;
            }
            dibujar_mino(posX + (columna * tamMino), posY + ((fila - FILAS_OCULTAS) * tamMino), pieza->color, resolucion);
        }
    }
}

void pintar_sombra(const Tablero* t, const Pieza* pieza, uint8_t posX, uint8_t posY, TipoResolucion resolucion)
{
    Pieza sombra = *pieza;
    while(puede_moverse(t, &sombra, 0, 1))
    {
        sombra.y++;
    }
    sombra.color = 40;
    pintar_pieza(&sombra, posX, posY, resolucion);
}
