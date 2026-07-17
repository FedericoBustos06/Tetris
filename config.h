#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdint.h>

#define CONFIG_ARCHIVO "tetris_config.bin"

#define VELOCIDAD_INICIAL_MS 1000
#define CANT_COLORES 41

extern tGBT_ColorRGB paletaMetalicaCGA[];
extern tGBT_ColorRGB paletaPastelCGA[];
extern tGBT_ColorRGB paletaMetalicaVGA[];
extern tGBT_ColorRGB paletaPastelVGA[];


typedef enum {
    PALETA_METALICA = 0,
    PALETA_PASTEL   = 1
} TipoPaleta;

typedef enum {
    RES_320x200 = 0,
    RES_640x480 = 1
} TipoResolucion;

typedef enum {
    VEL_BAJA = 0,
    VEL_ALTA = 1
} TipoVelocidad;

typedef struct {
    TipoPaleta     paleta;
    TipoResolucion resolucion;
    TipoVelocidad  velocidad;
    uint8_t escala;
} Config;

void config_guardar(const Config* c);
void inicializar_configuracion(Config* cfg);
void logica_config(eGBT_Tecla tecla, Config* cfg, uint8_t* estado);
void dibujar_config(Config cfg);

#endif // CONFIG_H_INCLUDED
