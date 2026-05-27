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

  * Apellido: BIASUTTI, LUCIANO
 * DNI:
 * Usuario: jamas se supo
 * Entrega: No, se ve que el tp le genero terror
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
#define CANT_COLORES 20

static tGBT_ColorRGB paleta[CANT_COLORES] = {
    {255,255,255}, /* 0  blanco         */
    {224,224,224}, /* 1  gris claro     */
    {180,180,180}, /* 2  gris medio     */
    {120,120,120}, /* 3  gris           */
    {60, 60, 60},  /* 4  gris oscuro    */
    {30, 30, 30},  /* 5  casi negro     */
    {10, 10, 10},  /* 6  negro          */
    {20, 20, 20},  /* 7  fondo tablero  */
    {40, 40, 40},  /* 8  fondo panel    */
    {80, 80, 80},  /* 9  borde          */
    {100,100,110}, /* 10 sombra pieza   */
    {200,200,200}, /* 11 reservado      */
    {150,150,150}, /* 12 reservado      */
    {  0,240,240}, /* 13 I - cyan       */
    {240,240,  0}, /* 14 O - amarillo   */
    {160,  0,240}, /* 15 T - violeta    */
    {240,160,  0}, /* 16 L - naranja    */
    {  0,  0,240}, /* 17 J - azul       */
    {240,  0,  0}, /* 18 Z - rojo       */
    {  0,240,  0}, /* 19 S - verde      */
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

//pantalla del menu
static void pantalla_menu(int ancho, int alto, uint8_t opcion){
    int x, y;
    uint8_t color;

    for (x = ancho/2; x < ancho; x++)
        for (y = 0; y < alto; y++)
            gbt_dibujar_pixel(x, y, 8);

    if (ancho == 320) {

        for (x = 85; x < 160; x++)
            for (y = 33; y < 63; y++)
                gbt_dibujar_pixel(x, y, 0);
        dibujar_texto_8x16("Tet", 136, 40, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 85,  33, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 85,  53, 3); //Tet

        for (x = 160; x < 235; x++)
            for (y = 33; y < 63; y++)
                gbt_dibujar_pixel(x, y, 6);
        dibujar_texto_8x16("ris", 160, 40, 11);                         //ris
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 33, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 53, 8);

        color = (opcion == 1) ? 2 : 0;
        for (x = 85; x < 150; x++)
            for (y = 68; y < 98; y++)
                gbt_dibujar_pixel(x, y, (opcion == 1) ? 2 : 0);
        dibujar_texto("Classic", 90, 79, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 85,  68, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 85,  88, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 140, 68, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 140, 88, 3);

        for (x = 85; x < 150; x++)
            for (y = 103; y < 168; y++)
                gbt_dibujar_pixel(x, y, 0);
        dibujar_elemento((const uint8_t*)logo_unlam, 40, 40, 98, 116, 5);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 85,  103, 3);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 85,  158, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 140, 103, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 140, 158, 3);

        color = (opcion == 2) ? 9 : 6;
        for (x = 170; x < 235; x++)
            for (y = 68; y < 98; y++)
                gbt_dibujar_pixel(x, y, color);
        dibujar_texto("Deluxe", 179, 79, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 68, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 88, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 68, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 88, 8);

        color = (opcion == 3) ? 9 : 6;
        for (x = 170; x < 200; x++)
            for (y = 103; y < 133; y++)
                gbt_dibujar_pixel(x, y, color);
        dibujar_elemento((const uint8_t*)exclamacion, 16, 16, 177, 110, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 103, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 123, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 190, 103, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 190, 123, 8);

        color = (opcion == 4) ? 9 : 6;
        for (x = 205; x < 235; x++)
            for (y = 103; y < 133; y++)
                gbt_dibujar_pixel(x, y, color);
        dibujar_elemento((const uint8_t*)estadisticas, 16, 16, 212, 110, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 205, 103, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 205, 123, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 103, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 123, 8);

        color = (opcion == 5) ? 9 : 6;
        for (x = 170; x < 200; x++)
            for (y = 138; y < 168; y++)
                gbt_dibujar_pixel(x, y, color);
        dibujar_elemento((const uint8_t*)configuracion, 16, 16, 177, 145, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 170, 138, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 170, 158, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 190, 138, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 190, 158, 8);

        color = (opcion == 6) ? 9 : 6;
        for (x = 205; x < 235; x++)
            for (y = 138; y < 168; y++)
                gbt_dibujar_pixel(x, y, color);
        dibujar_elemento((const uint8_t*)cerrar, 16, 16, 212, 145, 11);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 205, 138, 8);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 205, 158, 8);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 225, 138, 8);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 225, 158, 8);
    }
}

//pantalla de nombre
static void pantalla_nombre(int ancho, int alto, eGBT_Tecla tecla, char* nombre, uint8_t* idx, uint8_t* listo){
    int x, y;
    for (x = 0; x < ancho; x++)
        for (y = 0; y < alto; y++)
            gbt_dibujar_pixel(x, y, 6);

    dibujar_texto_8x16("JUGADOR", ancho/2 - 56, alto/2 - 40, 0);
    dibujar_texto("Ingrese su nombre:", ancho/2 - 54, alto/2 - 10, 2);
    dibujar_texto(nombre, ancho/2 - 54, alto/2 + 6, 0);

    dibujar_texto("_", ancho/2 - 54 + (*idx)*6, alto/2 + 6, 1);//el cursor para ver donde estamos
    dibujar_texto("ENTER para confirmar", ancho/2 - 60, alto/2 + 24, 3);


    if ((tecla >= GBTK_a && tecla <= GBTK_z) && *idx < MAX_NOMBRE - 1) {    //para registrar letras
        nombre[*idx] = (char)tecla;
        (*idx)++;
        nombre[*idx] = '\0';
    }
    if ((tecla >= GBTK_0 && tecla <= GBTK_9) && *idx < MAX_NOMBRE - 1) {    //y numeros
        nombre[*idx] = (char)tecla;
        (*idx)++;
        nombre[*idx] = '\0';
    }
    if (tecla == GBTK_RETROCESO && *idx > 0) {
        (*idx)--;
        nombre[*idx] = '\0';
    }

    if (tecla == GBTK_ENTER && *idx > 0)//esto lo puse porque no me detectaba el enter
        *listo = 1;
}

//pantalla de pausa
static void pantalla_pausa(int ancho, int alto){
    dibujar_texto_8x16("PAUSA", ancho/2 - 40, alto/2 - 10, 0);
    dibujar_texto("P: continuar   ESC: menu", ancho/2 - 72, alto/2 + 12, 3);
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

//macro para poner todo en cero cada vez que arrancamos otra vez

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

    int ancho = (cfg.resolucion == 2) ? 640 : 320;
    int alto  = (cfg.resolucion == 2) ? 480 : 200;
    uint8_t escala = cfg.escala;

    if (argc == 3) {
        escala = (uint8_t)atoi(argv[2]);
        if (atoi(argv[1]) == 2) { ancho = 640; alto = 480; }
        else                    { ancho = 320; alto = 200; }
    } else if (argc != 1) {
        printf("Uso: %s [<1=CGA|2=VGA> <escala>]\n", argv[0]);
    }

    //Tamanio de bloque y posicion del tablero
    int tam   = (alto - 40) / FILAS_VISIBLES;
    int org_x = ancho/2 - (COLUMNAS * tam)/2;
    int org_y = 20;
    int hud_x = org_x + COLUMNAS * tam + 10;

    // GBT
    gbt_iniciar();
    gbt_crear_ventana("Tetris", ancho, alto, escala);
    gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888);

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

    uint8_t estado      = 0;
    uint8_t opcion_menu = 1;  //la opcion que resalte del menu
    uint8_t corriendo   = 1;

    //tema de tecla consumida, puse este flag porque sino enter se apretaba consecutivamente y andaba mal, no tengo idea porque pero con este flag se arreglo
    uint8_t tecla_consumida = 0;

    while (corriendo) {
        gbt_borrar_backbuffer(5);
        gbt_procesar_entrada();

        eGBT_Tecla tecla = tecla_consumida ? GBTK_DESCONOCIDA
                                           : gbt_obtener_tecla_presionada();
        tecla_consumida = 0;

        if (estado == 0) {
            pantalla_menu(ancho, alto, opcion_menu);

            if (tecla == GBTK_ARRIBA) {
                opcion_menu--;
                if (opcion_menu < 1) opcion_menu = 6; //asi pasamos del primero al ultimo
            }
            if (tecla == GBTK_ABAJO) {
                opcion_menu++;
                if (opcion_menu > 6) opcion_menu = 1; //o del ultimo al primero
            }
            if (tecla == GBTK_ENTER) {
                switch (opcion_menu) {
                    case 1:                  // jugar
                        estado = 1;
                        tecla_consumida = 1;
                        break;
                    case 6:                  // salir
                        corriendo = 0;
                        break;               // solo tenemos jugar y salir
                    default:
                        break;
                }
            }

    // ESTADO 1: ingresamos nombre
        } else if (estado == 1) {
            uint8_t nombre_listo = 0;
            pantalla_nombre(ancho, alto, tecla, nombre, &nombre_idx, &nombre_listo);

            if (nombre_listo) {
                estado = 2;
                tecla_consumida = 1; //para que el enter no pase al juego
                INICIAR_PARTIDA();
            }

    // ESTADO 4: GAME OVER (lo generamos antes asi no se nos congela o haya alguna latencia)
        } else if (estado == 4) {
            pintar_tablero(tablero, org_x, org_y, tam);
            pantalla_game_over(ancho, alto, puntaje, lineas_total);

            if (tecla == GBTK_ENTER) {
                estado = 2;
                tecla_consumida = 1;
                INICIAR_PARTIDA();
            }
            if (tecla == GBTK_ESCAPE) {
                estado = 0;
                opcion_menu = 1;
            }

    //ESTADO 2 o 3: jugando o en pausa
        } else if (estado == 2 || estado == 3) {

            if (tecla == GBTK_p) {      //con P pausas
                if (estado == 2) {
                    estado = 3;
                    gbt_temporizador_pausar(t_caida);
                    gbt_temporizador_pausar(t_fijar);
                } else {
                    estado = 2;
                    gbt_temporizador_reanudar(t_caida);
                    gbt_temporizador_reanudar(t_fijar);
                }
            }
            if (tecla == GBTK_ESCAPE) { //con ESC salis
                estado = 0;
                opcion_menu = 1;
            }


            if (estado == 2) {          //aca ya esta andando

                if (tecla == GBTK_IZQUIERDA && pieza_es_valida(tablero, &actual, -1, 0)) {  //movernos a la izquierda
                    actual.x--;
                    fijar = 0;
                }
                if (tecla == GBTK_DERECHA && pieza_es_valida(tablero, &actual, 1, 0)) {     //movernos a la derecha
                    actual.x++;
                    fijar = 0;
                }

                if (tecla == GBTK_ARRIBA) {                                                //rotamos la pieza a la derecha
                    Pieza tmp = actual;
                    rotar_pieza_derecha(&tmp);
                    if (pieza_es_valida(tablero, &tmp, 0, 0)) {
                        actual = tmp;
                        fijar = 0;
                    }
                }

                if (tecla == GBTK_z) {                                                //rotamos la pieza a la izquierda
                    Pieza tmp = actual;
                    rotar_pieza_izquierda(&tmp);
                    if (pieza_es_valida(tablero, &tmp, 0, 0)) {
                        actual = tmp;
                        fijar = 0;
                    }
                }

                if (tecla == GBTK_ABAJO && pieza_es_valida(tablero, &actual, 0, 1)) {     //bajada manual la cual otorga un punto cada vez que lo apretas
                    actual.y++;
                    puntaje++;
                    fijar = 0;
                }


                if (gbt_temporizador_consumir(t_caida)) {                       //temporizador de bajada automatica
                    if (pieza_es_valida(tablero, &actual, 0, 1))
                        actual.y++;
                    else
                        fijar = 1;
                }


                if (fijar && gbt_temporizador_consumir(t_fijar)) {              //Temporizador de fijacion siendo tolerancia 50% de la vel de caida
                    if (!pieza_es_valida(tablero, &actual, 0, 1)) {


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

                        if (tablero_game_over(tablero)) {   //verificamos game over
                            stats_actualizar(&stats, nombre, puntaje, lineas_total);
                            estado = 4;
                        }
                        else {
                            actual    = siguiente;
                            siguiente = spawn_random(tablero->ancho);
                            fijar     = 0;
                        }

                    } else {
                        fijar = 0; //esto es si el jugador movio la pieza antes de que pase el tiempo de fijarla
                    }
                }
            }

    //aca empiezan los renders
            pintar_tablero(tablero, org_x, org_y, tam);
            pintar_sombra(tablero, &actual, org_x, org_y, tam);
            pintar_pieza(&actual, org_x, org_y, tam);
            dibujar_hud(hud_x, puntaje, lineas_total, vel_ms, &siguiente, tam);

            if (estado == 3)
                pantalla_pausa(ancho, alto);
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
