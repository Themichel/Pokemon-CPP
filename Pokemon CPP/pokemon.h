#pragma once  
#include <string>
#include <GL/freeglut.h>  

// Estructuras y funciones para manejar Pokémon y ataques en un juego de Pokémon  

struct ataque {  
    std::string nombre, tipo;  
    int danioBase, ppfijo, pp;  
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
extern int atJugador, atEnemigo;  
extern std::string atqEN;  
extern std::string atqJG;  

extern float animOffsetJugador;  
extern int animDirJugador;  

void aplicarAtaque(pokemon& atacante, pokemon& defensor, ataque atq);  
void turnJugador(int selecJugador);  
void turnEnemigo(int selecEnemigo);  
void dibujarPokemon(const pokemon& p, int x, int y, bool deFrente, int width, int height);  
void dibujarSprite(GLuint textura, int x, int y, int width, int height, bool transparente);  
void dibujarHPJugador(GLuint textura, int x, int y, float width, float height, int hp);  
void dibujarHPEnemigo(GLuint textura, int x, int y, float width, float height, int hp);  
void aplicarTurnos(int selecJugador);  
void temporizadorJugador(int value);  
void temporizadorEnemigo(int value);