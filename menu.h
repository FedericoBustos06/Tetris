#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void logica_menu(eGBT_Tecla tecla, uint8_t *opcion_menu, uint8_t *estado, uint8_t *corriendo);
void dibujar_menu(int ancho, int alto, uint8_t opcion);

#endif // MENU_H_INCLUDED
