#include "GBT/gbt.h"
#include "juego.h"
#include "fuentes.h"
#include "dibujos.h"
#include "funciones.h"
#include "tablero.h"
#include <stdio.h>

static const int PUNTOS_LINEAS[5] = {0, 100, 300, 500, 800};
static uint8_t opcionActual = 1;

static void actualizar_nivel_y_velocidad(Partida* p, uint32_t velocidadInicial);
static uint32_t puntaje_por_lineas(int lineas_limpiadas, uint32_t vel_ms);
static void dibujar_hud(Partida partida, TipoResolucion resolucion);

void logica_classic(eGBT_Tecla tecla, Partida* p, uint8_t* estado)
{
    if(tecla == GBTK_IZQUIERDA && puede_moverse(p->tablero, &p->actual, -1, 0))
    {
        p->actual.x--;
    }
    if(tecla == GBTK_DERECHA && puede_moverse(p->tablero, &p->actual, 1, 0))
    {
        p->actual.x++;
    }
    if(tecla == GBTK_ABAJO)
    {
        if(puede_moverse(p->tablero, &p->actual, 0, 1))
        {
            p->actual.y++;
            p->puntaje++;
            p->fijar = 0;
        }
    }
    if(tecla == GBTK_ESPACIO)
    {
        while(puede_moverse(p->tablero, &p->actual, 0, 1))
        {
            p->actual.y++;
            p->puntaje += 2;
        }
        p->fijar = 1;
    }
    if(tecla == GBTK_ARRIBA)
    {
        Pieza tmp = p->actual;
        rotar_pieza_derecha(&tmp);
        if(puede_moverse(p->tablero, &tmp, 0, 0))
        {
            p->actual = tmp;
        }
    }
    if(tecla == GBTK_z)
    {
        Pieza tmp = p->actual;
        rotar_pieza_izquierda(&tmp);
        if(puede_moverse(p->tablero, &tmp, 0, 0))
        {
            p->actual = tmp;
        }
    }
    if(tecla == GBTK_p)
    {
        gbt_temporizador_pausar(p->t_caida);
        gbt_temporizador_pausar(p->t_fijar);
        *estado = 4;
    }
    if(tecla == GBTK_ESCAPE)
    {
        *estado = 0;
    }

    if(gbt_temporizador_consumir(p->t_caida))
    {
        if(puede_moverse(p->tablero, &p->actual, 0, 1))
        {
            p->actual.y++;
        }
        else
        {
            p->fijar = 1;
        }
    }

    if(p->fijar && gbt_temporizador_consumir(p->t_fijar))
    {
        if(!puede_moverse(p->tablero, &p->actual, 0, 1))
        {
            uint8_t lineasLimpiadas;

            fijar_pieza(p->tablero, &p->actual);
            p->piezas_fijadas++;

            lineasLimpiadas = limpiar_lineas(p->tablero);
            if(lineasLimpiadas > 0)
            {
                p->lineasCompletadas += (uint16_t)lineasLimpiadas;
                p->puntaje += PUNTOS_LINEAS[lineasLimpiadas] * p->nivel;
            }

            actualizar_nivel_y_velocidad(p, p->vel_ms);

            if (verificar_derrota(p->tablero))
            {
                *estado = 5;
            }
            else
            {
                p->actual = p->siguientes[0];
                for(int i = 0; i < 4; i++)
                {
                    p->siguientes[i] = p->siguientes[i + 1];
                }
                p->siguientes[4] = crear_pieza();
            }
        }
    }
}

void dibujar_classic(Partida partida, TipoResolucion resolucion)
{
    uint8_t posX = (resolucion == RES_320x200) ? 120 : 210;
    uint8_t posY = 20;
    pintar_tablero(partida.tablero, resolucion);
    pintar_sombra(partida.tablero, &partida.actual, posX , posY, resolucion);
    pintar_pieza(&partida.actual, posX , posY, resolucion);
    dibujar_hud(partida, resolucion);
}

void logica_pausa(eGBT_Tecla tecla, Partida* partida, uint8_t* estado, TipoVelocidad velocidad)
{
    if(tecla == GBTK_ARRIBA)
    {
        opcionActual--;
        if(opcionActual < 1)
        {
            opcionActual = 3;
        }
    }
    else if(tecla == GBTK_ABAJO)
    {
        opcionActual++;
        if(opcionActual > 3)
        {
            opcionActual = 1;
        }
    }
    else if(tecla == GBTK_ENTER && opcionActual == 1)
    {
        gbt_temporizador_reanudar(partida->t_caida);
        gbt_temporizador_reanudar(partida->t_fijar);
        *estado = 2;
    }
    else if(tecla == GBTK_ENTER && opcionActual == 2)
    {
        inicializar_partida(partida, velocidad);
        *estado = 2;
    }
    else if(tecla == GBTK_ENTER && opcionActual == 3)
    {
        *estado = 0;
    }
}

void dibujar_pausa(Partida partida, TipoResolucion resolucion)
{
    uint8_t color1 = (opcionActual == 1) ? 16 : 17;
    uint8_t color2 = (opcionActual == 2) ? 16 : 17;
    uint8_t color3 = (opcionActual == 3) ? 16 : 17;

    pintar_tablero(partida.tablero, resolucion);
    dibujar_hud(partida, resolucion);

    if(resolucion == RES_320x200)
    {
        dibujar_rectangulo(100, 120, 60, 100, 18);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 100, 150, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 210, 150, 3);

        dibujar_rectangulo(100, 120, 40, 20, 16);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 100, 40, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 210, 40, 3);
        dibujar_texto("PAUSA", 140, 46, 11);

        dibujar_rectangulo(114, 92, 81, 16, color1);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 114, 81, 18);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 196, 87, 18);
        dibujar_texto("Reanudar", 128, 85, 11);

        dibujar_rectangulo(114, 92, 102, 16, color2);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 114, 102, 18);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 196, 108, 18);
        dibujar_texto("Reiniciar", 124, 106, 11);

        dibujar_rectangulo(114, 92, 123, 16, color3);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 114, 123, 18);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 196, 129, 18);
        dibujar_texto("Salir", 140, 127, 11 );
    }

    if(resolucion == RES_640x480)
    {
        dibujar_rectangulo(200, 240, 160, 200, 18);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 200, 350, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 430, 350, 3);

        dibujar_rectangulo(200, 240, 120, 40, 16);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 200, 120, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 430, 120, 3);
        dibujar_texto("PAUSA", 300, 132, 11);

        dibujar_rectangulo(228, 184, 202, 32, color1);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 228, 202, 18);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 402, 224, 18);
        dibujar_texto("Reanudar", 288, 210, 11);

        dibujar_rectangulo(228, 184, 244, 32, color2);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 228, 244, 18);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 402, 266, 18);
        dibujar_texto("Reiniciar", 288, 252, 11);

        dibujar_rectangulo(228, 184, 286, 32, color3);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 228, 286, 18);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 402, 308, 18);
        dibujar_texto("Salir", 288, 294, 11);
    }

}

void logica_derrota(eGBT_Tecla tecla, Partida* partida, uint8_t* estado, TipoVelocidad velocidad)
{
    if(tecla == GBTK_ARRIBA)
    {
        opcionActual--;
        if(opcionActual < 1)
        {
            opcionActual = 2;
        }
    }
    else if(tecla == GBTK_ABAJO)
    {
        opcionActual++;
        if(opcionActual > 2)
        {
            opcionActual = 1;
        }
    }
    else if(tecla == GBTK_ENTER && opcionActual == 1)
    {
        inicializar_partida(partida, velocidad);
        *estado = 2;
    }
    else if(tecla == GBTK_ENTER && opcionActual == 2)
    {
        *estado = 0;
    }
}

void dibujar_derrota(Partida partida, TipoResolucion resolucion)
{
    char buf[10];
    uint8_t color1 = (opcionActual == 1) ? 31 : 32;
    uint8_t color2 = (opcionActual == 2) ? 31 : 32;

    pintar_tablero(partida.tablero, resolucion);
    dibujar_hud(partida, resolucion);

    if(resolucion == RES_320x200)
    {
        dibujar_rectangulo(100, 120, 60, 100, 33);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 100, 150, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 210, 150, 3);

        dibujar_rectangulo(100, 120, 40, 20, 31);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 100, 40, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 210, 40, 3);
        dibujar_texto("DERROTA", 132, 46, 11);

        dibujar_texto("PUNTUACION:", 114, 66, 11);
        sprintf(buf, "%05lu", (unsigned long)partida.puntaje);
        dibujar_texto(buf, 114, 75,  11);

        dibujar_texto("RECORD:", 114, 90, 11);
        sprintf(buf, "%05lu", (unsigned long)partida.puntaje);
        dibujar_texto(buf, 114, 99, 11);

        dibujar_rectangulo(114, 92, 113, 16, color1);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 114, 113, 33);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 196, 119, 33);
        dibujar_texto("Reiniciar", 124, 117, 11);

        dibujar_rectangulo(114, 92, 134, 16, color2);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 114, 134, 33);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 196, 140, 33);
        dibujar_texto("Salir", 140, 138, 11);
    }

    if(resolucion == RES_640x480)
    {
        dibujar_rectangulo(200, 240, 160, 200, 33);
        dibujar_elemento((const uint8_t*)borde_ll, 10, 10, 200, 350, 3);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 430, 350, 3);

        dibujar_rectangulo(200, 240, 120, 40, 31);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 200, 120, 3);
        dibujar_elemento((const uint8_t*)borde_tr, 10, 10, 430, 120, 3);
        dibujar_texto("DERROTA", 292, 132, 11);

        dibujar_texto("PUNTUACION:", 228, 172, 11);
        sprintf(buf, "%05lu", (unsigned long)partida.puntaje);
        dibujar_texto(buf, 228, 190,  11);

        dibujar_texto("RECORD:", 228, 220, 11);
        sprintf(buf, "%05lu", (unsigned long)partida.puntaje);
        dibujar_texto(buf, 228, 238, 11);

        dibujar_rectangulo(228, 184, 266, 32, color1);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 228, 266, 33);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 402, 288, 33);
        dibujar_texto("Reiniciar", 288, 274, 11);

        dibujar_rectangulo(228, 184, 308, 32, color2);
        dibujar_elemento((const uint8_t*)borde_tl, 10, 10, 228, 308, 33);
        dibujar_elemento((const uint8_t*)borde_lr, 10, 10, 402, 330, 33);
        dibujar_texto("Salir", 288, 316, 11);
    }
}

void inicializar_partida(Partida* partida, TipoVelocidad velocidadInicial)
{
    partida->tablero = crear_tablero(COLUMNAS, FILAS_TOTAL);
    inicializar_tablero(partida->tablero);
    partida->nivel = 1;

    if(velocidadInicial==VEL_BAJA)
    {
        partida->vel_ms = 1000;
    }
    if(velocidadInicial==VEL_ALTA)
    {
        partida->vel_ms = 250;
    }

    partida->actual = crear_pieza();

    for (int i = 0; i < 5; i++) {
        partida->siguientes[i] =  crear_pieza();
    }

    partida->t_caida = gbt_temporizador_crear((double)partida->vel_ms / 1000.0);
    partida->t_fijar = gbt_temporizador_crear(0.5);
}


static void actualizar_nivel_y_velocidad(Partida* p, uint32_t velocidadInicial)
{
    p->nivel = (p->lineasCompletadas / 10) + 1;
    p->vel_ms = velocidadInicial;
    for(int i = 0; i < (p->piezas_fijadas)/10; i++)
    {
        p->vel_ms = ((p->vel_ms * 97) + 99) / 100;
    }
    if(p->vel_ms < 100)
    {
        p->vel_ms = 100;
    }
}

static uint32_t puntaje_por_lineas(int lineas_limpiadas, uint32_t vel_ms)
{

    if(lineas_limpiadas < 1 || lineas_limpiadas > 4)
    {
         return 0;
    }
    double mult = (double)VELOCIDAD_INICIAL_MS / (double)vel_ms;
    if (mult < 1.0)
    {
        mult = 1.0;
    }
    return (uint32_t)(PUNTOS_LINEAS[lineas_limpiadas] * mult);

}

static void dibujar_hud(Partida partida, TipoResolucion resolucion)
{
    char buf[24];
    if(resolucion == RES_320x200)
    {
        dibujar_texto(partida.nombreJugador, 20, 52, 8);

        dibujar_texto("NIVEL", 20, 82, 8);
        sprintf(buf, "%02lu", (unsigned long)partida.nivel);
        dibujar_texto(buf, 20, 92, 8);

        dibujar_texto("PUNTUACION", 20, 134, 8);
        sprintf(buf, "%05lu", (unsigned long)partida.puntaje);
        dibujar_texto(buf, 20, 144, 8);

        dibujar_texto("RECORD", 20, 162, 8);
        sprintf(buf, "%05lu", (unsigned long)partida.puntaje);
        dibujar_texto(buf, 20, 172, 8);

        dibujar_texto("PROXIMAS", 228, 20, 8);
        dibujar_texto("PIEZAS", 236, 28, 8);
        dibujar_rectangulo(240, 40, 60, 120, 8);

        for (int pieza = 0; pieza < 5; pieza++)
        {
            partida.siguientes[pieza].x = 0;
            partida.siguientes[pieza].y = FILAS_OCULTAS;
            int cuadro = (pieza * 24);
            int desfase_x = 8;
            int desfase_y= 4;
            if(partida.siguientes[pieza].tipo == 0 || partida.siguientes[pieza].tipo == 1)
            {
                desfase_x = 4;
                if(partida.siguientes[pieza].tipo == 0)
                {
                    desfase_y = 0;
                }
            }
            pintar_pieza(&partida.siguientes[pieza], 240 + desfase_x, 60 + cuadro + desfase_y, resolucion);
        }
    }
    if(resolucion == RES_640x480)
    {
        dibujar_texto_8x16(partida.nombreJugador, 40, 104, 8);

        dibujar_texto_8x16("NIVEL", 40, 164, 8);
        sprintf(buf, "%02lu", (unsigned long)partida.nivel);
        dibujar_texto_8x16(buf, 40, 184, 8);

        dibujar_texto_8x16("PUNTUACION", 40, 366, 8);
        sprintf(buf, "%05lu", (unsigned long)partida.puntaje);
        dibujar_texto_8x16(buf, 40, 387, 8);

        dibujar_texto_8x16("RECORD", 40, 423, 8);
        sprintf(buf, "%05lu", (unsigned long)partida.puntaje);
        dibujar_texto_8x16(buf, 40, 444, 8);

        dibujar_texto_8x16("PROXIMAS", 503, 20, 8);
        dibujar_texto_8x16("PIEZAS", 511, 36, 8);
        dibujar_rectangulo(495, 100, 88, 300, 8);

        for (int pieza = 0; pieza < 5; pieza++)
        {
            partida.siguientes[pieza].x = 0;
            partida.siguientes[pieza].y = FILAS_OCULTAS;
            int cuadro = (pieza * 60);
            int desfase_x = 17;
            int desfase_y= 8;
            if (partida.siguientes[pieza].tipo == 0 || partida.siguientes[pieza].tipo == 1)
            {
                desfase_x = 6;
                if(partida.siguientes[pieza].tipo == 0)
                {
                    desfase_y = -3;
                }
            }
            pintar_pieza(&partida.siguientes[pieza], 495 + desfase_x, 88 + cuadro + desfase_y, resolucion);
        }
    }
}
