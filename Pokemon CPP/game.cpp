#include "game.h"
#include "pokemon.h"
#include "menu.h"
#include "textura.h"
#include "animations.h"
#include "fonts.h"
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

// Variables globales
estadoJuego ultimoTurno = TURNOJUGADOR; // Ultimo turno jugado
estadoJuego estado = SELECCION; // Estado inicial del juego
estadoGeneral estadodeCombate = COMBATE;
estadoVis estadoVisual = SELECCIONPOKEMON; // Estado visual inicial
int ataqueJugador = 0; // Ataque seleccionado por el jugador
const int WINDOW_WIDTH = 800; const int WINDOW_HEIGHT = 600; // Dimensiones de la ventana
GLuint barrainferior = cargarTexturaDesdePNG("assets/barrainferior.png", false);
GLuint menuselec = cargarTexturaDesdePNG("assets/menuatq.png", false);
GLuint menuatq = cargarTexturaDesdePNG("assets/menuatq2.png", false);
GLuint background = cargarTexturaDesdePNG("assets/background.png", false);
GLuint arrow = cargarTexturaDesdePNG("assets/arrow.png", false);
GLuint texturaFuente1 = cargarTexturaDesdePNG("assets/fonts/font1.png", true);
GLuint hp_jugador = cargarTexturaDesdePNG("assets/hp_jugador.png", false);
GLuint hp_enemigo = cargarTexturaDesdePNG("assets/hp_enemigo.png", false);

// Funcion cargar texturas
void cargarTexturas() {
    barrainferior = cargarTexturaDesdePNG("assets/barrainferior.png", false);
    menuselec = cargarTexturaDesdePNG("assets/menuatq.png", false);
    menuatq = cargarTexturaDesdePNG("assets/menuatq2.png", false);
    background = cargarTexturaDesdePNG("assets/background.png", false);
    arrow = cargarTexturaDesdePNG("assets/arrow.png", false);
    texturaFuente1 = cargarTexturaDesdePNG("assets/fonts/font1.png", true);
    hp_jugador = cargarTexturaDesdePNG("assets/hp_jugador.png", false);
    hp_enemigo = cargarTexturaDesdePNG("assets/hp_enemigo.png", false);
}

// Funcion de display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Configuración de la proyección ortográfica
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0.0, int(WINDOW_WIDTH), 0.0, int(WINDOW_HEIGHT), -1, 1);
    // Inicio del dibujo
    if (estadoVisual == SELECCIONPOKEMON) {
        dibujarBoton(menuPokemon[0][0], (filaSelec == 0 && colSelec == 0)); // Dibuja el botón de Bulbasaur
        dibujarBoton(menuPokemon[0][1], (filaSelec == 0 && colSelec == 1)); // Dibuja el botón de Squirtle
        dibujarBoton(menuPokemon[0][2], (filaSelec == 0 && colSelec == 2)); // Dibuja el botón de Charmander

        // Dibujo de sprites encima de los botones
        dibujarSprite(bulbasaur.texturaID2, 124, WINDOW_HEIGHT / 2 - 56, 152, 152);
        dibujarSprite(squirtle.texturaID2, 324, WINDOW_HEIGHT / 2 - 56, 152, 152);
        dibujarSprite(charmander.texturaID2, 524, WINDOW_HEIGHT / 2 - 56, 152, 152);
    }
    else if ((estadoVisual == SELECCIONMENU && estadodeCombate == COMBATE) || (estadoVisual == SELECCIONATQ && estadodeCombate == COMBATE)) {
		// Dibujo del fondo
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, background);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 1); glVertex2i(0, 160);
        glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 160);
        glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
        glTexCoord2i(0, 0); glVertex2i(0, WINDOW_HEIGHT);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        // Dibujo de Pokemones
        dibujarPokemon(pokeJugador, 100, 155 + (int)animOffsetJugador, true, 200, 200);
        dibujarPokemon(pokeEnemigo, 500, 350, false, 150, 150);
        // Dibujo de la barra inferior
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, barrainferior);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 1); glVertex2i(0, 0);
        glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 0);
        glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, 160);
        glTexCoord2i(0, 0); glVertex2i(0, 160);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        if (menuActivo == 0) {
            // Dibujo del menu de seleccion
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, menuselec);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(400, 0); 
            glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 0);
            glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, 160);
            glTexCoord2i(0, 0); glVertex2i(400, 160);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            // Dibujo de la flecha
			int fx = 432, fy = 92, fw = 14, fh = 21; // Posicion y tamaño de la flecha
            switch (filaSelec) {
            case 0:
                if (colSelec == 0) {
                    glEnable(GL_TEXTURE_2D);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, arrow);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 1); glVertex2i(fx, fy);
                    glTexCoord2i(1, 1); glVertex2i(fx + fw, fy);
                    glTexCoord2i(1, 0); glVertex2i(fx + fw, fy + fh);
                    glTexCoord2i(0, 0); glVertex2i(fx, fy + fh);
                    glEnd();
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
                } else if (colSelec == 1) {
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, arrow);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 1); glVertex2i(fx + 184, fy);
                    glTexCoord2i(1, 1); glVertex2i(fx + 184 + fw, fy);
                    glTexCoord2i(1, 0); glVertex2i(fx + 184 + fw, fy + fh);
                    glTexCoord2i(0, 0); glVertex2i(fx + 184, fy + fh);
                    glEnd();
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
				}
                break;
            
            case 1:
                if (colSelec == 0) {
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, arrow);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 1); glVertex2i(fx, fy - 53);
                    glTexCoord2i(1, 1); glVertex2i(fx + fw, fy - 53);
                    glTexCoord2i(1, 0); glVertex2i(fx + fw, fy - 53 + fh);
                    glTexCoord2i(0, 0); glVertex2i(fx, fy - 53 + fh);
                    glEnd();
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
                }
                else if (colSelec == 1) {
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, arrow);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 1); glVertex2i(fx + 184, fy - 53);
                    glTexCoord2i(1, 1); glVertex2i(fx + 184 + fw, fy - 53);
                    glTexCoord2i(1, 0); glVertex2i(fx + 184 + fw, fy - 53 + fh);
                    glTexCoord2i(0, 0); glVertex2i(fx + 184, fy - 53 + fh);
                    glEnd();
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
                }
				break;
            }
        }
        else if (menuActivo == 1) {
            // Dibujo del cuadro de seleccion de ataque
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, menuatq);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(0, 0);
            glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 0);
            glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, 160);
            glTexCoord2i(0, 0); glVertex2i(0, 160);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            // Dibujo de los botones de ataque
            menuAtq[0][0].texto = pokeJugador.ataque1.nombre.c_str();
            menuAtq[0][1].texto = pokeJugador.ataque2.nombre.c_str();
            renderizarTexto(pokeJugador.ataque1.nombre.c_str(), 50, 90, 3.0f, texturaFuente1);
            renderizarTexto(pokeJugador.ataque2.nombre.c_str(), 300, 90, 3.0f, texturaFuente1);
            renderizarTexto("-", 51, 40, 3.0f, texturaFuente1);
            renderizarTexto("-", 301, 40, 3.0f, texturaFuente1);
            // Dibujo de la flecha
            int fx = 30, fy = 95, fw = 14, fh = 21; // Posicion y tamaño de la flecha
            switch (filaSelec) {
            case 0:
                if (colSelec == 0) {
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, arrow);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 1); glVertex2i(fx, fy);
                    glTexCoord2i(1, 1); glVertex2i(fx + fw, fy);
                    glTexCoord2i(1, 0); glVertex2i(fx + fw, fy + fh);
                    glTexCoord2i(0, 0); glVertex2i(fx, fy + fh);
                    glEnd();
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
                }
                else if (colSelec == 1) {
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, arrow);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 1); glVertex2i(fx + 250, fy);
                    glTexCoord2i(1, 1); glVertex2i(fx + 250 + fw, fy);
                    glTexCoord2i(1, 0); glVertex2i(fx + 250 + fw, fy + fh);
                    glTexCoord2i(0, 0); glVertex2i(fx + 250, fy + fh);
                    glEnd();
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
                }
                break;

            case 1:
                if (colSelec == 0) {
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, arrow);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 1); glVertex2i(fx, fy - 50);
                    glTexCoord2i(1, 1); glVertex2i(fx + fw, fy - 50);
                    glTexCoord2i(1, 0); glVertex2i(fx + fw, fy - 50 + fh);
                    glTexCoord2i(0, 0); glVertex2i(fx, fy - 50 + fh);
                    glEnd();
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
                }
                else if (colSelec == 1) {
                    glEnable(GL_TEXTURE_2D);
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    glBindTexture(GL_TEXTURE_2D, arrow);
                    glBegin(GL_QUADS);
                    glTexCoord2i(0, 1); glVertex2i(fx + 250, fy - 50);
                    glTexCoord2i(1, 1); glVertex2i(fx + 250 + fw, fy - 50);
                    glTexCoord2i(1, 0); glVertex2i(fx + 250 + fw, fy - 50 + fh);
                    glTexCoord2i(0, 0); glVertex2i(fx + 250, fy - 50 + fh);
                    glEnd();
                    glDisable(GL_BLEND);
                    glDisable(GL_TEXTURE_2D);
                }
                break;
            }
        }
    }
    else if (estadoVisual == SELECCIONFINCOMBATE) {
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
				estadoVisual = SELECCIONMENU;
                pokeJugador.texturaID2 = cargarTexturaDesdePNG(pokeJugador.rutaSprite2, true);
                pokeEnemigo.texturaID2 = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite2, true);
                pokeJugador.texturaID = cargarTexturaDesdePNG(pokeJugador.rutaSprite, true);
                pokeEnemigo.texturaID = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite, true);
                glutPostRedisplay();
            }
            else if (filaSelec == 0 && colSelec == 1) {
                cout << "Squirtle seleccionado\n";
                pokeJugador = squirtle;
                pokeEnemigo = bulbasaur;
                filaSelec = 0;
                colSelec = 0;
                estado = MENU;
				estadoVisual = SELECCIONMENU;
                pokeJugador.texturaID2 = cargarTexturaDesdePNG(pokeJugador.rutaSprite2, true);
                pokeEnemigo.texturaID2 = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite2, true);
                pokeJugador.texturaID = cargarTexturaDesdePNG(pokeJugador.rutaSprite, true);
                pokeEnemigo.texturaID = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite, true);
                glutPostRedisplay();
            }
            else if (filaSelec == 0 && colSelec == 2) {
                cout << "Charmander seleccionado\n";
                pokeJugador = charmander;
                pokeEnemigo = squirtle;
                filaSelec = 0;
                colSelec = 0;
                estado = MENU;
				estadoVisual = SELECCIONMENU;
                pokeJugador.texturaID2 = cargarTexturaDesdePNG(pokeJugador.rutaSprite2, true);
                pokeEnemigo.texturaID2 = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite2, true);
                pokeJugador.texturaID = cargarTexturaDesdePNG(pokeJugador.rutaSprite, true);
                pokeEnemigo.texturaID = cargarTexturaDesdePNG(pokeEnemigo.rutaSprite, true);
                glutPostRedisplay();
            }
        }
        break;

    case MENU: // Si el menu principal esta activo
        if (key == 13) {
            if (seleccionMenu)
                if (filaSelec == 0 && colSelec == 0) {
                    estado = MENUATQ; // Cambiar al estado de ataque
					estadoVisual = SELECCIONATQ; // Cambiar al estado visual de selección de ataque
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
                    ataqueJugador = 0;
                    if (pokeJugador.velocidad > pokeEnemigo.velocidad || pokeJugador.velocidad == pokeEnemigo.velocidad) {
                        estado = TURNOJUGADOR; // Cambiar al estado de turno del jugador
                        ultimoTurno = estado;
                        turnJugador(ataqueJugador); // Llamar a la función de turno del jugador
                    }
                    else if (pokeEnemigo.velocidad > pokeJugador.velocidad) {
                        estado = TURNOENEMIGO; // Cambiar al estado de turno del enemigo
                        ultimoTurno = estado;
                        turnEnemigo(); // Llamar a la función de turno del enemigo
                    }
                    menuActivo = 0; // Volver al menú principal
                    filaSelec = 0;
                    colSelec = 0;
                    seleccionMenu = true; // Volver al modo de selección de menú
                    seleccionAtq = false; // Desactivar el modo de ataque
                    glutPostRedisplay(); // Redibujar la ventana
                }
                else if (filaSelec == 0 && colSelec == 1) {
                    ataqueJugador = 1;
                    if (pokeJugador.velocidad > pokeEnemigo.velocidad || pokeJugador.velocidad == pokeEnemigo.velocidad) {
						estado = TURNOJUGADOR; // Cambiar al estado de turno del jugador
                        ultimoTurno = estado;
                        turnJugador(ataqueJugador); // Llamar a la función de turno del jugador
                    }
					else if (pokeEnemigo.velocidad > pokeJugador.velocidad) {
						estado = TURNOENEMIGO; // Cambiar al estado de turno del enemigo
                        ultimoTurno = estado;
                        turnEnemigo(); // Llamar a la función de turno del enemigo
					}
                    menuActivo = 0; // Volver al menú principal
                    filaSelec = 0;
                    colSelec = 0;
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
				// Reiniciar el juego
                pokeJugador.vida = 20;
                pokeJugador.defensa = 1;
                pokeJugador.ataque = 1;
                pokeJugador.ataque1.pp = pokeJugador.ataque1.ppfijo;
                pokeJugador.ataque2.pp = pokeJugador.ataque2.ppfijo;
                pokeEnemigo.vida = 20;
                pokeEnemigo.defensa = 1;
                pokeEnemigo.ataque = 1;
                pokeEnemigo.ataque1.pp = pokeEnemigo.ataque1.ppfijo;
                pokeEnemigo.ataque2.pp = pokeEnemigo.ataque2.ppfijo;
				estadoVisual = SELECCIONPOKEMON; // Volver al estado de selección de Pokémon
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
    bulbasaur.texturaID = cargarTexturaDesdePNG(bulbasaur.rutaSprite, true);
    bulbasaur.texturaID2 = cargarTexturaDesdePNG(bulbasaur.rutaSprite2, true);

    squirtle.texturaID = cargarTexturaDesdePNG(squirtle.rutaSprite, true);
    squirtle.texturaID2 = cargarTexturaDesdePNG(squirtle.rutaSprite2, true);

    charmander.texturaID = cargarTexturaDesdePNG(charmander.rutaSprite, true);
    charmander.texturaID2 = cargarTexturaDesdePNG(charmander.rutaSprite2, true);

    // Limpiar pantalla al iniciar
    glutPostRedisplay();
}