#include "game.h"
#include "pokemon.h"
#include "menu.h"
#include "textura.h"
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

estadoJuego estado = SELECCION;
estadoGeneral estadodeCombate = COMBATE;

const int WINDOW_WIDTH = 800; const int WINDOW_HEIGHT = 600; // Dimensiones de la ventana
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

// Funcion de display
void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    // Configuración de la proyección ortográfica
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // Reiniciar la matriz de transformación
    glOrtho(0.0, int(WINDOW_WIDTH), 0.0, int(WINDOW_HEIGHT), -1, 1);

    // Inicio del dibujo
    if (estado == SELECCION) {
        dibujarBoton(menuPokemon[0][0], (filaSelec == 0 && colSelec == 0)); // Dibuja el botón de Bulbasaur
        dibujarBoton(menuPokemon[0][1], (filaSelec == 0 && colSelec == 1)); // Dibuja el botón de Squirtle
        dibujarBoton(menuPokemon[0][2], (filaSelec == 0 && colSelec == 2)); // Dibuja el botón de Charmander
    }

    else if ((estado == MENU && estadodeCombate == COMBATE) || (estado == MENUATQ && estadodeCombate == COMBATE)) {
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f); // Cuadro de fondo
        glVertex2i(WINDOW_WIDTH, 0);
        glVertex2i(0, 0);
        glVertex2i(0, 180);
        glVertex2i(WINDOW_WIDTH, 180);
        glEnd();
        // Dibujo de Pokemones
        glColor3f(1.0f, 1.0f, 1.0f);
        dibujarPokemon(pokeJugador, 100, 210 + (int)animOffsetJugador, true, 200, 200);
        glColor3f(1.0f, 1.0f, 1.0f);
        dibujarPokemon(pokeEnemigo, 500, 350, false, 150, 150);
        if (menuActivo == 0) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    dibujarBoton(menuMain[i][j], (filaSelec == i && colSelec == j));
                }
            }
        }
        else if (menuActivo == 1) {
            // Dibuja los botones de ataque
            menuAtq[0][0].texto = pokeJugador.ataque1.nombre.c_str();
            menuAtq[0][1].texto = pokeJugador.ataque2.nombre.c_str();
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    dibujarBoton(menuAtq[i][j], (filaSelec == i && colSelec == j));
                }
            }
        }
    }
    else if (estadodeCombate == FINCOMBATE) {
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo para el mensaje de fin de combate
        glRasterPos2i(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
        const char* mensaje = (pokeJugador.vida <= 0) ? "Has perdido el combate" : "Has ganado el combate";
        for (const char* c = mensaje; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        for (int j = 0; j < 2; j++) {
            dibujarBoton(menuFin[0][j], colSelec == j);
        }
    }

    // Fin del dibujo
    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y) { // Función para manejar las teclas normales
    if (key == 27) {
        glutLeaveMainLoop(); // Salir usando la tecla ESC
    }

    switch (estado) {
    case SELECCION: // Si el estado es de selección de Pokémon
        if (key == 13) { // Si se presiona Enter
            if (filaSelec == 0 && colSelec == 0) {
                cout << "Bulbasaur seleccionado\n";
                pokeJugador = bulbasaur;
                pokeEnemigo = charmander;
                filaSelec = 0;
                colSelec = 0;
                estado = MENU;
                pokeJugador.texturaID2 = cargarTexturaDesdePNG(pokeJugador.rutaSprite2);
                pokeEnemigo.texturaID2 = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite2);
                pokeJugador.texturaID = cargarTexturaDesdePNG(pokeJugador.rutaSprite);
                pokeEnemigo.texturaID = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite);
                glutPostRedisplay();
            }
            else if (filaSelec == 0 && colSelec == 1) {
                cout << "Squirtle seleccionado\n";
                pokeJugador = squirtle;
                pokeEnemigo = bulbasaur;
                filaSelec = 0;
                colSelec = 0;
                estado = MENU;
                pokeJugador.texturaID2 = cargarTexturaDesdePNG(pokeJugador.rutaSprite2);
                pokeEnemigo.texturaID2 = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite2);
                pokeJugador.texturaID = cargarTexturaDesdePNG(pokeJugador.rutaSprite);
                pokeEnemigo.texturaID = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite);
                glutPostRedisplay();
            }
            else if (filaSelec == 0 && colSelec == 2) {
                cout << "Charmander seleccionado\n";
                pokeJugador = charmander;
                pokeEnemigo = squirtle;
                filaSelec = 0;
                colSelec = 0;
                estado = MENU;
                pokeJugador.texturaID2 = cargarTexturaDesdePNG(pokeJugador.rutaSprite2);
                pokeEnemigo.texturaID2 = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite2);
                pokeJugador.texturaID = cargarTexturaDesdePNG(pokeJugador.rutaSprite);
                pokeEnemigo.texturaID = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite);
                glutPostRedisplay();
            }
        }
        break;

    case MENU: // Si el menu principal esta activo
        if (key == 13) {
            if (seleccionMenu)
                if (filaSelec == 0 && colSelec == 0) {
                    estado = MENUATQ; // Cambiar al estado de ataque
                    menuActivo = 1; // Atacar
                    seleccionAtq = true; // Activar el modo de ataque
                    seleccionMenu = false; // Cambiar a modo de selección de ataque
                    glutPostRedisplay(); // Redibujar la ventana
                }
        }
        break;

    case MENUATQ: // Si el menu de ataque esta activo
        if (key == 13) { // Si se presiona Enter
            if (seleccionAtq) {
                if (filaSelec == 0 && colSelec == 0) {
                    estado = TURNOJUGADOR; // Cambiar al estado de turno del jugador
                    turnJugador(0); // Llamar a la función de turno del jugador
                    menuActivo = 0; // Volver al menú principal
                    seleccionMenu = true; // Volver al modo de selección de menú
                    seleccionAtq = false; // Desactivar el modo de ataque
                    glutPostRedisplay(); // Redibujar la ventana
                }
                else if (filaSelec == 0 && colSelec == 1) {
                    estado = TURNOJUGADOR; // Cambiar al estado de turno del jugador
                    turnJugador(1); // Llamar a la función de turno del jugador
                    menuActivo = 0; // Volver al menú principal
                    seleccionMenu = true; // Volver al modo de selección de menú
                    seleccionAtq = false; // Desactivar el modo de ataque
                    glutPostRedisplay(); // Redibujar la ventana
                }
            }
        }
        break;

    case MENUFIN:
        if (key == 13) {
            if (colSelec == 0) { // Reintentar
                pokeJugador.vida = 20;
                pokeJugador.defensa = 1;
                pokeJugador.ataque = 1;
                pokeEnemigo.vida = 20;
                pokeEnemigo.defensa = 1;
                pokeEnemigo.ataque = 1;
                estadodeCombate = COMBATE;
                estado = SELECCION;
                filaSelec = 0;
                colSelec = 0;
                menuActivo = 0;
                seleccionMenu = true;
                seleccionAtq = false;
                glutPostRedisplay();
                return;
            }
            else if (colSelec == 1) { // Salir
                glutLeaveMainLoop();
                return;
            }
        }
        break;

        if (key == 8) {
            if (menuActivo == 1) {
                menuActivo = 0; // Volver al menú principal
                filaSelec = 0; // Reiniciar la selección
                colSelec = 0; // Reiniciar la selección
                glutPostRedisplay(); // Redibujar la ventana
            }
        }
        break;
    }
}

void teclasEspeciales(int key, int x, int y) {

    // Chequea si esta en el estado de selección de Pokemon
    if (estado == SELECCION) {
        switch (key) {
        case GLUT_KEY_LEFT:
            if (colSelec > 0) {
                colSelec--;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (colSelec < 2) {
                colSelec++;
            }
            break;
        default:
            break;
        }
    }

    // Chequea si esta en el estado de menu principal o de ataque
    else if (estado == MENU || estado == MENUATQ) {
        switch (key) {
        case GLUT_KEY_LEFT:
            if (colSelec > 0) {
                colSelec--;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (colSelec < 1) {
                colSelec++;
            }
            break;
        case GLUT_KEY_UP:
            if (filaSelec > 0) {
                filaSelec--;
            }
            break;
        case GLUT_KEY_DOWN:
            if (filaSelec < 1) {
                filaSelec++;
            }
            break;
        default:
            break;
        }
    }

    else if (estadodeCombate == FINCOMBATE) {
        switch (key) {
        case GLUT_KEY_LEFT:
            if (colSelec > 0) colSelec--;
            break;
        case GLUT_KEY_RIGHT:
            if (colSelec < 1) colSelec++;
            break;
        default:
            break;
        }
    }

    glutPostRedisplay();
}

void initJuego() {
    // Resetear vida y stats de pokemones
    bulbasaur.vida = squirtle.vida = charmander.vida = 20;
    bulbasaur.defensa = squirtle.defensa = charmander.defensa = 1.0f;
    bulbasaur.ataque = squirtle.ataque = charmander.ataque = 1.0f;

    // Resetear texturas
    bulbasaur.texturaID = cargarTexturaDesdePNG(bulbasaur.rutaSprite);
    bulbasaur.texturaID2 = cargarTexturaDesdePNG(bulbasaur.rutaSprite2);

    squirtle.texturaID = cargarTexturaDesdePNG(squirtle.rutaSprite);
    squirtle.texturaID2 = cargarTexturaDesdePNG(squirtle.rutaSprite2);

    charmander.texturaID = cargarTexturaDesdePNG(charmander.rutaSprite);
    charmander.texturaID2 = cargarTexturaDesdePNG(charmander.rutaSprite2);

    // Limpiar pantalla al iniciar
    glutPostRedisplay();
}