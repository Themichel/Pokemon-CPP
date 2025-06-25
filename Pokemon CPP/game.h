	#pragma once
enum estadoJuego {  
    SELECCION,  
    MENU,  
    MENUATQ,  
    TURNOJUGADOR,  
	TURNOENEMIGO,
    MENUFIN  
};  

enum estadoGeneral {  
    COMBATE,  
    FINCOMBATE  
};

extern estadoJuego estado; // Estado del juego
extern estadoGeneral estadodeCombate; // Estado del combate
extern const int WINDOW_WIDTH, WINDOW_HEIGHT; // Dimensiones de la ventana
void animarPokemones(int value);
void teclado(unsigned char key, int x, int y);
void teclasEspeciales(int key, int x, int y);
void display();
void initJuego();