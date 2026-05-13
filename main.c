#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"

int main(int argc, char* argv[])
{
    int anchoVentana = 320;
    int altoVentana = 200;
    int escala = 1;

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
    uint8_t corriendo = 1;
    while (corriendo) {}
    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
