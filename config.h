#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <stdint.h>

#define CONFIG_ARCHIVO "tetris_config.bin"

#define VELOCIDAD_INICIAL_MS 1000

typedef struct {
    uint8_t  resolucion;
    uint8_t  escala;
    uint32_t velocidad_ms;
    uint8_t  paleta;
} Config;

void config_cargar(Config* c);

void config_guardar(const Config* c);

void config_default(Config* c);

#endif
