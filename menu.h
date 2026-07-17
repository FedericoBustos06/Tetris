#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "config.h"
#include "juego.h"

void logica_menu(eGBT_Tecla tecla, Partida* partida, uint8_t* estado);
void dibujar_menu(TipoResolucion resolucion);

#endif // MENU_H_INCLUDED
