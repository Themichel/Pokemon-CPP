#include "pokemon.h"
#include "game.h"
#include <iostream>
using namespace std;

float animOffsetJugador = 0.0f;
int animDirJugador = 1;

// Pokemones
pokemon bulbasaur = { "Bulbasaur", {"Placaje", 3, false, false, 1.0f}, {"Grunido", 0, false, true, 0.2f}, 5, 20, 1, 1, 1.2f,"assets/back_bulbasaur.png","assets/bulbasaur.png",0,0 };
pokemon squirtle = { "Squirtle", {"Placaje", 3, false, false, 1.0f}, {"Latigo", 0, true, false, 0.2f}, 5, 20, 1, 1, 1.1f,"assets/back_squirtle.png", "assets/squirtle.png",0,0 };
pokemon charmander = { "Charmander", {"Araniazo", 3, false,false, 1.0f}, {"Grunido", 0, false, true, 0.2f}, 5, 20, 1, 1, 1.5f,"assets/back_charmander.png", "assets/charmander.png",0,0 };
pokemon pokeJugador, pokeEnemigo; // Variables para almacenar los pokemones del jugador y del enemigo

// Funcion para saber que ataque se selecciono
void aplicarAtaque(pokemon& atacante, pokemon& defensor, ataque atq) {
    if (atq.danioBase > 0) {
        int danio = atq.danioBase * atacante.ataque * defensor.defensa; // Calcula el daño base multiplicando el ataque del atacante
        if (danio < 1) danio = 1; // El daño no puede ser menor a 1
        defensor.vida -= danio; // Resta el daño a la vida del defensor
        if (defensor.vida <= 0) {
            defensor.vida = 0; // La vida no puede ser menor a 0
            estadodeCombate = FINCOMBATE; // Cambia el estado del combate a FINCOMBATE
            estado = MENUFIN; // Cambia el estado a MENUFIN
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
        if (defensor.ataque < 0.6) {
            defensor.ataque = 0.6; // El ataque no puede ser menor a 0.6
            cout << "El ataque de " << defensor.nombre << " no puede bajar mas" << endl;
        }
    }
}

// Funciones para manejar los turnos del jugador y del enemigo
void turnEnemigo() {
    if (estado != TURNOENEMIGO) return;
    int selecEnem = rand() % 2;
    ataque atq = (selecEnem == 0) ? pokeEnemigo.ataque1 : pokeEnemigo.ataque2;
    aplicarAtaque(pokeEnemigo, pokeJugador, atq);
    if (estadodeCombate == FINCOMBATE) return; // Detener si el combate terminó
    estado = MENU;
}

void turnJugador(int selecJugador) {
    if (estado != TURNOJUGADOR) return;
    ataque atq = (selecJugador == 0) ? pokeJugador.ataque1 : pokeJugador.ataque2;
    aplicarAtaque(pokeJugador, pokeEnemigo, atq);
    if (estadodeCombate == FINCOMBATE) return; // Detener si el combate terminó
    estado = TURNOENEMIGO;
    turnEnemigo();
}

// Funcion para dibujar Pokemon
void dibujarPokemon(const pokemon& p, int x, int y, bool deFrente, int width, int height) {
    GLuint textura = deFrente ? p.texturaID : p.texturaID2; // Selecciona la textura correcta
    glEnable(GL_TEXTURE_2D); // Habilita el uso de texturas
    glBindTexture(GL_TEXTURE_2D, textura); // Vincula la textura del Pokémon
    // Dibuja cuadro base del Pokémon
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex2i(x, y);
    glTexCoord2f(1, 1); glVertex2i(x + width, y);
    glTexCoord2f(1, 0); glVertex2i(x + width, y + height);
    glTexCoord2f(0, 0); glVertex2i(x, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D); // Deshabilita el uso de texturas

    // Muestra el nombre arriba del cuadro
    glColor3f(0.0f, 0.0f, 0.0f); // Texto negro
    glRasterPos2i(x + 10, y + 210);
    for (char c : p.nombre) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Muestra la vida debajo del cuadro
    string vidaStr = "HP: " + to_string(p.vida);
    glRasterPos2i(x + 10, y - 20);
    for (char c : vidaStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}