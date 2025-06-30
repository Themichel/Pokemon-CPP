#include "pokemon.h"
#include "game.h"
#include "animations.h"
#include "fonts.h"
#include "textura.h"
#include <iostream>
using namespace std;
// Pokemones
pokemon bulbasaur = { "BULBASAUR", {"TACKLE","NORMAL", 3, 35, 35, false, false, 1.0f}, {"GROWL","NORMAL", 0, 40, 40, false, true, 0.2f}, 5, 20, 1, 1, 1.2f,"assets/back_bulbasaur.png","assets/bulbasaur.png",0,0};
pokemon squirtle = { "SQUIRTLE", {"TACKLE","NORMAL", 3, 35, 35, false, false, 1.0f}, {"TAIL WHIP","NORMAL", 0, 30, 30, true, false, 0.2f}, 5, 20, 1, 1, 1.1f,"assets/back_squirtle.png", "assets/squirtle.png",0,0};
pokemon charmander = { "CHARMANDER", {"SCRATCH", "NORMAL", 3, 35, 35, false,false, 1.0f}, {"GROWL","NORMAL", 0, 30, 40, false, true, 0.2f}, 5, 20, 1, 1, 1.5f,"assets/back_charmander.png", "assets/charmander.png",0,0 };
pokemon pokeJugador, pokeEnemigo; // Variables para almacenar los pokemones del jugador y del enemigo

// Funcion para saber que ataque se selecciono
void aplicarAtaque(pokemon& atacante, pokemon& defensor, ataque atq) {
    if (atq.danioBase > 0) {
        int danio = atq.danioBase * atacante.ataque * defensor.defensa; // Calcula el daño base multiplicando el ataque del atacante
        if (danio < 1) danio = 1; // El daño no puede ser menor a 1
        defensor.vida -= danio; // Resta el daño a la vida del defensor
        if (defensor.vida <= 0) {
            defensor.vida = 0; // La vida no puede ser menor a 0
            estadoVisual = SELECCIONFINCOMBATE;
            estadodeCombate = FINCOMBATE; // Cambia el estado del combate a FINCOMBATE
            estado = MENUFIN;
        }
        cout << atacante.nombre << " usa " << atq.nombre << " y causa " << danio << " puntos de daño a " << defensor.nombre << endl;
    }

    if (atq.bajaDefensa) {
        defensor.defensa += atq.modificador; // Aplica el modificador a la defensa del defensor
        cout << defensor.nombre << " baja su defensa a " << defensor.defensa << endl;
        if (defensor.defensa > 1.6) {
            defensor.defensa = 1.6; // La defensa no puede ser mayor a 1.6
            cout << "La defensa de " << defensor.nombre << " no puede bajar mas" << endl;
        }
    }

    if (atq.bajaAtaque) {
		defensor.ataque -= atq.modificador; // Aplica el modificador al ataque del defensor
		cout << defensor.nombre << " baja su ataque a " << defensor.ataque << endl;
        if (defensor.ataque < 0.4) {
            defensor.ataque = 0.4; // El ataque no puede ser menor a 0.4
            cout << "El ataque de " << defensor.nombre << " no puede bajar mas" << endl;
        }
    }
}

// Funciones para manejar los turnos del jugador y del enemigo
void turnEnemigo() {
    int selecEnem = rand() % 2;
    ataque atq = (selecEnem == 0) ? pokeEnemigo.ataque1 : pokeEnemigo.ataque2;
    if (estadodeCombate == FINCOMBATE) return; // Detener si el combate terminó
    if (ultimoTurno == TURNOENEMIGO) {
        estado = TURNOJUGADOR;
        aplicarAtaque(pokeEnemigo, pokeJugador, atq);
        turnJugador(ataqueJugador);
    }
    else if (ultimoTurno == TURNOJUGADOR || ultimoTurno == NONE) {
        estado = ESPERA;
		estadoVisual = ESPERATURNO;
        aplicarAtaque(pokeEnemigo, pokeJugador, atq);
    }
}

void turnJugador(int selecJugador) {
    ataque atq = (selecJugador == 0) ? pokeJugador.ataque1 : pokeJugador.ataque2;
    if (estadodeCombate == FINCOMBATE) return; // Detener si el combate terminó
    if (ultimoTurno == TURNOJUGADOR) {
        estado = TURNOENEMIGO;
        aplicarAtaque(pokeJugador, pokeEnemigo, atq);
        turnEnemigo();
		ataqueJugador = 0; // Reinicia la selección del ataque del jugador
    }
    else if (ultimoTurno == TURNOENEMIGO || ultimoTurno == NONE) {
        estado = ESPERA;
        estadoVisual = ESPERATURNO;
        aplicarAtaque(pokeJugador, pokeEnemigo, atq);
	}
}

// Funcion para dibujar Pokemon
void dibujarPokemon(const pokemon& p, int x, int y, bool deFrente, int width, int height) {
    GLuint textura = deFrente ? p.texturaID : p.texturaID2; // Selecciona la textura correcta
    glEnable(GL_TEXTURE_2D); // Habilita el uso de texturas
	glEnable(GL_BLEND); // Habilita el blending para texturas
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Configura el modo de mezcla para texturas con transparencia
    glBindTexture(GL_TEXTURE_2D, textura); // Vincula la textura del Pokémon
    // Dibuja cuadro base del Pokémon
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2i(x, y);
    glTexCoord2f(1, 1); glVertex2i(x + width, y);
    glTexCoord2f(1, 0); glVertex2i(x + width, y + height);
    glTexCoord2f(0, 0); glVertex2i(x, y + height);
    glEnd();

	glDisable(GL_BLEND); // Deshabilita el modo de mezcla
    glDisable(GL_TEXTURE_2D); // Deshabilita el uso de texturas
    
}

void dibujarSprite(GLuint textura, int x, int y, int width, int height, bool transparente) {
    if (transparente) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, textura);
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2i(x, y);
        glTexCoord2f(1, 1); glVertex2i(x + width, y);
        glTexCoord2f(1, 0); glVertex2i(x + width, y + height);
        glTexCoord2f(0, 0); glVertex2i(x, y + height);
        glEnd();

        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }
    
    else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textura);
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2i(x, y);
        glTexCoord2f(1, 1); glVertex2i(x + width, y);
        glTexCoord2f(1, 0); glVertex2i(x + width, y + height);
        glTexCoord2f(0, 0); glVertex2i(x, y + height);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
}

void dibujarHPJugador(GLuint textura, int x, int y, float width, float height, int hp) {
    glColor3f(0.4078f, 0.9216f, 0.6078f);
    glBegin(GL_QUADS);
    glVertex2f(x + 166.5, y + 28); 
    glVertex2f(x + 166.5 + (hp * 8.4), y + 28);
    glVertex2f(x + 166.5 + (hp * 8.4), y + height - 59.5);
    glVertex2f(x + 166.5, y + height - 59.5);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2i(x, y);
    glTexCoord2f(1, 1); glVertex2i(x + width, y);
    glTexCoord2f(1, 0); glVertex2i(x + width, y + height);
    glTexCoord2f(0, 0); glVertex2i(x, y + height);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void dibujarHPEnemigo(GLuint textura, int x, int y, float width, float height, int hp) {
    glColor3f(0.4078f, 0.9216f, 0.6078f);
    glBegin(GL_QUADS);
    glVertex2f(x + 136.5, y + 28);
    glVertex2f(x + 136.5 + (hp * 8.4), y + 28);
    glVertex2f(x + 136.5 + (hp * 8.4), y + height - 59.5);
    glVertex2f(x + 136.5, y + height - 59.5);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2i(x, y);
    glTexCoord2f(1, 1); glVertex2i(x + width, y);
    glTexCoord2f(1, 0); glVertex2i(x + width, y + height);
    glTexCoord2f(0, 0); glVertex2i(x, y + height);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}