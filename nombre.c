#include "GBT/gbt.h"
#include "nombre.h"
#include "fuentes.h"
#include "config.h"
#include <stdio.h>

void logica_nombre(eGBT_Tecla tecla, Partida* partida, uint8_t* estado, TipoVelocidad tipoVelocidad)
{
    static uint8_t indiceLetra = 0;

    if(((tecla >= GBTK_a && tecla <= GBTK_z) || (tecla >= GBTK_0 && tecla <= GBTK_9)) && indiceLetra < 10)
    {
        partida->nombreJugador[indiceLetra] = (char)tecla;
        indiceLetra++;
        partida->nombreJugador[indiceLetra] = '\0';
    }

    if(tecla == GBTK_RETROCESO && (indiceLetra) > 0)
    {
        (indiceLetra)--;
        partida->nombreJugador[indiceLetra] = '\0';
    }

    if((indiceLetra) > 0 && tecla == GBTK_ENTER)
    {
        inicializar_partida(partida, tipoVelocidad);
        indiceLetra = 0;
        *estado = 2;
    }
}

void dibujar_nombre(char* nombreJugador, TipoResolucion resolucion)
{
    if(resolucion == RES_320x200)
    {
        dibujar_texto_8x16("INGRESE SU NOMBRE",92,42,5);
        dibujar_texto(nombreJugador, 120, 96, 5);
    }
    if(resolucion == RES_640x480)
    {
        dibujar_texto_8x16("INGRESE SU NOMBRE", 252, 112, 5);
        dibujar_texto(nombreJugador, 280, 236, 5);
    }
}
