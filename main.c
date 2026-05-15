#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include "fuentes.h"
#define CANT_COLORES 16

tGBT_ColorRGB paletaCGA[CANT_COLORES] = {
    {13, 13, 13}, // 0:   Paleta oscura 1
    {44, 44, 46}, // 1:   Paleta oscura 3
    {229, 229, 234}, // 2:   Paleta oscura 8
    {242, 242, 247}, // 3:   Paleta clara 2
    {209, 209, 214}, // 4:   Paleta clara 4
    {28, 28, 30}, // 5:   Paleta clara 8
    {0xAA, 0x55, 0x00}, // 6:   Marron
    {0xAA, 0xAA, 0xAA}, // 7:   Gris claro
    {0x55, 0x55, 0x55}, // 8:   Gris oscuro
    {0x55, 0x55, 0xFF}, // 9:   Azul brillante
    {0x55, 0xFF, 0x55}, // 10:  Verde brillante
    {0x55, 0xFF, 0xFF}, // 11:  Cian brillante
    {0xFF, 0x55, 0x55}, // 12:  Rojo brillante
    {0xFF, 0x55, 0xFF}, // 13:  Magenta brillante
    {0xFF, 0xFF, 0x55}, // 14:  Amarillo
    {0xFF, 0xFF, 0xFF}  // 15:  Usado como transparente por GBT
};

int main(int argc, char* argv[])
{
    int anchoVentana = 320;
    int altoVentana = 200;
    int escala = 1;

    uint8_t opcion_seleccionada = 0;
    uint8_t menu = 0;

    char nombreJugador[16] = "";
    uint16_t indiceLetra= 0;

    gbt_iniciar();

    if (argc == 3) {

        int resolucion = atoi(argv[1]);
        escala = atoi(argv[2]);

        if (resolucion == 2) {
            anchoVentana = 640;
            altoVentana = 480;
        }
    } else {
        printf("Aviso: Iniciando con valores por defecto.\n");
        printf("Para configurar use: %s <1(CGA) o 2(VGA)> <escala>\n", argv[0]);
    }

    gbt_crear_ventana("Mi Tetris", anchoVentana, altoVentana, escala);
    gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888);
    uint8_t corriendo = 1;

    while (corriendo)
    {
        gbt_borrar_backbuffer(0);
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        if(menu==0)
        {
            if(tecla== GBTK_ABAJO||tecla== GBTK_ARRIBA )
            {
                opcion_seleccionada++;
                if (opcion_seleccionada > 1) {
                opcion_seleccionada = 0;
                }
            }
            if(opcion_seleccionada==0)
            {
                dibujar_caracter('<',((anchoVentana/2)+80),88,12);
                if(tecla== GBTK_ENTER)
                {
                    menu++;
                }
            }
            if(opcion_seleccionada==1)
            {
                dibujar_caracter('<',((anchoVentana/2)+80),122,12);
                if(tecla== GBTK_ENTER)
                {
                    corriendo = 0;
                }
            }
            dibujar_texto_8x16("TETRIS",((anchoVentana/2)-30),50,12);
            for(int x=(anchoVentana)/2 - 50; x<((anchoVentana/2)+50); x++)
            {
                for(int y=80;y< 104;y++){
                    gbt_dibujar_pixel(x, y, 1);
                }
            }
            dibujar_texto("Classic",((anchoVentana/2)-30),88,12);
            for(int x=(anchoVentana)/2 - 50; x<((anchoVentana/2)+50); x++)
            {
                for(int y=114;y< 138;y++)
                {
                    gbt_dibujar_pixel(x, y, 1);
                }
            }
            dibujar_texto("Salir",((anchoVentana/2)-30),122,12);
        }
        else if(menu==1){
            dibujar_texto("Ingrese su nombre",((anchoVentana/2)-80),40,12);

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

            dibujar_texto(nombreJugador, ((anchoVentana/2)-80), 88, 11);
        }
        else if(menu==2){

        }


        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
