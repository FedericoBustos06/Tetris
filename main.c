#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GBT/gbt.h"
#include "fuentes.h"
#include "dibujos.h"
#include "tablero.h"
#include "pieza.h"
#include "config.h"
#include "estadisticas.h"
#include "menu.h"
#include "nombre.h"
#include "funciones.h"
#include "juego.h"

#define CANT_COLORES 34

tGBT_ColorRGB paletaMetalicaCGA[CANT_COLORES] =
{
    {255, 255, 255}, // 0:   Paleta clara 1 #FFFFFF
    {242, 242, 247}, // 1:   Paleta clara 2 #F2F2F7
    {224, 224, 224}, // 2:   Paleta clara 3 #E5E5EA
    {209, 209, 214}, // 3:   Paleta clara 4 #D1D1D6
    {58, 58, 60},    // 4:   Paleta clara 5 #3A3A3C
    {28, 28, 30},    // 5:   Paleta clara 6 #1C1C1E
    {13, 13, 13},    // 6:   Paleta oscura 1 #0D0D0D
    {26, 26, 26},    // 7:   Paleta oscura 2 #1A1A1A
    {44, 44, 46},    // 8:   Paleta oscura 3 #2C2C2E
    {58, 58, 60},    // 9:   Paleta oscura 4 #3A3A3C
    {142, 142, 147}, // 10:  Paleta oscura 5 #8E8E93
    {229, 229, 234}, // 11:  Paleta oscura 6 #E5E5EA
    {212, 175, 55},  // 12:  Amarillo opciones #D4AF37

    // I Celeste
    {113, 166, 210}, // 13:  I Celeste Metalico #71A6D2
    {203, 225, 242}, // 14:  I Celeste Luz #CBE1F2
    {57, 102, 143},  // 15:  I Celeste Sombra #39668F

    // J Azul
    {33, 76, 143},   // 16:  J Azul Metalico #214C8F
    {101, 141, 224}, // 17:  J Azul Luz #658DE0
    {16, 40, 77},    // 18:  J Azul Sombra #10284D

    // L Naranja
    {200, 106, 45},  // 19:  L Naranja Metalico #C86A2D
    {229, 161, 115}, // 20:  L Naranja Luz #E5A173
    {122, 58, 19},   // 21:  L Naranja Sombra #7A3A13

    // O Amarillo
    {212, 175, 55},  // 22:  O Amarillo Metalico #D4AF37
    {245, 224, 149}, // 23:  O Amarillo Luz #F5E095
    {138, 109, 25},  // 24:  O Amarillo Sombra #8A6D19

    // S Verde
    {40, 140, 90},   // 25:  S Verde Metalico #288C5A
    {112, 201, 154}, // 26:  S Verde Luz #BB92DB
    {19, 77, 46},    // 27:  S Verde Sombra #47285C

    // T Violeta
    {133, 84, 166},  // 28:  T Violeta Metalico #8554A6
    {185, 130, 215}, // 29:  T Violeta Luz #B982D7
    {85, 45, 110},   // 30:  T Violeta Sombra #552D6E

    // Z Rojo
    {184, 34, 48},   // 31:  Z Rojo Metalico #B82230
    {230, 101, 114}, // 32:  Z Rojo Luz #E66572
    {97, 15, 24},    // 33:  Z Rojo Sombra #610F18
};

tGBT_ColorRGB paletaPastelCGA[CANT_COLORES] =
{
    {255, 255, 255}, // 0:   Paleta clara 1 #FFFFFF
    {242, 242, 247}, // 1:   Paleta clara 2 #F2F2F7
    {224, 224, 224}, // 2:   Paleta clara 3 #E5E5EA
    {209, 209, 214}, // 3:   Paleta clara 4 #D1D1D6
    {58, 58, 60},    // 4:   Paleta clara 5 #3A3A3C
    {28, 28, 30},    // 5:   Paleta clara 6 #1C1C1E
    {13, 13, 13},    // 6:   Paleta oscura 1 #0D0D0D
    {26, 26, 26},    // 7:   Paleta oscura 2 #1A1A1A
    {44, 44, 46},    // 8:   Paleta oscura 3 #2C2C2E
    {58, 58, 60},    // 9:   Paleta oscura 4 #3A3A3C
    {142, 142, 147}, // 10:  Paleta oscura 5 #8E8E93
    {229, 229, 234}, // 11:  Paleta oscura 6 #E5E5EA
    {212, 175, 55},  // 12:  Amarillo opciones #D4AF37

    // I Celeste
    {174, 198, 207}, // 13:  I Celeste Pastel #AEC6CF
    {214, 232, 237}, // 14:  I Celeste Luz #D6E8ED
    {132, 163, 176}, // 15:  I Celeste Sombra #84A3B0

    // J Azul
    {163, 184, 224}, // 16:  J Azul Pastel #A3B8E0
    {209, 222, 239}, // 17:  J Azul Luz #D1DEEF
    {126, 151, 196}, // 18:  J Azul Sombra #7E97C4

    // L Naranja
    {250, 200, 152}, // 19:  L Naranja Pastel #FAC898
    {253, 226, 201}, // 20:  L Naranja Luz #FDE2C9
    {214, 159, 113}, // 21:  L Naranja Sombra #D69F71

    // O Amarillo
    {253, 253, 150}, // 22:  O Amarillo Pastel #FDFD96
    {254, 254, 206}, // 23:  O Amarillo Luz #FEFECE
    {214, 214, 122}, // 24:  O Amarillo Sombra #D6D67A

    // S Verde
    {162, 228, 184}, // 25:  S Verde Pastel #A2E4B8
    {212, 244, 223}, // 26:  S Verde Luz #D4F4DF
    {123, 191, 149}, // 27:  S Verde Sombra #7BBF95

    // T Violeta
    {208, 167, 227}, // 28:  T Violeta Pastel #D0A7E3
    {233, 210, 242}, // 29:  T Violeta Luz #E9D2F2
    {171, 129, 190}, // 30:  T Violeta Sombra #AB81BE

    // Z Rojo
    {255, 154, 162}, // 31:  Z Rojo Pastel #FF9AA2
    {255, 205, 210}, // 32:  Z Rojo Luz #FFCDD2
    {216, 119, 128}, // 33:  Z Rojo Sombra #D87780
};

tGBT_ColorRGB paletaMetalicaVGA[CANT_COLORES] =
{
    {63, 63, 63}, // 0:   Paleta clara 1 #FFFFFF
    {60, 60, 61}, // 1:   Paleta clara 2 #F2F2F7
    {56, 56, 56}, // 2:   Paleta clara 3 #E5E5EA
    {52, 52, 53}, // 3:   Paleta clara 4 #D1D1D6
    {14, 14, 15}, // 4:   Paleta clara 5 #3A3A3C
    {7, 7, 7},    // 5:   Paleta clara 6 #1C1C1E
    {3, 3, 3},    // 6:   Paleta oscura 1 #0D0D0D
    {6, 6, 6},    // 7:   Paleta oscura 2 #1A1A1A
    {11, 11, 11}, // 8:   Paleta oscura 3 #2C2C2E
    {14, 14, 15}, // 9:   Paleta oscura 4 #3A3A3C
    {35, 35, 36}, // 10:  Paleta oscura 5 #8E8E93
    {57, 57, 58}, // 11:  Paleta oscura 6 #E5E5EA
    {53, 43, 13}, // 12:  Amarillo opciones #D4AF37

    // I Celeste
    {28, 41, 52}, // 13:  I Celeste Metalico #71A6D2
    {50, 56, 60}, // 14:  I Celeste Luz #CBE1F2
    {14, 25, 35}, // 15:  I Celeste Sombra #39668F

    // J Azul
    {8, 19, 35},  // 16:  J Azul Metalico #214C8F
    {25, 35, 56}, // 17:  J Azul Luz #658DE0
    {4, 10, 19},  // 18:  J Azul Sombra #10284D

    // L Naranja
    {50, 26, 11}, // 19:  L Naranja Metalico #C86A2D
    {57, 40, 28}, // 20:  L Naranja Luz #E5A173
    {30, 14, 4},  // 21:  L Naranja Sombra #7A3A13

    // O Amarillo
    {53, 43, 13}, // 22:  O Amarillo Metalico #D4AF37
    {61, 56, 37}, // 23:  O Amarillo Luz #F5E095
    {34, 27, 6},  // 24:  O Amarillo Sombra #8A6D19

    // S Verde
    {10, 35, 22}, // 25:  S Verde Metalico #288C5A
    {28, 50, 38}, // 26:  S Verde Luz #BB92DB
    {4, 19, 11},  // 27:  S Verde Sombra #47285C

    // T Violeta
    {33, 21, 41}, // 28:  T Violeta Metalico #8554A6
    {46, 32, 53}, // 29:  T Violeta Luz #B982D7
    {21, 11, 27}, // 30:  T Violeta Sombra #552D6E

    // Z Rojo
    {46, 8, 12},  // 31:  Z Rojo Metalico #B82230
    {57, 25, 28}, // 32:  Z Rojo Luz #E66572
    {24, 3, 6},   // 33:  Z Rojo Sombra #610F18
};

tGBT_ColorRGB paletaPastelVGA[CANT_COLORES] =
{
    {63, 63, 63}, // 0:   Paleta clara 1 #FFFFFF
    {60, 60, 61}, // 1:   Paleta clara 2 #F2F2F7
    {56, 56, 56}, // 2:   Paleta clara 3 #E5E5EA
    {52, 52, 53}, // 3:   Paleta clara 4 #D1D1D6
    {14, 14, 15}, // 4:   Paleta clara 5 #3A3A3C
    {7, 7, 7},    // 5:   Paleta clara 6 #1C1C1E
    {3, 3, 3},    // 6:   Paleta oscura 1 #0D0D0D
    {6, 6, 6},    // 7:   Paleta oscura 2 #1A1A1A
    {11, 11, 11}, // 8:   Paleta oscura 3 #2C2C2E
    {14, 14, 15}, // 9:   Paleta oscura 4 #3A3A3C
    {35, 35, 36}, // 10:  Paleta oscura 5 #8E8E93
    {57, 57, 58}, // 11:  Paleta oscura 6 #E5E5EA
    {53, 43, 13}, // 12:  Amarillo opciones #D4AF37

    // I Celeste
    {43, 49, 51}, // 13:  I Celeste Pastel #AEC6CF
    {53, 58, 59}, // 14:  I Celeste Luz #D6E8ED
    {33, 40, 44}, // 15:  I Celeste Sombra #84A3B0

    // J Azul
    {40, 46, 56}, // 16:  J Azul Pastel #A3B8E0
    {52, 55, 59}, // 17:  J Azul Luz #D1DEEF
    {31, 37, 49}, // 18:  J Azul Sombra #7E97C4

    // L Naranja
    {62, 50, 38}, // 19:  L Naranja Pastel #FAC898
    {63, 56, 50}, // 20:  L Naranja Luz #FDE2C9
    {53, 39, 28}, // 21:  L Naranja Sombra #D69F71

    // O Amarillo
    {63, 63, 37}, // 22:  O Amarillo Pastel #FDFD96
    {63, 63, 51}, // 23:  O Amarillo Luz #FEFECE
    {53, 53, 30}, // 24:  O Amarillo Sombra #D6D67A

    // S Verde
    {40, 57, 46}, // 25:  S Verde Pastel #A2E4B8
    {53, 61, 55}, // 26:  S Verde Luz #D4F4DF
    {30, 47, 37}, // 27:  S Verde Sombra #7BBF95

    // T Violeta
    {52, 41, 56}, // 28:  T Violeta Pastel #D0A7E3
    {58, 52, 60}, // 29:  T Violeta Luz #E9D2F2
    {42, 32, 47}, // 30:  T Violeta Sombra #AB81BE

    // Z Rojo
    {63, 38, 40}, // 31:  Z Rojo Pastel #FF9AA2
    {63, 51, 52}, // 32:  Z Rojo Luz #FFCDD2
    {54, 29, 32}, // 33:  Z Rojo Sombra #D87780
};

int main(int argc, char* argv[])
{
    srand(time(NULL));
    uint8_t estado = 0;
    uint8_t corriendo = 1;
    Config cfg;
    Partida partida = {0};
    inicializar_configuracion(&cfg);
    inicializar_parametros(argc, argv, &cfg);

    gbt_iniciar();
    crear_ventana(cfg);
    while(corriendo)
    {
        gbt_borrar_backbuffer(3);
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
        switch(estado)
        {
            case 0: // Menu
                logica_menu(tecla, &partida, &estado);
                dibujar_menu(cfg.resolucion);
                break;
            case 1: // Pedir nombre
                logica_nombre(tecla, &partida, &estado, cfg.velocidad);
                dibujar_nombre(partida.nombreJugador, cfg.resolucion);
                break;
            case 2: // Classic
                logica_classic(tecla, &partida, &estado);
                dibujar_classic(partida, cfg.resolucion);
                break;
            case 3: // Deluxe
                 if (tecla == GBTK_ESCAPE)
                    estado = 0;
                break;
            case 4: // Pausa
                logica_pausa(tecla, &partida, &estado, cfg.velocidad);
                dibujar_pausa(partida, cfg.resolucion);
                break;
            case 5: // Derrota
                logica_derrota(tecla, &partida, &estado, cfg.velocidad);
                dibujar_derrota(partida, cfg.resolucion);
                break;
            case 6: // Info
                if (tecla == GBTK_ESCAPE)
                    estado = 0;
                break;
            case 7: // Estadisticas
                if (tecla == GBTK_ESCAPE)
                    estado = 0;
                break;
            case 8: // Config
                logica_config(tecla, &cfg, &estado);
                dibujar_config(cfg);
                break;
            case 9: // Salir
                corriendo = 0;
                break;
        }
        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
