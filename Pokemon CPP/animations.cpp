#include "animations.h"
#include "game.h"
#include <GL/freeglut.h>
#include "pokemon.h"
#include "audio.h"
#include <iostream>
using namespace std;

float animOffsetJugador = 0.0f, animAtaqueOffset = 0.0f; // Desplazamiento vertical del Pokémon jugador
int animDirJugador = 1, animAtaqueTurno = 0; // Dirección del movimiento (1 = hacia arriba, -1 = hacia abajo)
bool animAtaqueEnCurso = false;
bool animAtaqueIda = true; // true: va hacia el defensor, false: regresa
bool animAtaqueJugador = true; // true: ataque del jugador, false: del rival
float animAnguloCircular = 0.0f;
float animRadioCircular = 40.0f;
bool animCircularEnCurso = false;
bool animCircularJugador = true; // true: jugador, false: enemigo
float offsetXCircular = 0.0f;
float offsetYCircular = 0.0f;

void animarPokemones(int value) {
    // Solo animar si estamos en selección o esperando turno
    if (estado == MENU || estado == MENUATQ) {
        // Movimiento vertical tipo "flotante"
        animOffsetJugador += 0.2f * animDirJugador;

        if (animOffsetJugador > 2.0f || animOffsetJugador < -2.0f)
            animDirJugador *= -1;
    }
    else if (estado == SELECCION) {
        animOffsetJugador += 0.2f * animDirJugador;

        if (animOffsetJugador > 2.0f || animOffsetJugador < -2.0f)
            animDirJugador *= -1;
    }
    else {
        animOffsetJugador = 0.0f;
    }

    glutPostRedisplay(); // Redibuja la pantalla
    glutTimerFunc(16, animarPokemones, 0); // Llama de nuevo en ~16ms (60 FPS)
}

void animarAtaque1(int value) {
    if (!animAtaqueEnCurso) return;
    float velocidad = 8.0f;
    float maxOffset = 60.0f;
    if (animAtaqueIda) {
        glutTimerFunc(100, volumenMusica, 10);
        animAtaqueOffset += velocidad;
        if (animAtaqueOffset >= maxOffset) {
            animAtaqueOffset = maxOffset;
            animAtaqueIda = false;
            cout << atqJG << atqEN << endl;
			cout << estadoTurno << endl;
            if (estadoTurno == JUGADOR) {
                if (atqJG == "TAIL WHIP") {
                    reproducirSonido("tailwhip", 1);
                }
                else if (atqJG == "GROWL") {
                    reproducirSonido("growl", 0);
                }
                else {
                    reproducirSonido("danio", 0);
                }
            }
            else {
                if (atqEN == "TAIL WHIP") {
                    reproducirSonido("tailwhip", 1);
                }
                else if (atqEN == "GROWL") {
                    reproducirSonido("growl", 0);
                }
                else {
                    reproducirSonido("danio", 0);
                }
            }
			glutTimerFunc(500, volumenMusica, 32);
        }
    }
    else {
        animAtaqueOffset -= velocidad;
        if (animAtaqueOffset <= 0.0f) {
            animAtaqueOffset = 0.0f;
            animAtaqueEnCurso = false;
        }
    }

    glutPostRedisplay();
    if (animAtaqueEnCurso)
        glutTimerFunc(16, animarAtaque1, 0);
}

void animarAtaque2(int value) {
    if (!animAtaqueEnCurso) return;
    float velocidad = 8.0f;
    float maxOffset = 60.0f;
    if (animAtaqueIda) {
        glutTimerFunc(100, volumenMusica, 10);
        animAtaqueOffset += velocidad;
        if (animAtaqueOffset >= maxOffset) {
            animAtaqueOffset = maxOffset;
            animAtaqueIda = false;
			cout << atqJG << atqEN << endl;
			cout << estadoTurno << endl;
            if (estadoTurno == JUGADOR) {
                if (atqJG == "TAIL WHIP") {
					reproducirSonido("tailwhip", 1);
                }
                else if (atqJG == "GROWL") {
					reproducirSonido("growl", 0);
                }
                else {
                    reproducirSonido("danio", 0);
                }
            }
            else {
                if (atqEN == "TAIL WHIP") {
					reproducirSonido("tailwhip", 1);
                }
				else if (atqEN == "GROWL") {
                    reproducirSonido("growl", 0);
                }
                else {
                    reproducirSonido("danio", 0);
                }
            }
            glutTimerFunc(500, volumenMusica, 32);
        }
    }
    else {
        animAtaqueOffset -= velocidad;
        if (animAtaqueOffset <= 0.0f) {
            animAtaqueOffset = 0.0f;
            animAtaqueEnCurso = false;
        }
    }

    glutPostRedisplay();
    if (animAtaqueEnCurso)
        glutTimerFunc(16, animarAtaque2, 0);
    else {
        if (pokeEnemigo.vida <= 0 || pokeJugador.vida <= 0) return;
        estado = MENU;
        estadoVisual = SELECCIONMENU;
    }
}

void animarCircularJugador1(int value) {
    if (!animCircularEnCurso) return;
    animAnguloCircular += 0.12f;
    if (animAnguloCircular > 2 * 3.14159265f) animAnguloCircular -= 2 * 3.14159265f;
    offsetXCircular = cos(animAnguloCircular) * animRadioCircular;
    offsetYCircular = sin(animAnguloCircular) * animRadioCircular;
    animCircularEnCurso = false;
    glutPostRedisplay();
    if (animCircularEnCurso)
        glutTimerFunc(16, animarCircularJugador1, 0);
}

void animarCircularJugador2(int value) {
    if (!animCircularEnCurso) return;
    animAnguloCircular += 0.12f;
    if (animAnguloCircular > 2 * 3.14159265f) animAnguloCircular -= 2 * 3.14159265f;
    offsetXCircular = cos(animAnguloCircular) * animRadioCircular;
    offsetYCircular = sin(animAnguloCircular) * animRadioCircular;
	animCircularEnCurso = false;
    glutPostRedisplay();
    if (animCircularEnCurso)
        glutTimerFunc(16, animarCircularJugador2, 0);
    else {
		if (pokeEnemigo.vida <= 0 || pokeJugador.vida <= 0) return;
        estado = MENU;
		estadoVisual = SELECCIONMENU;
    }
}