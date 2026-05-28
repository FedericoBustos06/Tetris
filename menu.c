#include "GBT/gbt.h"
#include "menu.h"
#include "funciones.h"
#include "fuentes.h"
#include "dibujos.h"
#include "config.h"

void logica_menu(eGBT_Tecla tecla, uint8_t *opcion_menu, uint8_t *estado, uint8_t *corriendo)
{
    if (tecla == GBTK_ARRIBA)
    {
        (*opcion_menu)--;
        if (*opcion_menu < 1)
        {
            *opcion_menu = 6;
        }
    }
    if (tecla == GBTK_ABAJO)
    {
        (*opcion_menu)++;
        if (*opcion_menu > 6)
        {
            *opcion_menu = 1;
        }
    }
    if (tecla == GBTK_ENTER)
    {
        switch (*opcion_menu)
        {
            case 1:
                *estado = 2;
                break;
            case 3:
                *estado = 7;
                break;
            case 4:
                *estado = 6;
                break;
            case 5:
                *estado = 1;
                break;
            case 6:
                *corriendo = 0;
                break;
            default:
                break;
        }
    }
}

void dibujar_menu(int ancho, int alto, uint8_t opcion)
{
    int x, y;
    uint8_t color;

    for(x = ancho/2; x < ancho; x++)
    {
        for (y = 0; y < alto; y++)
        {
            gbt_dibujar_pixel(x, y, 8);
        }
    }

    if(ancho == 320)
    {
        dibujar_rectangulo(85, 75, 33, 30, 0);
        dibujar_texto_8x16("Tet", 136, 40, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 85,  33, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 85,  53, 3);

        color = (opcion == 1) ? 2 : 0;
        dibujar_rectangulo(85, 65, 68, 30, color);
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

        color = (opcion == 2) ? 9 : 6;
        dibujar_rectangulo(170, 65, 68, 30, color);
        dibujar_texto("Deluxe", 179, 79, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 68, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 88, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 68, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 88, 8);

        color = (opcion == 3) ? 9 : 6;
        dibujar_rectangulo(170, 30, 103, 30, color);
        dibujar_elemento((const uint8_t*)exclamacion, 16, 16, 177, 110, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 103, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 123, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 190, 103, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 190, 123, 8);

        color = (opcion == 4) ? 9 : 6;
        dibujar_rectangulo(205, 30, 103, 30, color);
        dibujar_elemento((const uint8_t*)estadisticas, 16, 16, 212, 110, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 205, 103, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 205, 123, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 103, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 123, 8);

        color = (opcion == 5) ? 9 : 6;
        dibujar_rectangulo(170, 30, 138, 30, color);
        dibujar_elemento((const uint8_t*)configuracion, 16, 16, 177, 145, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 138, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 158, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 190, 138, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 190, 158, 8);

        color = (opcion == 6) ? 9 : 6;
        dibujar_rectangulo(205, 30, 138, 30, color);
        dibujar_elemento((const uint8_t*)cerrar, 16, 16, 212, 145, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 205, 138, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 205, 158, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 138, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 158, 8);
    }
    if(ancho == 640)
    {
        dibujar_rectangulo(160, 160, 105, 60, 0);
        dibujar_texto_8x16("Tet", 296, 127, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 160,  105, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 160,  155, 3);

        color = (opcion == 1) ? 2 : 0;
        dibujar_rectangulo(160, 130, 175, 60, color);
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

        color = (opcion == 2) ? 9 : 6;
        dibujar_rectangulo(350, 130, 175, 60, color);
        dibujar_texto_8x16("Deluxe", 391, 197, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 350, 175, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 350, 225, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 470, 175, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 470, 225, 8);

        color = (opcion == 3) ? 9 : 6;
        dibujar_rectangulo(350, 60, 245, 60, color);
        dibujar_elemento((const uint8_t*)exclamacion, 16, 16, 372, 267, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 350, 245, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 350, 295, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 400, 245, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 400, 295, 8);

        color = (opcion == 4) ? 9 : 6;
        dibujar_rectangulo(420, 60, 245, 60, color);
        dibujar_elemento((const uint8_t*)estadisticas, 16, 16, 442, 267, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 420, 245, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 420, 295, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 470, 245, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 470, 295, 8);

        color = (opcion == 5) ? 9 : 6;
        dibujar_rectangulo(350, 60, 315, 60, color);
        dibujar_elemento((const uint8_t*)configuracion, 16, 16, 372, 337, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 350, 315, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 350, 365, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 400, 315, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 400, 365, 8);

        color = (opcion == 6) ? 9 : 6;
        dibujar_rectangulo(420, 60, 315, 60, color);
        dibujar_elemento((const uint8_t*)cerrar, 16, 16, 442, 337, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 420, 315, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 420, 365, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 470, 315, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 470, 365, 8);
    }
}
