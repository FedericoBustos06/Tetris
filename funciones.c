#include "GBT/gbt.h"
#include "stdio.h"
#include "funciones.h"
#include "config.h"

void dibujar_rectangulo(int x, int ancho, int y, int altura, int color)
{
    for(int j=x; j<ancho+x; j++)
    {
        for(int k=y; k<altura+y; k++)
        {
            gbt_dibujar_pixel(j, k, color);
        }
    }
}

void inicializar_parametros(int argc, char** argv, Config* cfg)
{
    if(argc == 1)
    {
        printf("Iniciando con parametros por defecto...\n");
        printf("Puedes usar parametros: %s <resolucion> <escala>\n", argv[0]);
        return;
    }

    if(argc != 3)
    {
        printf("Error: Cantidad de parametros incorrecta.\n");
        printf("Uso de parametros: <ruta> <resolucion> <escala>\n");
        exit(1);
    }

    int opcion_res = atoi(argv[1]);
    int escala = atoi(argv[2]);

    if(opcion_res != 1 && opcion_res != 2)
    {
        printf("Error: Introduce una resolucion valida (1 para 320x200, 2 para 640x480).\n");
        exit(1);
    }
    if(opcion_res == 1)
    {
        if(escala > 0 && escala <= 4)
        {
            cfg->resolucion = RES_320x200;
            cfg->escala     = escala;
        }
        else
        {
            printf("Error: Para la resolucion 1 (320x200), la escala debe estar entre 1 y 4.\n");
            exit(1);
        }
    }
    else if(opcion_res == 2)
    {
        if(escala > 0 && escala <= 2)
        {
            cfg->resolucion = RES_640x480;
            cfg->escala     = escala;
        }
        else
        {
            printf("Error: Para la resolucion 2 (640x480), la escala debe estar entre 1 y 2.\n");
            exit(1);
        }
    }
}

void crear_ventana(Config cfg)
{
    if(cfg.resolucion == RES_320x200)
    {
        gbt_crear_ventana("Tetris", 320, 200, cfg.escala);
        if(cfg.paleta == PALETA_METALICA)
        {
            gbt_aplicar_paleta(paletaMetalicaCGA, CANT_COLORES, GBT_FORMATO_888);
        }
        else if(cfg.paleta == PALETA_PASTEL)
        {
            gbt_aplicar_paleta(paletaPastelCGA, CANT_COLORES, GBT_FORMATO_888);
        }
    }
    if(cfg.resolucion == RES_640x480)
    {
        gbt_crear_ventana("Tetris", 640, 480, cfg.escala);
        if(cfg.paleta == PALETA_METALICA)
        {
            gbt_aplicar_paleta(paletaMetalicaVGA, CANT_COLORES, GBT_FORMATO_666);
        }
        else if(cfg.paleta == PALETA_PASTEL)
        {
            gbt_aplicar_paleta(paletaPastelVGA, CANT_COLORES, GBT_FORMATO_666);
        }
    }
}
