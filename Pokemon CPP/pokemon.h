#pragma once
#include <string>
#include <GL/freeglut.h>

struct ataque {
    std::string nombre;
    int danioBase;
    bool bajaDefensa, bajaAtaque;
    float modificador;
};

struct pokemon {
    std::string nombre;
    ataque ataque1, ataque2;
    int nivel, vida;
    float defensa, ataque, velocidad;
    const char* rutaSprite;
    const char* rutaSprite2;
    GLuint texturaID, texturaID2;
};

extern pokemon bulbasaur, squirtle, charmander;
extern pokemon pokeJugador, pokeEnemigo;

extern float animOffsetJugador;
extern int animDirJugador;

void aplicarAtaque(pokemon& atacante, pokemon& defensor, ataque atq);
void turnJugador(int selecJugador);
void turnEnemigo();
void dibujarPokemon(const pokemon& p, int x, int y, bool deFrente, int width, int height);