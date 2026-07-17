#ifndef NOMBRE_H_INCLUDED
#define NOMBRE_H_INCLUDED

#include "config.h"
#include "juego.h"

void logica_nombre(eGBT_Tecla tecla, Partida* partida, uint8_t* estado, TipoVelocidad tipoVelocidad);
void dibujar_nombre(char* nombreJugador, TipoResolucion resolucion);

#endif // NOMBRE_H_INCLUDED
