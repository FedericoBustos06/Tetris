/*
 * Apellido: Melillo, Franco Marcelo
 * DNI: 42014467
 * Usuario: https://github.com/francomelillo-sys
 * Entrega: Si
 *
 * Apellido: Bustos, Federico
 * DNI: 46952382
 * Usuario: https://github.com/FedericoBustos06
 * Entrega: Si
 */

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
#define CANT_COLORES 35

tGBT_ColorRGB paletaCGA[CANT_COLORES] =
{
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
    {212, 175, 55}, // 12:  Amarillo opciones #D4AF37
    {113, 166, 210}, // 13:  I Celeste Metalico #71A6D2
    {33, 76, 143},   // 14:  J Azul Metalico #214C8F
    {200, 106, 45},  // 15:  L Naranja Metalico #C86A2D
    {212, 175, 55},  // 16:  O Amarillo Metalico #D4AF37
    {40, 140, 90},   // 17:  S Verde Metalico #288C5A
    {133, 84, 166},  // 18:  T Violeta Metalico #8554A6
    {184, 34, 48},   // 19:  Z Rojo Metalico #B82230
    {174, 228, 255}, // 20:  I Celeste base #AEE4FF
    {181, 192, 255}, // 21:  J Azul base #B5C0FF
    {255, 208, 168}, // 22:  L Naranja base #FFD0A8
    {255, 240, 168}, // 23:  O Amarillo base #FFF0A8
    {181, 234, 215}, // 24:  S Verde base #B5EAD7
    {218, 181, 255}, // 25:  T Morado base #DAB5FF
    {255, 181, 181}, // 26:  Z Rojo base #FFB5B5
};

static const int PUNTOS_LINEAS[5] = {0, 100, 300, 500, 800};

static uint32_t puntaje_por_lineas(int lineas, uint32_t vel_ms){
    if (lineas < 1 || lineas > 4) return 0;
    double mult = (double)VELOCIDAD_INICIAL_MS / (double)vel_ms; //al aumentar velocidad ganas mas puntos, ejemplo 1000ms/900ms = mult y (puntos x mult) se suman a puntos
    if (mult < 1.0) mult = 1.0;
    return (uint32_t)(PUNTOS_LINEAS[lineas] * mult);
}

static uint32_t nueva_velocidad(uint32_t vel_inicial, int piezas){
    double v = (double)vel_inicial;
    int i;
    for (i = 0; i < piezas / 10; i++)
        v *= 0.97;
    if (v < 50.0) v = 50.0;
    return (uint32_t)v;
}

//HUD
static void dibujar_hud(int px, uint32_t puntaje, uint32_t lineas, uint32_t vel_ms, const Pieza* sig, int tam){
    char buf[24];
    int y = 20;

    dibujar_texto("PUNTAJE", px, y, 0);  y += 10;
    sprintf(buf, "%lu", (unsigned long)puntaje);
    dibujar_texto(buf, px, y, 1);      y += 20;

    dibujar_texto("LINEAS", px, y, 0);  y += 10;
    sprintf(buf, "%lu", (unsigned long)lineas);
    dibujar_texto(buf, px, y, 1);      y += 20;

    dibujar_texto("VELOCIDAD", px, y, 0);  y += 10;
    sprintf(buf, "%lums", (unsigned long)vel_ms);
    dibujar_texto(buf, px, y, 1);      y += 20;

    dibujar_texto("NEXT", px, y, 0);   y += 10; //pongo next porque queda mejor
    if (sig) {
        int i, j, d, k;
        int mini = (tam > 5) ? 5 : tam; //preview de siguiente bloque en chiquito
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++) {
                if (!sig->matriz[i][j]) continue;
                for (d = 0; d < mini; d++)
                    for (k = 0; k < mini; k++)
                        gbt_dibujar_pixel(px + j*mini + k, y + i*mini + d, sig->color);
            }
    }
}

//pantalla de pausa
static void pantalla_pausa(int ancho, int alto){
    dibujar_texto_8x16("PAUSA", ancho/2 - 40, alto/2 - 10, 12);
    dibujar_texto("P: continuar", ancho/2 - 72, alto/2 + 12, 12);
    dibujar_texto("ESC: menu", ancho/2 - 72, alto/2 + 24, 12);
}

//pantalla game over
static void pantalla_game_over(int ancho, int alto, uint32_t puntaje, uint32_t lineas){
    char buf[32];
    dibujar_texto_8x16("GAME OVER", ancho/2 - 72, alto/2 - 20, 18);
    sprintf(buf, "Puntaje: %lu", (unsigned long)puntaje);
    dibujar_texto(buf, ancho/2 - 48, alto/2 + 4,  0);
    sprintf(buf, "Lineas:  %lu", (unsigned long)lineas);
    dibujar_texto(buf, ancho/2 - 48, alto/2 + 16, 0);
    dibujar_texto("ENTER: jugar de nuevo", ancho/2 - 64, alto/2 + 30, 3);
    dibujar_texto("ESC:   volver al menu", ancho/2 - 64, alto/2 + 42, 3);
}
static void dibujar_estadisticas(int ancho, int alto, const Estadisticas* stats) {
    char buf[64];
    int y = 40;

    int x_nombre = ancho / 2 - 120;
    int x_pts    = ancho / 2 - 10;
    int x_pj     = ancho / 2 + 70;

    dibujar_texto_8x16("ESTADISTICAS", ancho / 2 - 48, 15, 12);

    dibujar_texto("NOMBRE", x_nombre, y, 3);
    dibujar_texto("PUNTAJE", x_pts, y, 3);
    dibujar_texto("JUGADAS", x_pj, y, 3);
    y += 20;

    if (stats->cantidad == 0) {
        dibujar_texto("NO HAY DATOS TODAVIA", ancho / 2 - 80, y + 20, 10);
    }
    int i;
    for (i = 0; i < stats->cantidad; i++) {
        const RegistroJugador* r = &stats->jugadores[i];

        dibujar_texto(r->nombre, x_nombre, y, 0);

        sprintf(buf, "%lu", (unsigned long)r->mejor_puntaje);
        dibujar_texto(buf, x_pts, y, 0);

        sprintf(buf, "%lu", (unsigned long)r->partidas_jugadas);
        dibujar_texto(buf, x_pj, y, 0);

        y += 15;
    }
    dibujar_texto("ESC: volver al menu", ancho / 2 - 76, alto - 20, 4);
}

#define INICIAR_PARTIDA() do {                                              \
    inicializar_tablero(tablero);                                           \
    puntaje = 0; lineas_total = 0; piezas_fijas = 0;                       \
    vel_ms  = cfg.velocidad_ms;                                             \
    fijar   = 0;                                                            \
    actual    = spawn_random(tablero->ancho);                               \
    siguiente = spawn_random(tablero->ancho);                               \
    gbt_temporizador_destruir(t_caida);                                     \
    gbt_temporizador_destruir(t_fijar);                                     \
    t_caida = gbt_temporizador_crear((double)vel_ms / 1000.0);             \
    t_fijar = gbt_temporizador_crear((double)vel_ms / 2000.0);             \
} while(0)

//MAIN

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));

    Config cfg;
    config_cargar(&cfg);

    uint16_t ancho_ventana;
    uint16_t alto_ventana;
    uint8_t escala;

    const char *opcion1 = "<Metalica>";
    const char *opcion2;
    const char *opcion3 = "<Alta>";

    if (argc == 3) {
        uint8_t escala = (uint8_t)atoi(argv[2]);
        if(atoi(argv[1]) == 1)
        {
            cfg.resolucion = 1;
            opcion2 = "<320x200>";
        }
        else
        {
            cfg.resolucion = 2;
            opcion2 = "<640x480>";
        }
    } else if (argc != 1)
    {
        printf("Uso: %s [<1=CGA|2=VGA> <escala>]\n", argv[0]);
    }

    if(cfg.resolucion == 1)
    {
        ancho_ventana = 320;
        alto_ventana = 200;
        escala = 4;
    }
    if(cfg.resolucion == 2)
    {
        ancho_ventana = 640;
        alto_ventana = 480;
        escala = 2;
    }

     uint8_t indiceLetra= 0;
     char nombreJugador[16] = "";
     uint8_t opcionSeleccionadaConfig = 1;

    int tam;
    int org_x;
    int org_y;
    int hud_x;

    // GBT
    gbt_iniciar();
    gbt_crear_ventana("Tetris", ancho_ventana, alto_ventana, escala);
    gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888);

    // tablero
    Tablero* tablero = crear_tablero(COLUMNAS, FILAS_TOTAL);
    inicializar_tablero(tablero);

    // stats
    Estadisticas stats;
    stats_cargar(&stats);

    // variables de la partida
    Pieza actual, siguiente;
    uint32_t puntaje      = 0;
    uint32_t lineas_total = 0;
    int      piezas_fijas = 0;
    uint32_t vel_ms       = cfg.velocidad_ms;
    uint8_t  fijar        = 0;

    // nombre
    char    nombre[MAX_NOMBRE] = "";
    uint8_t nombre_idx = 0;

    // temporizadores
    tGBT_Temporizador* t_caida = gbt_temporizador_crear((double)vel_ms / 1000.0);
    tGBT_Temporizador* t_fijar = gbt_temporizador_crear((double)vel_ms / 2000.0);

    // los estados del programa son: 0 menu, 1 ingreso de nombre, 2 jugando, 3 pausa, 4 game over

    INICIAR_PARTIDA();
    uint8_t estado      = 0;
    uint8_t opcion_menu = 1;
    uint8_t corriendo   = 1;

    while(corriendo)
    {
        if(cfg.resolucion == 1) {
            ancho_ventana = 320;
            alto_ventana = 200;
        } else {
            ancho_ventana = 640;
            alto_ventana = 480;
        }
        tam   = (alto_ventana - 40) / FILAS_VISIBLES;
        org_x = ancho_ventana/2 - (COLUMNAS * tam)/2;
        org_y = 20;
        hud_x = org_x + COLUMNAS * tam + 10;
        gbt_borrar_backbuffer(3);
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
        if(estado == 0)
        {
            logica_menu(tecla, &opcion_menu, &estado, &corriendo);
            dibujar_menu(ancho_ventana, alto_ventana, opcion_menu);
        }
        else if(estado == 1)
        {
            logica_config(tecla, &opcionSeleccionadaConfig, &opcion1, &opcion2, &opcion3, &cfg, &estado);
            int alto_actual = (cfg.resolucion == 2) ? 480 : 200;
            dibujar_config(alto_actual ,&opcionSeleccionadaConfig, opcion1, opcion2, opcion3);
        }
        else if(estado == 2)
        {
            logica_nombre(tecla, &indiceLetra, nombreJugador, &estado);
            dibujar_nombre(ancho_ventana, nombreJugador);
        }
        else if(estado == 3 || estado == 4)
        {
            if (tecla == GBTK_p)
            {
                if (estado == 3)
                {
                    estado = 4;
                    gbt_temporizador_pausar(t_caida);
                    gbt_temporizador_pausar(t_fijar);
                } else {
                    estado = 3;
                    gbt_temporizador_reanudar(t_caida);
                    gbt_temporizador_reanudar(t_fijar);
                }
            }
            if (tecla == GBTK_ESCAPE)
            {
                estado = 0;
                opcion_menu = 1;
            }
            if (estado == 3)
            {
                if (tecla == GBTK_IZQUIERDA && pieza_es_valida(tablero, &actual, -1, 0))
                {
                    actual.x--;
                    fijar = 0;
                }
                if (tecla == GBTK_DERECHA && pieza_es_valida(tablero, &actual, 1, 0))
                {
                    actual.x++;
                    fijar = 0;
                }
                if (tecla == GBTK_ARRIBA)
                {
                    Pieza tmp = actual;
                    rotar_pieza_derecha(&tmp);
                    if (pieza_es_valida(tablero, &tmp, 0, 0))
                    {
                        actual = tmp;
                        fijar = 0;
                    }
                }
                if (tecla == GBTK_z)
                {
                    Pieza tmp = actual;
                    rotar_pieza_izquierda(&tmp);
                    if (pieza_es_valida(tablero, &tmp, 0, 0))
                    {
                        actual = tmp;
                        fijar = 0;
                    }
                }

                if (tecla == GBTK_ABAJO && pieza_es_valida(tablero, &actual, 0, 1))
                {     //bajada manual la cual otorga un punto cada vez que lo apretas
                    actual.y++;
                    puntaje++;
                    fijar = 0;
                }


                if (gbt_temporizador_consumir(t_caida))
                {                       //temporizador de bajada automatica
                    if (pieza_es_valida(tablero, &actual, 0, 1))
                    {
                        actual.y++;
                    }else
                    {
                        fijar = 1;
                    }
                }

                if (fijar && gbt_temporizador_consumir(t_fijar))
                {              //Temporizador de fijacion siendo tolerancia 50% de la vel de caida
                    if (!pieza_es_valida(tablero, &actual, 0, 1))
                    {
                        fijar_pieza(tablero, &actual);      //fijamos la pieza
                        piezas_fijas++;
                        int n = limpiar_lineas(tablero);    //limpiamos linea completa y sumamos el puntaje
                        lineas_total += (uint32_t)n;
                        puntaje += puntaje_por_lineas(n, vel_ms);
                        vel_ms = nueva_velocidad(cfg.velocidad_ms, piezas_fijas);  //Actualizamos la velocidad (-3% cada 10 piezas) y recreamos temporizadores
                        gbt_temporizador_destruir(t_caida);
                        gbt_temporizador_destruir(t_fijar);
                        t_caida = gbt_temporizador_crear((double)vel_ms / 1000.0);
                        t_fijar = gbt_temporizador_crear((double)vel_ms / 2000.0);
                        if (tablero_game_over(tablero))
                        {   //verificamos game over
                            stats_actualizar(&stats, nombre, puntaje, lineas_total);
                            estado = 5;
                        }
                        else
                        {
                            actual    = siguiente;
                            siguiente = spawn_random(tablero->ancho);
                            fijar     = 0;
                        }

                    }
                    else
                    {
                        fijar = 0; //esto es si el jugador movio la pieza antes de que pase el tiempo de fijarla
                    }
                }
            }
            pintar_tablero(tablero, org_x, org_y, tam);
            pintar_sombra(tablero, &actual, org_x, org_y, tam);
            pintar_pieza(&actual, org_x, org_y, tam);
            dibujar_hud(hud_x, puntaje, lineas_total, vel_ms, &siguiente, tam);
            if (estado == 4)
            {
                pantalla_pausa(ancho_ventana, alto_ventana);
            }
        }
        else if (estado == 5)
        {
            pintar_tablero(tablero, org_x, org_y, tam);
            pantalla_game_over(ancho_ventana, alto_ventana, puntaje, lineas_total);

            if (tecla == GBTK_ENTER) {
                estado = 2;
                //tecla_consumida = 1;
                INICIAR_PARTIDA();
            }
            if (tecla == GBTK_ESCAPE) {
                estado = 0;
                opcion_menu = 1;
            }
        }
        else if (estado == 6)
        {
            if (tecla == GBTK_ESCAPE)
            {
                estado = 0;
                opcion_menu = 1;
            }

            dibujar_estadisticas(ancho_ventana, alto_ventana, &stats);
        }
        else if (estado == 7)
        {

                dibujar_texto("Trabajo practico realizado por", 20, 80, 15);
                dibujar_texto("Federico Bustos y Franco Melillo", 10, 100, 15);
                if (gbt_tecla_presionada(GBTK_ESCAPE) || gbt_tecla_presionada(GBTK_ENTER))
                {
                    estado = 0;
                }

        }
        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    gbt_temporizador_destruir(t_caida);
    gbt_temporizador_destruir(t_fijar);
    destruir_tablero(tablero);
    gbt_destruir_ventana();
    gbt_cerrar();
    return 0;
}
