#ifndef ESTADISTICAS_H_INCLUDED
#define ESTADISTICAS_H_INCLUDED

#include <stdint.h>

#define ESTADISTICAS_ARCHIVO  "tetris_stats.bin"
#define MAX_JUGADORES         10
#define MAX_NOMBRE            16

typedef struct {
    char     nombre[MAX_NOMBRE];
    uint32_t mejor_puntaje;
    uint32_t partidas_jugadas;
    uint32_t lineas_totales;
} RegistroJugador;

typedef struct {
    RegistroJugador jugadores[MAX_JUGADORES];
    int             cantidad;
} Estadisticas;

void stats_cargar(Estadisticas* e);

void stats_guardar(const Estadisticas* e);

RegistroJugador* stats_obtener_jugador(Estadisticas* e, const char *nombre);

void stats_actualizar(Estadisticas* e, const char* nombre, uint32_t puntaje, uint32_t lineas);

#endif
