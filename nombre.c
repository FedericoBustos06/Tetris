#include "GBT/gbt.h"
#include "nombre.h"
#include "fuentes.h"


void logica_nombre(eGBT_Tecla tecla, uint8_t *indiceLetra, char *nombreJugador, uint8_t *estado)
{
    if (((tecla >= GBTK_a && tecla <= GBTK_z) || (tecla >= GBTK_0 && tecla <= GBTK_9)) && (*indiceLetra) < 15)
    {
        nombreJugador[*indiceLetra] = (char)tecla;
        (*indiceLetra)++;
        nombreJugador[*indiceLetra] = '\0';
    }

    if(tecla == GBTK_RETROCESO && (*indiceLetra) > 0)
    {
        (*indiceLetra)--;
        nombreJugador[*indiceLetra] = '\0';
    }

    if((*indiceLetra) > 0 && tecla == GBTK_ENTER)
    {
        *estado=3;
    }
}
void dibujar_nombre(int ancho, char *nombreJugador)
{
    if(ancho==320)
    {
        dibujar_texto_8x16("INGRESE SU NOMBRE",92,42,5);
        dibujar_texto(nombreJugador, 96, 92, 5);
    }
    if(ancho==640)
    {
        dibujar_texto_8x16("INGRESE SU NOMBRE", 252, 112, 5);
        dibujar_texto(nombreJugador, 256, 232, 5);
    }
}
