#pragma once
#include <string>
// Declaraciones de botones, variables y funciones para los menus del juego

struct boton {
    int x, y, width, height;
    const char* texto;
};

extern boton menuPokemon[1][3];
extern boton menuMain[2][2];
extern boton menuAtq[2][2];
extern boton menuFin[1][2];

extern bool seleccionMenu, seleccionAtq;
extern int menuActivo, filaSelec, colSelec;

void dibujarBoton(const boton& b, bool seleccionado);