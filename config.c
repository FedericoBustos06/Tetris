#include <stdio.h>
#include <string.h>
#include "config.h"

void config_default(Config* c){
    c->resolucion  = 1;
    c->escala      = 2;
    c->velocidad_ms = VELOCIDAD_INICIAL_MS;
    c->paleta      = 0;
}

void config_cargar(Config* c){
    FILE* f = fopen(CONFIG_ARCHIVO, "rb");
    if (!f) {
        config_default(c);
        return;
    }
    if (fread(c, sizeof(Config), 1, f) != 1)
        config_default(c);
    fclose(f);
}

void config_guardar(const Config* c){
    FILE* f = fopen(CONFIG_ARCHIVO, "wb");
    if (!f) return;
    fwrite(c, sizeof(Config), 1, f);
    fclose(f);
}
