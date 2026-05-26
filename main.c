#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include "fuentes.h"
#include "dibujos.h"
#define CANT_COLORES 13

#include <time.h>

tGBT_ColorRGB paletaCGA[CANT_COLORES] = {
    {255, 255, 255}, // 0:   Paleta clara 1 #FFFFFF
    {242, 242, 247}, // 1:   Paleta clara 2 #F2F2F7
    {224, 224, 224}, // 2:   Paleta clara 3 #E5E5EA
    {209, 209, 214}, // 3:   Paleta clara 4 #D1D1D6
    {58, 58, 60}, // 4:   Paleta clara 5 #3A3A3C
    {28, 28, 30}, // 5:   Paleta clara 6 #1C1C1E
    {13, 13, 13}, // 6:   Paleta oscura 1 #0D0D0D
    {26, 26, 26}, // 7:   Paleta oscura 2 #1A1A1A
    {44, 44, 46}, // 8:   Paleta oscura 3 #2C2C2E
    {58, 58, 60}, // 9:   Paleta oscura 4 #3A3A3C
    {142, 142, 147}, // 10:  Paleta oscura 5 #8E8E93
    {229, 229, 234}, // 11:  Paleta oscura 6 #E5E5EA

};

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int anchoVentana = 320;
    int altoVentana = 200;
    uint8_t escala = 1;

    int* tablero[20];
    for (uint8_t i = 0; i < 20; i++)
    {
        tablero[i] = (int*)malloc(10 * sizeof(int));
    }

    int nivel_fijo[20][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,0,0,1,1,0,0},
    {0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,1,1,1},
    {0,0,0,1,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0}
    };
    for (int fila = 0; fila < 20; fila++) {
        for (int col = 0; col < 10; col++) {
            tablero[fila][col] = nivel_fijo[fila][col];
        }
    }

    uint8_t opcion_seleccionada = 1;
    uint8_t menu = 0;
    uint8_t color= 0;

    char nombreJugador[16] = "";
    uint8_t indiceLetra= 0;

    if (argc == 3) {
        uint8_t resolucion = atoi(argv[1]);
        escala = atoi(argv[2]);

        if (resolucion == 2) {
            anchoVentana = 640;
            altoVentana = 480;
        }
    } else {
        printf("Aviso: Iniciando con valores por defecto.\n");
        printf("Para configurar use: %s <1(CGA) o 2(VGA)> <escala>\n", argv[0]);
    }

    uint16_t tamanioBloque = (altoVentana - 40) / 20;
    uint8_t a = 0;
    uint8_t b = 0;
    uint8_t c = 0;

    gbt_iniciar();
    gbt_crear_ventana("Mi Tetris", anchoVentana, altoVentana, escala);
    gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888);


    uint8_t corriendo = 1;


    while (corriendo)
    {
        gbt_borrar_backbuffer(3);
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
        if(menu==0){
            if(tecla== GBTK_ARRIBA)
            {
                opcion_seleccionada--;
                if (opcion_seleccionada < 1)
                {
                    opcion_seleccionada = 6;
                }
            }
            if(tecla== GBTK_ABAJO)
            {
                opcion_seleccionada++;
                if (opcion_seleccionada > 6)
                {
                    opcion_seleccionada = 1;
                }
            }
            if(tecla== GBTK_ENTER)
            {
                switch(opcion_seleccionada)
                {
                    case 1:
                        menu++;
                        break;
                    case 6:
                        corriendo = 0;
                        break;
                }
            }
            for(int x=(anchoVentana/2); x<=anchoVentana; x++)
            {
                for(int y=0; y<=altoVentana; y++)
                {
                    gbt_dibujar_pixel(x, y, 8);
                }
            }


            if(altoVentana==200)
            {
                for(int x=85; x<160; x++)
                {
                    for(int y=33; y<63; y++)
                    {
                        gbt_dibujar_pixel(x, y, 0);
                    }
                }
                dibujar_texto_8x16("Tet",136, 40, 5);
                dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 85, 33, 3);
                dibujar_elemento((const uint8_t *)borde_ll, 10, 10, 85, 53, 3);
                if(opcion_seleccionada==1)
                {
                        color=2;
                }
                else
                {
                        color=0;
                }
                for(int x=85; x<150; x++)
                {
                    for(int y=68; y<98; y++)
                    {
                        gbt_dibujar_pixel(x, y, color);
                    }
                }
                dibujar_texto("Classic", 90, 79, 5);
                dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 85, 68, 3);
                dibujar_elemento((const uint8_t *)borde_ll, 10, 10, 85, 88, 3);
                dibujar_elemento((const uint8_t *)borde_tr, 10, 10, 140, 68, 3);
                dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 140, 88, 3);
                for(int x=85; x<150; x++)
                {
                    for(int y=103; y<168; y++)
                    {
                        gbt_dibujar_pixel(x, y, 0);
                    }
                }
                dibujar_elemento((const uint8_t *)logo_unlam, 40, 40, 98, 116, 5);
                dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 85, 103, 3);
                dibujar_elemento((const uint8_t *)borde_ll, 10, 10, 85, 158, 3);
                dibujar_elemento((const uint8_t *)borde_tr, 10, 10, 140, 103, 3);
                dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 140, 158, 3);
                for(int x=160; x<235; x++)
                {
                    for(int y=33; y<63; y++)
                    {
                        gbt_dibujar_pixel(x, y, 6);
                    }
                }
                dibujar_texto_8x16("ris",160,40,11);
                dibujar_elemento((const uint8_t *)borde_tr, 10, 10, 225, 33, 8);
                dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 225, 53, 8);
                if(opcion_seleccionada==2)
                {
                        color=9;
                }
                else
                {
                        color=6;
                }
                for(int x=170; x<235; x++)
                {
                    for(int y=68; y<98; y++)
                    {
                        gbt_dibujar_pixel(x, y, color);
                    }
                }
                dibujar_texto("Deluxe", 179, 79, 11);
                dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 170, 68, 8);
                dibujar_elemento((const uint8_t *)borde_ll, 10, 10, 170, 88, 8);
                dibujar_elemento((const uint8_t *)borde_tr, 10, 10, 225, 68, 8);
                dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 225, 88, 8);
                if(opcion_seleccionada==3)
                {
                        color=9;
                }
                else
                {
                        color=6;
                }
                for(int x=170; x<200; x++)
                {
                    for(int y=103; y<133; y++)
                    {
                        gbt_dibujar_pixel(x, y, color);
                    }
                }
                dibujar_elemento((const uint8_t *)exclamacion, 16, 16, 177, 110, 11);
                dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 170, 103, 8);
                dibujar_elemento((const uint8_t *)borde_ll, 10, 10, 170, 123, 8);
                dibujar_elemento((const uint8_t *)borde_tr, 10, 10, 190, 103, 8);
                dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 190, 123, 8);
                if(opcion_seleccionada==4)
                {
                        color=9;
                }
                else
                {
                        color=6;
                }
                for(int x=205; x<235; x++)
                {
                    for(int y=103; y<133; y++)
                    {
                        gbt_dibujar_pixel(x, y, color);
                    }
                }
                dibujar_elemento((const uint8_t *)estadisticas, 16, 16, 212, 110, 11);
                dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 205, 103, 8);
                dibujar_elemento((const uint8_t *)borde_ll, 10, 10, 205, 123, 8);
                dibujar_elemento((const uint8_t *)borde_tr, 10, 10, 225, 103, 8);
                dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 225, 123, 8);
                if(opcion_seleccionada==5)
                {
                        color=9;
                }
                else
                {
                        color=6;
                }
                for(int x=170; x<200; x++)
                {
                    for(int y=138; y<168; y++)
                    {
                        gbt_dibujar_pixel(x, y, color);
                    }
                }
                dibujar_elemento((const uint8_t *)configuracion, 16, 16, 177, 145, 11);
                dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 170, 138, 8);
                dibujar_elemento((const uint8_t *)borde_ll, 10, 10, 170, 158, 8);
                dibujar_elemento((const uint8_t *)borde_tr, 10, 10, 190, 138, 8);
                dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 190, 158, 8);
                if(opcion_seleccionada==6)
                {
                        color=9;
                }
                else
                {
                        color=6;
                }
                for(int x=205; x<235; x++)
                {
                    for(int y=138; y<168; y++)
                    {
                        gbt_dibujar_pixel(x, y, color);
                    }
                }
                dibujar_elemento((const uint8_t *)cerrar, 16, 16, 212, 145, 11);
                dibujar_elemento((const uint8_t *)borde_tl, 10, 10, 205, 138, 8);
                dibujar_elemento((const uint8_t *)borde_ll, 10, 10, 205, 158, 8);
                dibujar_elemento((const uint8_t *)borde_tr, 10, 10, 225, 138, 8);
                dibujar_elemento((const uint8_t *)borde_lr, 10, 10, 225, 158, 8);
            }
        }
        else if(menu==1){
            dibujar_texto("Ingrese su nombre",((anchoVentana/2)-80),40,5);

            if ((tecla >= GBTK_a && tecla <= GBTK_z || tecla >= GBTK_0 && tecla <= GBTK_9) && indiceLetra < 15)
            {
                nombreJugador[indiceLetra] = (char)tecla;
                indiceLetra++;
            }
            if(tecla == GBTK_RETROCESO)
            {
                indiceLetra--;
                nombreJugador[indiceLetra] = '\0';
            }
            if(nombreJugador!="" &&(tecla == GBTK_ENTER))
            {
                menu++;
            }

            dibujar_texto(nombreJugador, ((anchoVentana/2)-80), 88, 5);
        }
        else if(menu==2){
            int inicio_x = (anchoVentana / 2) - (tamanioBloque * 5);
            int inicio_y = 20;

            for (int fila = 0; fila < 20; fila++)
            {
                for (int col = 0; col < 10; col++)
                {
                    uint8_t color_bloque = tablero[fila][col];
                    int pos_x = inicio_x + (col * tamanioBloque);
                    int pos_y = inicio_y + (fila * tamanioBloque);
                    for (int j = 0; j < tamanioBloque; j++)
                    {
                        for (int k = 0; k < tamanioBloque; k++)
                        {
                            gbt_dibujar_pixel(pos_x + k, pos_y + j, color_bloque);
                        }
                    }
                }
            }
        }
        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
