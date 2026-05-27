#include <stdio.h>
#include <string.h>
#include "estadisticas.h"

void stats_cargar(Estadisticas* e){
    e->cantidad = 0;
    FILE* f = fopen(ESTADISTICAS_ARCHIVO, "rb");
    if (!f) return;
    fread(e, sizeof(Estadisticas), 1, f);
    fclose(f);
}

void stats_guardar(const Estadisticas* e){
    FILE* f = fopen(ESTADISTICAS_ARCHIVO, "wb");
    if (!f) return;
    fwrite(e, sizeof(Estadisticas), 1, f);
    fclose(f);
}

RegistroJugador* stats_obtener_jugador(Estadisticas* e, const char* nombre){
    int i;

    for (i = 0; i < e->cantidad; i++) {                 //busca si existe
        if (strncmp(e->jugadores[i].nombre, nombre, MAX_NOMBRE) == 0)
            return &e->jugadores[i];
    }

    if (e->cantidad >= MAX_JUGADORES) return NULL;      //sino lo crea
    RegistroJugador* r = &e->jugadores[e->cantidad];
    strncpy(r->nombre, nombre, MAX_NOMBRE - 1);
    r->nombre[MAX_NOMBRE - 1] = '\0';
    r->mejor_puntaje    = 0;
    r->partidas_jugadas = 0;
    r->lineas_totales   = 0;
    e->cantidad++;
    return r;
}

void stats_actualizar(Estadisticas* e, const char* nombre, uint32_t puntaje, uint32_t lineas){
    RegistroJugador* r = stats_obtener_jugador(e, nombre);
    if (!r) return;
    r->partidas_jugadas++;
    r->lineas_totales += lineas;
    if (puntaje > r->mejor_puntaje)
        r->mejor_puntaje = puntaje;
    stats_guardar(e);
}
