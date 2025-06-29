#include "animations.h"
#include "game.h"
#include <GL/freeglut.h>

float animOffsetJugador = 0.0f, animAtaqueOffset = 0.0f; // Desplazamiento vertical del Pokémon jugador
int animDirJugador = 1, animAtaqueTurno = 0; // Dirección del movimiento (1 = hacia arriba, -1 = hacia abajo)
bool animAtaqueEnCurso = false;
bool animAtaqueIda = true; // true: va hacia el defensor, false: regresa

void animarPokemones(int value) {
    // Solo animar si estamos en selección o esperando turno
    if (estado == MENU || estado == MENUATQ) {
        // Movimiento vertical tipo "flotante"
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

void animarAtaque(int value2) {
    if (!animAtaqueEnCurso) return;

    float velocidad = 12.0f;
    float maxOffset = 60.0f;

    if (animAtaqueIda) {
        animAtaqueOffset += velocidad;
        if (animAtaqueOffset >= maxOffset) {
            animAtaqueOffset = maxOffset;
            animAtaqueIda = false;
        }
    }
    else {
        animAtaqueOffset -= velocidad;
        if (animAtaqueOffset <= 0.0f) {
            animAtaqueOffset = 0.0f;
            animAtaqueEnCurso = false;
            // Aquí puedes continuar con el flujo del juego, por ejemplo, llamar al siguiente turno
        }
    }

    glutPostRedisplay();
    if (animAtaqueEnCurso)
        glutTimerFunc(16, animarAtaque, 0);
}