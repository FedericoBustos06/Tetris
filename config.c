#include "GBT/gbt.h"
#include "config.h"
#include "string.h"
#include "funciones.h"
#include "dibujos.h"
#include "fuentes.h"
#include <stdio.h>
#include <string.h>

static uint8_t opcion_actual = 1;

void logica_config(eGBT_Tecla tecla, Config* cfg, uint8_t* estado)
{
    if(tecla == GBTK_ARRIBA)
    {
        opcion_actual--;
        if(opcion_actual < 1)
        {
            opcion_actual = 3;
        }
    }
    else if(tecla == GBTK_ABAJO)
    {
        opcion_actual++;
        if(opcion_actual > 3)
        {
            opcion_actual = 1;
        }
    }
    else if(tecla == GBTK_IZQUIERDA || tecla == GBTK_DERECHA)
    {
        uint8_t hubo_cambio = 0;

        if(opcion_actual == 1)
        {
            if(cfg->paleta == PALETA_METALICA)
            {
                cfg->paleta = PALETA_PASTEL;
            }
            else
            {
                cfg->paleta = PALETA_METALICA;
            }
            gbt_destruir_ventana();
            crear_ventana(*cfg);
            hubo_cambio = 1;
        }
        else if(opcion_actual == 2)
        {
            if(cfg->resolucion == RES_640x480)
            {
                cfg->resolucion = RES_320x200;
                cfg->escala = 4;
            }
            else
            {
                cfg->resolucion = RES_640x480;
                cfg->escala = 2;
            }
            gbt_destruir_ventana();
            crear_ventana(*cfg);
            hubo_cambio = 1;
        }
        else if(opcion_actual == 3)
        {
            if(cfg->velocidad == VEL_ALTA)
            {
                cfg->velocidad = VEL_BAJA;
            }
            else
            {
                cfg->velocidad = VEL_ALTA;
            };

            hubo_cambio = 1;
        }
        if(hubo_cambio)
        {
            config_guardar(cfg);
        }
    }
    else if (tecla == GBTK_ESCAPE)
    {
        *estado = 0;
        opcion_actual = 1;
    }
}

void inicializar_configuracion(Config* cfg)
{
    FILE* f = fopen(CONFIG_ARCHIVO, "rb");
    if (!f)
    {
        cfg->paleta     = PALETA_METALICA;
        cfg->resolucion = RES_320x200;
        cfg->velocidad  = VEL_BAJA;
        cfg->escala     = 4;
        return;
    }

    if (fread(cfg, sizeof(Config), 1, f) != 1)
    {
        cfg->paleta     = PALETA_METALICA;
        cfg->resolucion = RES_320x200;
        cfg->velocidad  = VEL_BAJA;
        cfg->escala     = 4;
    }
    fclose(f);
}

void config_guardar(const Config* cfg)
{
    FILE* f = fopen(CONFIG_ARCHIVO, "wb");

    if (!f) return;

    fwrite(cfg, sizeof(Config), 1, f);
    fclose(f);
}

void dibujar_config(Config cfg)
{
    uint8_t color1 = (opcion_actual == 1) ? 12 : 0;
    uint8_t color2 = (opcion_actual == 2) ? 12 : 0;
    uint8_t color3 = (opcion_actual == 3) ? 12 : 0;

    const char* txt_paleta = (cfg.paleta == PALETA_METALICA) ? "<Metalica>" : "  <Pastel>";
    const char* txt_res    = (cfg.resolucion == RES_320x200) ? "<320x200>" : "<640x480>";
    const char* txt_vel    = (cfg.velocidad == VEL_ALTA) ? "<Alta>" : "<Baja>";

    if(cfg.resolucion == RES_320x200)
    {
        dibujar_rectangulo(40, 240, 20, 40, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 40, 20, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 270,50, 3);
        dibujar_texto("Paleta", 50, 36, 0);
        dibujar_texto(txt_paleta, 190, 36, color1);

        dibujar_rectangulo(40, 240, 80, 40, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 40, 80, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 270, 110, 3);
        dibujar_texto("Resolucion", 50, 96, 0);
        dibujar_texto(txt_res, 198, 96, color2);

        dibujar_rectangulo(40, 240, 140, 40, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 40, 140, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 270, 170, 3);
        dibujar_texto("Velocidad de caida", 50, 156, 0);
        dibujar_texto(txt_vel, 222, 156, color3);
    }
    else if(cfg.resolucion == RES_640x480)
    {
        dibujar_rectangulo(80, 480, 80, 80, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 80, 80, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 550, 150, 3);
        dibujar_texto_8x16("Paleta", 100, 112, 0);
        dibujar_texto_8x16(txt_paleta, 460, 112, color1);

        dibujar_rectangulo(80, 480, 200, 80, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 80, 200, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 550, 270, 3);
        dibujar_texto_8x16("Resolucion", 100, 232, 0);
        dibujar_texto_8x16(txt_res, 468, 232, color2);

        dibujar_rectangulo(80, 480, 320, 80, 8);
        dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 80, 320, 3);
        dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 550, 390, 3);
        dibujar_texto_8x16("Velocidad de caida", 100, 352, 0);
        dibujar_texto_8x16(txt_vel, 492, 352, color3);
    }
}
