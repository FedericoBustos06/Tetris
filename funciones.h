#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "config.h"

void dibujar_rectangulo(int x, int ancho, int y, int altura, int color);
void inicializar_parametros(int argc, char** argv, Config *cfg);
void crear_ventana(Config cfg);

#endif // FUNCIONES_H_INCLUDED
