#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdint.h>

#define CONFIG_ARCHIVO "tetris_config.bin"

#define VELOCIDAD_INICIAL_MS 1000

typedef struct {
    uint8_t  paleta;
    uint8_t  resolucion;
    uint32_t velocidad_ms;
} Config;

void config_cargar(Config* c);
void config_guardar(const Config* c);
void config_default(Config* c);

void logica_config(eGBT_Tecla tecla, uint8_t *opcionSeleccionadaConfig, const char **opcion1, const char **opcion2, const char **opcion3, Config *cfg, uint8_t *estado);
void dibujar_config(int alto_ventana, uint8_t *opcionSeleccionadaConfig, const char *opcion1, const char *opcion2, const char *opcion3);

#endif // CONFIG_H_INCLUDED
