#include "GBT/gbt.h"
#include "config.h"
#include "string.h"
#include "funciones.h"
#include "dibujos.h"
#include "fuentes.h"

#include <stdio.h>
#include <string.h>


void logica_config(eGBT_Tecla tecla, uint8_t *opcionSeleccionadaConfig, const char **opcion1, const char **opcion2, const char **opcion3, Config *cfg, uint8_t *estado)
{
    if(tecla == GBTK_ARRIBA)
    {
        (*opcionSeleccionadaConfig)--;
        if (*opcionSeleccionadaConfig < 1)
        {
            *opcionSeleccionadaConfig = 3;
        }
    }
    if(tecla == GBTK_ABAJO)
    {
        (*opcionSeleccionadaConfig)++;
        if(*opcionSeleccionadaConfig > 3)
        {
            *opcionSeleccionadaConfig = 1;
        }
    }
    if(tecla == GBTK_IZQUIERDA || tecla == GBTK_DERECHA)
    {
      uint8_t hubo_cambio = 0;
        if(*opcionSeleccionadaConfig == 1)
        {
            if(strcmp(*opcion1, "<Metalica>") == 0)
            {
                *opcion1 = "  <Pastel>";
                cfg->paleta = 1;
            } else {
                *opcion1 = "<Metalica>";
                cfg->paleta = 0;
            }
            hubo_cambio = 1;
        }
        if(*opcionSeleccionadaConfig == 2)
        {
            int nuevo_ancho;
            int nuevo_alto;
            int escala;

            if(strcmp(*opcion2, "<640x480>") == 0)
            {
                *opcion2 = "<320x200>";
                cfg->resolucion = 1;
                nuevo_ancho = 320;
                nuevo_alto = 200;
                escala = 4;
            } else {
                *opcion2 = "<640x480>";
                cfg->resolucion = 2;
                nuevo_ancho = 640;
                nuevo_alto = 480;
                escala = 2;
            }

            gbt_destruir_ventana();
            gbt_crear_ventana("Tetris", nuevo_ancho, nuevo_alto, escala);
            extern tGBT_ColorRGB paletaCGA[];
            gbt_aplicar_paleta(paletaCGA, 20, GBT_FORMATO_888);
            hubo_cambio = 1;
        }
        if(*opcionSeleccionadaConfig == 3)
        {
            if(strcmp(*opcion3, "<Alta>") == 0)
            {
                *opcion3 = "<Baja>";
                cfg->velocidad_ms = 1000;
            } else {
                *opcion3 = "<Alta>";
                cfg->velocidad_ms = 500;
            }
            hubo_cambio = 1;
        }
        if(hubo_cambio)
        {
            config_guardar(cfg);
        }
    }
    if (tecla == GBTK_ESCAPE)
    {
        *estado=0;
    }
}

void dibujar_config(int alto_ventana, uint8_t *opcionSeleccionadaConfig, const char *opcion1, const char *opcion2, const char *opcion3)
{
    if(alto_ventana==200)
    {
        dibujar_rectangulo(40, 240, 20, 40, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 40, 20, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 270,50, 3);

        dibujar_rectangulo(40, 240, 80, 40, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 40, 80, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 270, 110, 3);

        dibujar_rectangulo(40, 240, 140, 40, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 40, 140, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 270, 170, 3);

        switch(*opcionSeleccionadaConfig)
        {
            case 1:
                dibujar_texto("Paleta", 50, 36, 0);
                dibujar_texto(opcion1, 190, 36, 12);
                dibujar_texto("Resolucion", 50, 96, 0);
                dibujar_texto(opcion2, 198, 96, 0);
                dibujar_texto("Velocidad de caida", 50, 156, 0);
                dibujar_texto(opcion3, 222, 156, 0);
                break;
            case 2:
                dibujar_texto("Paleta", 50, 36, 0);
                dibujar_texto(opcion1, 190, 36, 0);
                dibujar_texto("Resolucion", 50, 96, 0);
                dibujar_texto(opcion2, 198, 96, 12);
                dibujar_texto("Velocidad de caida", 50, 156, 0);
                dibujar_texto(opcion3, 222, 156, 0);
                break;
            case 3:
                dibujar_texto("Paleta", 50, 36, 0);
                dibujar_texto(opcion1, 190, 36, 0);
                dibujar_texto("Resolucion", 50, 96, 0);
                dibujar_texto(opcion2, 198, 96, 0);
                dibujar_texto("Velocidad de caida", 50, 156, 0);
                dibujar_texto(opcion3, 222, 156, 12);
                break;
        }
    }
    if(alto_ventana==480)
    {
        dibujar_rectangulo(80, 480, 80, 80, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 80, 80, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 550, 150, 3);

        dibujar_rectangulo(80, 480, 200, 80, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 80, 200, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 550, 270, 3);

        dibujar_rectangulo(80, 480, 320, 80, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 80, 320, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 550, 390, 3);

        switch(*opcionSeleccionadaConfig)
        {
            case 1:
                dibujar_texto_8x16("Paleta", 100, 112, 0);
                dibujar_texto_8x16(opcion1, 460, 112, 12);
                dibujar_texto_8x16("Resolucion", 100, 232, 0);
                dibujar_texto_8x16(opcion2, 468, 232, 0);
                dibujar_texto_8x16("Velocidad de caida", 100, 352, 0);
                dibujar_texto_8x16(opcion3, 492, 352, 0);
                break;
            case 2:
                dibujar_texto_8x16("Paleta", 100, 112, 0);
                dibujar_texto_8x16(opcion1, 460, 112, 0);
                dibujar_texto_8x16("Resolucion", 100, 232, 0);
                dibujar_texto_8x16(opcion2, 468, 232, 12);
                dibujar_texto_8x16("Velocidad de caida", 100, 352, 0);
                dibujar_texto_8x16(opcion3, 492, 352, 0);
                break;
            case 3:
                dibujar_texto_8x16("Paleta", 100, 112, 0);
                dibujar_texto_8x16(opcion1, 460, 112, 0);
                dibujar_texto_8x16("Resolucion", 100, 232, 0);
                dibujar_texto_8x16(opcion2, 468, 232, 0);
                dibujar_texto_8x16("Velocidad de caida", 100, 352, 0);
                dibujar_texto_8x16(opcion3, 492, 352, 12);
                break;
        }
    }
}

void config_default(Config* c){
    c->resolucion  = 1;
    c->velocidad_ms = VELOCIDAD_INICIAL_MS;
    c->paleta      = 0;
}

void config_cargar(Config* c){
    FILE* f = fopen(CONFIG_ARCHIVO, "rb");
    if (!f) {
        config_default(c);
        return;
    }
    if (fread(c, sizeof(Config), 1, f) != 1)
        config_default(c);
    fclose(f);
}

void config_guardar(const Config* c){
    FILE* f = fopen(CONFIG_ARCHIVO, "wb");
    if (!f) return;
    fwrite(c, sizeof(Config), 1, f);
    fclose(f);
}
