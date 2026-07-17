#include "GBT/gbt.h"
#include "menu.h"
#include "funciones.h"
#include "fuentes.h"
#include "dibujos.h"
#include "config.h"
#include <string.h>

static uint8_t opcion_actual = 1;

void logica_menu(eGBT_Tecla tecla, Partida* partida, uint8_t* estado)
{
    if (tecla == GBTK_ARRIBA)
    {
        opcion_actual--;
        if (opcion_actual < 1)
        {
            opcion_actual = 6;
        }
    }
    if (tecla == GBTK_ABAJO)
    {
        opcion_actual++;
        if (opcion_actual > 6)
        {
            opcion_actual = 1;
        }
    }
    if (tecla == GBTK_ENTER)
    {
        switch (opcion_actual)
        {
            case 1: // Classic
                if((strcmp(partida->nombreJugador, "")) == 0)
                {
                    *estado = 1;
                }
                else
                {
                    gbt_temporizador_reanudar(partida->t_caida);
                    gbt_temporizador_reanudar(partida->t_fijar);
                    *estado = 2;
                }
                break;
            case 2: // Deluxe
                *estado = 3;
                break;
            case 3: // Info
                *estado = 6;
                break;
            case 4: // Estadisticas
                *estado = 7;
                break;
            case 5: // Config
                *estado = 8;
                break;
            case 6: // Salir
                *estado = 9;
                break;
        }
    }
}

void dibujar_menu(TipoResolucion resolucion)
{
    uint8_t color1 = (opcion_actual == 1) ? 2 : 0;
    uint8_t color2 = (opcion_actual == 2) ? 9 : 6;
    uint8_t color3 = (opcion_actual == 3) ? 9 : 6;
    uint8_t color4 = (opcion_actual == 4) ? 9 : 6;
    uint8_t color5 = (opcion_actual == 5) ? 9 : 6;
    uint8_t color6 = (opcion_actual == 6) ? 9 : 6;

    if(resolucion == RES_320x200)
    {
        dibujar_rectangulo(160, 160, 0, 200, 8);

        dibujar_rectangulo(85, 75, 33, 30, 0);
        dibujar_texto_8x16("Tet", 136, 40, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 85,  33, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 85,  53, 3);

        dibujar_rectangulo(85, 65, 68, 30, color1);
        dibujar_texto("Classic", 90, 79, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 85,  68, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 85,  88, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 140, 68, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 140, 88, 3);

        dibujar_rectangulo(85, 65, 103, 65, 0);
        dibujar_elemento((const uint8_t*)logo_unlam, 40, 40, 98, 116, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 85,  103, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 85,  158, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 140, 103, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 140, 158, 3);

        dibujar_rectangulo(160, 75, 33, 30, 6);
        dibujar_texto_8x16("ris", 160, 40, 11);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 33, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 53, 8);

        dibujar_rectangulo(170, 65, 68, 30, color2);
        dibujar_texto("Deluxe", 179, 79, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 68, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 88, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 68, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 88, 8);

        dibujar_rectangulo(170, 30, 103, 30, color3);
        dibujar_elemento((const uint8_t*)exclamacion, 16, 16, 177, 110, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 103, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 123, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 190, 103, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 190, 123, 8);

        dibujar_rectangulo(205, 30, 103, 30, color4);
        dibujar_elemento((const uint8_t*)estadisticas, 16, 16, 212, 110, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 205, 103, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 205, 123, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 103, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 123, 8);

        dibujar_rectangulo(170, 30, 138, 30, color5);
        dibujar_elemento((const uint8_t*)configuracion, 16, 16, 177, 145, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 138, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 158, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 190, 138, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 190, 158, 8);

        dibujar_rectangulo(205, 30, 138, 30, color6);
        dibujar_elemento((const uint8_t*)cerrar, 16, 16, 212, 145, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 205, 138, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 205, 158, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 138, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 158, 8);
    }
    else if(resolucion == RES_640x480)
    {
        dibujar_rectangulo(320, 320, 0, 480, 8);

        dibujar_rectangulo(160, 160, 105, 60, 0);
        dibujar_texto_8x16("Tet", 296, 127, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 160,  105, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 160,  155, 3);

        dibujar_rectangulo(160, 130, 175, 60, color1);
        dibujar_texto_8x16("Classic", 197, 197, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 160, 175, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 160,  225, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 280, 175, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 280, 225, 3);

        dibujar_rectangulo(160, 130, 245, 130, 0);
        dibujar_elemento((const uint8_t*)logo_unlam, 40, 40, 205, 290, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 160,  245, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 160,  365, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 280, 245, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 280, 365, 3);

        dibujar_rectangulo(320, 160, 105, 60, 6);
        dibujar_texto_8x16("ris", 320, 127, 11);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 470, 105, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 470, 155, 8);

        dibujar_rectangulo(350, 130, 175, 60, color2);
        dibujar_texto_8x16("Deluxe", 391, 197, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 350, 175, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 350, 225, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 470, 175, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 470, 225, 8);

        dibujar_rectangulo(350, 60, 245, 60, color3);
        dibujar_elemento((const uint8_t*)exclamacion, 16, 16, 372, 267, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 350, 245, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 350, 295, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 400, 245, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 400, 295, 8);

        dibujar_rectangulo(420, 60, 245, 60, color4);
        dibujar_elemento((const uint8_t*)estadisticas, 16, 16, 442, 267, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 420, 245, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 420, 295, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 470, 245, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 470, 295, 8);

        dibujar_rectangulo(350, 60, 315, 60, color5);
        dibujar_elemento((const uint8_t*)configuracion, 16, 16, 372, 337, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 350, 315, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 350, 365, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 400, 315, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 400, 365, 8);

        dibujar_rectangulo(420, 60, 315, 60, color6);
        dibujar_elemento((const uint8_t*)cerrar, 16, 16, 442, 337, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 420, 315, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 420, 365, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 470, 315, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 470, 365, 8);
    }
}
