#include "GBT/gbt.h"
#include "funciones.h"

void dibujar_rectangulo(int x, int ancho, int y, int altura, int color){
    for(int j=x; j<ancho+x; j++)
    {
        for(int k=y; k<altura+y; k++)
        {
            gbt_dibujar_pixel(j, k, color);
        }
    }
}
