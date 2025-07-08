#pragma once
enum estadoVis {
    TITLE,
    SELECCIONPOKEMON,
    SELECCIONMENU,
    SELECCIONATQ,
    ESPERATURNO,
    SELECCIONFINCOMBATE
};

enum estadoTurn {
    JUGADOR,
    ENEMIGO,
};

enum estadoJuego {
    SELECCION,
    MENU,
    MENUATQ,
    TURNOJUGADOR,
    TURNOENEMIGO,
    ESPERA,
    MENUFIN,
    TITLESCREEN,
    NONE
};

enum estadoGeneral {
    COMBATE,
    FINCOMBATE
};

extern estadoVis estadoVisual; // Estado visual del juego
extern estadoJuego estado; // Estado del juego
extern estadoGeneral estadodeCombate; // Estado del combate
extern estadoJuego ultimoTurno; // Ultimo turno jugado
extern estadoTurn estadoTurno; // Estado del turno actual
extern int ataqueJugador; // Ataque del jugador

extern const int WINDOW_WIDTH, WINDOW_HEIGHT; // Dimensiones de la ventana
// Funciones de inicialización y manejo de eventos
void teclado(unsigned char key, int x, int y);
void teclasEspeciales(int key, int x, int y);
void display();
void initJuego();
void cargarTexturas();
void titleScreen1(int value);
void titleScreen2(int value);
void cambioTitulo(int value);