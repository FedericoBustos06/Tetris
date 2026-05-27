#include <stdlib.h>
#include <string.h>
#include "tablero.h"
#include "GBT/gbt.h"

Tablero* crear_tablero(int ancho, int alto){
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

void inicializar_tablero(Tablero* t){
    int i, j;
    for (i = 0; i < t->alto; i++)
        for (j = 0; j < t->ancho; j++)
            t->celdas[i][j] = 0;
}

void destruir_tablero(Tablero* t){
    int i;
    if (!t) return;
    for (i = 0; i < t->alto; i++)
        free(t->celdas[i]);
    free(t->celdas);
    free(t);
}

int pieza_es_valida(const Tablero* t, const Pieza* p, int dx, int dy){
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (!p->matriz[i][j]) continue;

            int nx = p->x + j + dx;
            int ny = p->y + i + dy;

            if (nx < 0 || nx >= t->ancho) return 0; //por si se excede de bordes x
            if (ny >= t->alto)            return 0;

            if (ny < 0) continue;

            if (t->celdas[ny][nx] != 0)   return 0;
        }
    }
    return 1;
}

void fijar_pieza(Tablero* t, const Pieza* p){
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

static int fila_completa(const Tablero* t, int fila){
    int j;
    for (j = 0; j < t->ancho; j++)
        if (t->celdas[fila][j] == 0) return 0;
    return 1;
}

int limpiar_lineas(Tablero* t){
    int eliminadas = 0;
    int fila;

    for (fila = t->alto - 1; fila >= 0; fila--) {
        if (!fila_completa(t, fila)) continue;

        int* fila_vaciada = t->celdas[fila];// guardamos el puntero de la fila vaciada

        //desplazamos los punteros desde la fila eliminada hasta arriba
        int k;
        for (k = fila; k > 0; k--)
            t->celdas[k] = t->celdas[k - 1];

        //limpiamos la fila reciclada y la ponemos arriba
        memset(fila_vaciada, 0, sizeof(int) * t->ancho);
        t->celdas[0] = fila_vaciada;

        eliminadas++;

        fila++;
    }
    return eliminadas;
}

int tablero_game_over(const Tablero* t)
{
    int i, j;
    for (i = 0; i < FILAS_OCULTAS; i++)
        for (j = 0; j < t->ancho; j++)
            if (t->celdas[i][j] != 0) return 1;
    return 0;
}

//RENDER

static void dibujar_bloque(int px, int py, int tam, uint8_t color)
{
    int dx, dy;
    for (dy = 0; dy < tam; dy++)
        for (dx = 0; dx < tam; dx++)
            gbt_dibujar_pixel(px + dx, py + dy, color);
}

//dibuja el borde de un bloque generando como efecto 3D
static void dibujar_bloque_borde(int px, int py, int tam, uint8_t color, uint8_t borde){
    int dx, dy;
    //relleno principal
    for (dy = 1; dy < tam - 1; dy++)
        for (dx = 1; dx < tam - 1; dx++)
            gbt_dibujar_pixel(px + dx, py + dy, color);
    //claro arriba e izquierda
    for (dx = 0; dx < tam; dx++) {
        gbt_dibujar_pixel(px + dx, py,        borde);
        gbt_dibujar_pixel(px,      py + dx,   borde);
    }
    //oscuro abajo y derecha
    for (dx = 0; dx < tam; dx++) {
        gbt_dibujar_pixel(px + dx,       py + tam - 1, 6);
        gbt_dibujar_pixel(px + tam - 1,  py + dx,      6);
    }
}

void pintar_tablero(const Tablero* t, int origen_x, int origen_y, int tam_bloque){
    int fila, col;

    for (fila = FILAS_OCULTAS; fila < t->alto; fila++) {//pintamos a partir de las visibles
        for (col = 0; col < t->ancho; col++) {
            int px = origen_x + col * tam_bloque;
            int py = origen_y + (fila - FILAS_OCULTAS) * tam_bloque;
            uint8_t color = (uint8_t)t->celdas[fila][col];
            if (color != 0) {
                dibujar_bloque_borde(px, py, tam_bloque, color, 0);
            } else {
                dibujar_bloque(px, py, tam_bloque, 7);//la vacia la pintamos de gris oscuro
            }
        }
    }

    int x, y;
    int bx = origen_x - 1;
    int by = origen_y - 1;
    int bw = t->ancho * tam_bloque + 2;
    int bh = FILAS_VISIBLES * tam_bloque + 2;
    for (x = bx; x < bx + bw; x++) {
        gbt_dibujar_pixel(x, by, 3);
        gbt_dibujar_pixel(x, by + bh, 3);
    }
    for (y = by; y <= by + bh; y++) {
        gbt_dibujar_pixel(bx, y, 3);
        gbt_dibujar_pixel(bx + bw, y, 3);
    }
}

void pintar_pieza(const Pieza* p, int origen_x, int origen_y, int tam_bloque){
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (!p->matriz[i][j]) continue;
            int ny = p->y + i;
            if (ny < FILAS_OCULTAS) continue;
            int px = origen_x + (p->x + j) * tam_bloque;
            int py = origen_y + (ny - FILAS_OCULTAS) * tam_bloque;
            dibujar_bloque_borde(px, py, tam_bloque, p->color, 0);
        }
    }
}

void pintar_sombra(const Tablero* t, const Pieza* p,int origen_x, int origen_y, int tam_bloque){

    Pieza sombra = *p;
    while (pieza_es_valida(t, &sombra, 0, 1))
        sombra.y++;

    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (!sombra.matriz[i][j]) continue;
            int ny = sombra.y + i;
            if (ny < FILAS_OCULTAS) continue;
            int px = origen_x + (sombra.x + j) * tam_bloque;
            int py = origen_y + (ny - FILAS_OCULTAS) * tam_bloque;

            int dx, dy;
            for (dy = 0; dy < tam_bloque; dy++)
                for (dx = 0; dx < tam_bloque; dx++)
                    if (dy == 0 || dy == tam_bloque-1 || dx == 0 || dx == tam_bloque-1)
                        gbt_dibujar_pixel(px + dx, py + dy, 10);
        }
    }
}
