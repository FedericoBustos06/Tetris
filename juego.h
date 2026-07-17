#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include <stdint.h>
#include "GBT/gbt.h"
#include "tablero.h"
#include "pieza.h"
#include "config.h"
#include "estadisticas.h"

typedef struct {
    Tablero* tablero;
    Pieza actual;
    Pieza siguientes[5];
    char nombreJugador[16];
    uint32_t puntaje;
    uint16_t lineasCompletadas;
    uint32_t piezas_fijadas;
    uint32_t vel_ms;
    uint32_t nivel;
    uint8_t fijar;
    tGBT_Temporizador* t_caida;
    tGBT_Temporizador* t_fijar;
} Partida;

void logica_classic(eGBT_Tecla tecla, Partida* p, uint8_t* estado);
void dibujar_classic(Partida partida, TipoResolucion resolucion);
void logica_pausa(eGBT_Tecla tecla, Partida* partida, uint8_t* estado, TipoVelocidad velocidad);
void dibujar_pausa(Partida partida, TipoResolucion resolucion);
void logica_derrota(eGBT_Tecla tecla, Partida* partida, uint8_t* estado, TipoVelocidad velocidad);
void dibujar_derrota(Partida p, TipoResolucion resolucion);
void inicializar_partida(Partida* partida, TipoVelocidad velocidadInicial);

#endif // JUEGO_H_INCLUDED
