	#pragma once
// Game.h - Declaración de funciones y variables globales para el juego Pokémon
enum estadoVis {
    SELECCIONPOKEMON,
    SELECCIONMENU,
    SELECCIONATQ,
    ESPERATURNO,
    SELECCIONFINCOMBATE
};

enum estadoJuego {  
    SELECCION,  
    MENU,  
    MENUATQ,  
    TURNOJUGADOR,  
	TURNOENEMIGO,
    ESPERA,
    MENUFIN,
    NONE
};  

enum estadoGeneral {  
    COMBATE,  
    FINCOMBATE  
};

extern bool ataquePendiente;
extern pokemon* atacantePendiente;
extern pokemon* defensorPendiente;
extern ataque ataqueEnProceso;
extern estadoVis estadoVisual; // Estado visual del juego
extern estadoJuego estado; // Estado del juego
extern estadoGeneral estadodeCombate; // Estado del combate
extern estadoJuego ultimoTurno; // Ultimo turno jugado
extern int ataqueJugador; // Ataque del jugador
extern const int WINDOW_WIDTH, WINDOW_HEIGHT; // Dimensiones de la ventana
// Funciones de inicialización y manejo de eventos
void teclado(unsigned char key, int x, int y);
void teclasEspeciales(int key, int x, int y);
void display();
void initJuego();
void cargarTexturas();
void procesarAtaquePendiente();