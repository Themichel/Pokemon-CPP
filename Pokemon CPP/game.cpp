#include "game.h"
#include "pokemon.h"
#include "menu.h"
#include "textura.h"
#include "animations.h"
#include "fonts.h"
#include "audio.h" 
#include <GL/freeglut.h>
#include <cstdlib>
#include <iostream>
using namespace std;

// Variables globales
estadoJuego ultimoTurno = TURNOJUGADOR; // Ultimo turno jugado
estadoJuego estado = NONE; // Estado inicial del juego
estadoGeneral estadodeCombate = COMBATE;
estadoVis estadoVisual = TITLE; // Estado visual inicial
estadoTurn estadoTurno = JUGADOR; // Estado del turno inicial
int title = 0; // Variable para controlar la pantalla de título
int ataqueJugador = 0; // Ataque seleccionado por el jugador
bool pulsado = false;
const int WINDOW_WIDTH = 800; const int WINDOW_HEIGHT = 600; // Dimensiones de la ventana
GLuint barrainferior = cargarTexturaDesdePNG("assets/barrainferior.png", false);
GLuint menuselec = cargarTexturaDesdePNG("assets/menuatq.png", false);
GLuint menuatq = cargarTexturaDesdePNG("assets/menuatq2.png", false);
GLuint title0 = cargarTexturaDesdePNG("assets/titlescreen.png", false);
GLuint title1 = cargarTexturaDesdePNG("assets/titlescreen1.png", false);
GLuint title2 = cargarTexturaDesdePNG("assets/titlescreen2.png", false);
GLuint background = cargarTexturaDesdePNG("assets/background.png", false);
GLuint background2 = cargarTexturaDesdePNG("assets/background2.png", false);
GLuint background3 = cargarTexturaDesdePNG("assets/background3.png", false);
GLuint frame = cargarTexturaDesdePNG("assets/frame.png", false);
GLuint arrow = cargarTexturaDesdePNG("assets/arrow.png", false);
GLuint redarrow = cargarTexturaDesdePNG("assets/redarrow.png", false);
GLuint male = cargarTexturaDesdePNG("assets/male.png", false);
GLuint female = cargarTexturaDesdePNG("assets/female.png", false);
GLuint texturaFuente1 = cargarTexturaDesdePNG("assets/fonts/font1.png", true);
GLuint texturaFuente2 = cargarTexturaDesdePNG("assets/fonts/font2.png", true);
GLuint texturaFuente3 = cargarTexturaDesdePNG("assets/fonts/font3.png", true);
GLuint hp_jugador = cargarTexturaDesdePNG("assets/hp_jugador.png", false);
GLuint hp_enemigo = cargarTexturaDesdePNG("assets/hp_enemigo.png", false);

// Funcion cargar texturas
void cargarTexturas() {
    barrainferior = cargarTexturaDesdePNG("assets/barrainferior.png", false);
    menuselec = cargarTexturaDesdePNG("assets/menuatq.png", false);
    menuatq = cargarTexturaDesdePNG("assets/menuatq2.png", false);
    title0 = cargarTexturaDesdePNG("assets/titlescreen.png", false);
	title1 = cargarTexturaDesdePNG("assets/titlescreen1.png", false);
	title2 = cargarTexturaDesdePNG("assets/titlescreen2.png", false);
    background = cargarTexturaDesdePNG("assets/background.png", false);
	background2 = cargarTexturaDesdePNG("assets/background2.png", false);
    background3 = cargarTexturaDesdePNG("assets/background3.png", false);
	frame = cargarTexturaDesdePNG("assets/frame.png", false);
    arrow = cargarTexturaDesdePNG("assets/arrow.png", false);
	redarrow = cargarTexturaDesdePNG("assets/redarrow.png", false);
    male = cargarTexturaDesdePNG("assets/male.png", false);
    female = cargarTexturaDesdePNG("assets/female.png", false);
    texturaFuente1 = cargarTexturaDesdePNG("assets/fonts/font1.png", true);
    texturaFuente2 = cargarTexturaDesdePNG("assets/fonts/font2.png", true);
    texturaFuente3 = cargarTexturaDesdePNG("assets/fonts/font3.png", true);
    hp_jugador = cargarTexturaDesdePNG("assets/hp_jugador.png", false);
    hp_enemigo = cargarTexturaDesdePNG("assets/hp_enemigo.png", false);
}

// Funcion de display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
	cout << estado << estadoVisual << endl; // Imprimir el estado actual del juego en la consola
    // Configuración de la proyección ortográfica
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0.0, int(WINDOW_WIDTH), 0.0, int(WINDOW_HEIGHT), -1, 1);
    // Inicio del dibujo
    if (estadoVisual == TITLE) {
        if (title == 0) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, title0);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(0, 0);
            glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 0);
            glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
            glTexCoord2i(0, 0); glVertex2i(0, WINDOW_HEIGHT);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glutTimerFunc(2000, titleScreen1, 0);// Cambiar a la siguiente pantalla después de 2 segundos
        }
        if (title == 1) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, title1);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(0, 0);
            glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 0);
            glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
            glTexCoord2i(0, 0); glVertex2i(0, WINDOW_HEIGHT);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            renderizarTexto("MIGUEL FIGUEREDO - 2025", (WINDOW_WIDTH / 2) - 140, 10, 2, texturaFuente3);
            glutTimerFunc(2300, titleScreen2, 0);// Cambiar a la siguiente pantalla después de 2 segundos
        }
        if (title == 2) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, title2);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(0, 0);
            glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 0);
            glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
            glTexCoord2i(0, 0); glVertex2i(0, WINDOW_HEIGHT);
            glEnd();
            glDisable(GL_TEXTURE_2D);
            renderizarTexto("MIGUEL FIGUEREDO - 2025", (WINDOW_WIDTH / 2) - 140, 10, 2, texturaFuente3);
			renderizarTexto("PRESS ENTER TO START", (WINDOW_WIDTH / 2) - 300, 100, 3, texturaFuente3);
        }
    }
    if (estadoVisual == SELECCIONPOKEMON) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, background2);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 1); glVertex2i(0, 0);
        glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 0);
        glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
        glTexCoord2i(0, 0); glVertex2i(0, WINDOW_HEIGHT);
        glEnd();
        glDisable(GL_TEXTURE_2D);
		renderizarTexto("SELECT YOUR POKEMON", 185, 470, 4.0f, texturaFuente2);
        dibujarSprite(frame, 100, WINDOW_HEIGHT / 2 - 96, 176, 176, true);
        dibujarSprite(frame, 312, WINDOW_HEIGHT / 2 - 96, 176, 176, true);
        dibujarSprite(frame, 524, WINDOW_HEIGHT / 2 - 96, 176, 176, true);

        // Dibujo de sprites encima de los botones
        dibujarSprite(bulbasaur.texturaID2, 132, WINDOW_HEIGHT / 2 - 66, 115, 115, true);
        dibujarSprite(squirtle.texturaID2, 340, WINDOW_HEIGHT / 2 - 62, 115, 115, true);
        dibujarSprite(charmander.texturaID2, 556, WINDOW_HEIGHT / 2 - 63, 115, 115, true);
        renderizarTexto(bulbasaur.nombre, 109, 158, 3, texturaFuente2);
        renderizarTexto(squirtle.nombre, 330, 158, 3, texturaFuente2);
        renderizarTexto(charmander.nombre, 525, 158, 3, texturaFuente2);
        int fx = 168, fy = 390 + (int)animOffsetJugador, fw = 35, fh = 32 + (int)animOffsetJugador; // Posicion y tamaño de la flecha
        switch (colSelec) {
        case 0:
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, redarrow);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(fx, fy);
            glTexCoord2i(1, 1); glVertex2i(fx + fw, fy);
            glTexCoord2i(1, 0); glVertex2i(fx + fw, fy + fh);
            glTexCoord2i(0, 0); glVertex2i(fx, fy + fh);
            glEnd();
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
            break;
        case 1:
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, redarrow);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(fx+212, fy);
            glTexCoord2i(1, 1); glVertex2i(fx+212 + fw, fy);
            glTexCoord2i(1, 0); glVertex2i(fx+212 + fw, fy + fh);
            glTexCoord2i(0, 0); glVertex2i(fx+212, fy + fh);
            glEnd();
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
            break;
        case 2:
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, redarrow);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(fx+424, fy);
            glTexCoord2i(1, 1); glVertex2i(fx+424 + fw, fy);
            glTexCoord2i(1, 0); glVertex2i(fx+424 + fw, fy + fh);
            glTexCoord2i(0, 0); glVertex2i(fx+424, fy + fh);
            glEnd();
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
            break;
        }
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
        // Dibujo de Pokemones y barras de vida
        dibujarHPJugador(hp_jugador, 400, 160 + (int)animOffsetJugador, 104 * (3.5), (37 * (3.5) + (int)animOffsetJugador), pokeJugador.vida);
        renderizarTexto(pokeJugador.nombre + "*", 455, 238 + (int)animOffsetJugador, 3.0f, texturaFuente2);
        renderizarTexto("5", 715, 241 + (int)animOffsetJugador, 2.6f, texturaFuente2);
        renderizarTexto(to_string(pokeJugador.vida), 645, 184 + (int)animOffsetJugador, 2.4f, texturaFuente1);
        renderizarTexto("/20", 675, 184 + (int)animOffsetJugador, 2.4f, texturaFuente1);
        dibujarHPEnemigo(hp_enemigo, 20, 450, (100 * (3.5)), (29 * (3.5)), pokeEnemigo.vida);
        renderizarTexto(pokeEnemigo.nombre + "*", 50, 502, 3.0f, texturaFuente2);
        renderizarTexto("5", 300, 505, 2.6f, texturaFuente2);
        dibujarPokemon(pokeJugador, 125, 155 + (int)animOffsetJugador, true, 175, 175);
        dibujarPokemon(pokeEnemigo, 525, 325, false, 125, 125);
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

            // Texto en pantalla
            renderizarTexto("What will", 44, 90, 3.0f, texturaFuente3);
            renderizarTexto(pokeJugador.nombre + " do", 44, 37, 3.0f, texturaFuente3);

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
                }
                else if (colSelec == 1) {
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
            renderizarTexto("NORMAL", 645, 32, 3.0f, texturaFuente1);
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
                    renderizarTexto(to_string(pokeJugador.ataque1.pp), 672, 92, 2.8f, texturaFuente1);
                    renderizarTexto(to_string(pokeJugador.ataque1.ppfijo), 735, 92, 2.8f, texturaFuente1);
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
                    renderizarTexto(to_string(pokeJugador.ataque2.pp), 672, 92, 2.8f, texturaFuente1);
                    renderizarTexto(to_string(pokeJugador.ataque2.ppfijo), 735, 92, 2.8f, texturaFuente1);
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
    else if (estadoVisual == ESPERATURNO) {
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
        // Dibujo de Pokemones y barras de vida
        int offsetJugador = 0, offsetEnemigo = 0;
        if (animAtaqueEnCurso) {
            if (animAtaqueJugador) {
                offsetJugador = (int)animAtaqueOffset; // El jugador se mueve hacia el enemigo
            }
            else {
                offsetEnemigo = -(int)animAtaqueOffset; // El enemigo se mueve hacia el jugador
            }
        }
        dibujarHPJugador(hp_jugador, 400, 160, 104 * (3.5), (37 * (3.5)), pokeJugador.vida);
        renderizarTexto(pokeJugador.nombre + "*", 455, 238, 3.0f, texturaFuente2);
        renderizarTexto("5", 715, 241, 2.6f, texturaFuente2);
        renderizarTexto(to_string(pokeJugador.vida), 645, 184, 2.4f, texturaFuente1);
        renderizarTexto("/20", 675, 184, 2.4f, texturaFuente1);
        dibujarHPEnemigo(hp_enemigo, 20, 450, (100 * (3.5)), (29 * (3.5)), pokeEnemigo.vida);
        renderizarTexto(pokeEnemigo.nombre + "*", 50, 502, 3.0f, texturaFuente2);
        renderizarTexto("5", 300, 505, 2.6f, texturaFuente2);
        dibujarPokemon(pokeJugador, 125+offsetJugador+offsetXCircular, 155 + (int)animOffsetJugador+offsetYCircular, true, 175, 175);
        dibujarPokemon(pokeEnemigo, 525+offsetEnemigo, 325, false, 125, 125);
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
        if (estado == TURNOJUGADOR) {
            renderizarTexto(pokeJugador.nombre + " used ", 44, 90, 3.0f, texturaFuente3);
            renderizarTexto(atqJG + "!", 44, 37, 3.0f, texturaFuente3);
        }
        if (estado == TURNOENEMIGO) {
            renderizarTexto(pokeEnemigo.nombre + " used ", 44, 90, 3.0f, texturaFuente3);
            renderizarTexto(atqEN + "!", 44, 37, 3.0f, texturaFuente3);
		}
    }

    else if (estadoVisual == SELECCIONFINCOMBATE) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, background3);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 1); glVertex2i(0, 0);
        glTexCoord2i(1, 1); glVertex2i(WINDOW_WIDTH, 0);
        glTexCoord2i(1, 0); glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
        glTexCoord2i(0, 0); glVertex2i(0, WINDOW_HEIGHT);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        renderizarTexto("PLAY AGAIN", 147, 158, 3.0, texturaFuente3);
        renderizarTexto("QUIT", 525, 158, 3.0, texturaFuente3);
		int fx = 216, fy = 230 + (int)animOffsetJugador, fw = 35, fh = 32 + (int)animOffsetJugador;
        switch (colSelec) {
        case 0:
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, redarrow);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(fx, fy);
            glTexCoord2i(1, 1); glVertex2i(fx + fw, fy);
            glTexCoord2i(1, 0); glVertex2i(fx + fw, fy + fh);
            glTexCoord2i(0, 0); glVertex2i(fx, fy + fh);
            glEnd();
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
            break;
        case 1:
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, redarrow);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 1); glVertex2i(fx + 325, fy);
            glTexCoord2i(1, 1); glVertex2i(fx + 325 + fw, fy);
            glTexCoord2i(1, 0); glVertex2i(fx + 325 + fw, fy + fh);
            glTexCoord2i(0, 0); glVertex2i(fx + 325, fy + fh);
            glEnd();
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
            break;
        }
        if (pokeJugador.vida <= 0) {
            renderizarTexto("YOU HAVE LOST THE BATTLE", 112, 350, 4.0, texturaFuente3);
        } else {
            renderizarTexto("YOU HAVE WON THE BATTLE", 123, 350, 4.0, texturaFuente3);
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
    case TITLESCREEN: 
        if (!pulsado) {
            if (key == 13) {
                volumenMusica(16);
                reproducirSonido("growl", 0);
                glutTimerFunc(1500, cambioTitulo, 0); // Cambiar al estado a selección de Pokémon después de 1 segundo
                pulsado = true;
            }
        }
            break;
    case SELECCION: // Si el estado es de selección de Pokémon
        if (key == 13) { // Si se presiona Enter
            detenerMusica();
            reproducirMusica("battle");
            volumenMusica(32);
            reproducirSonido("select", 0);
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
                    reproducirSonido("select", 0);
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
                    reproducirSonido("select", 0);
                    menuActivo = 0; // Volver al menú principal
                    filaSelec = 0;
                    colSelec = 0;
                    seleccionMenu = true; // Volver al modo de selección de menú
                    ataqueJugador = 0;
                    pokeJugador.ataque1.pp--; // Reducir los PP del ataque
                    if (pokeJugador.velocidad > pokeEnemigo.velocidad || pokeJugador.velocidad == pokeEnemigo.velocidad) {
                        estado = TURNOJUGADOR; // Cambiar al estado de turno del jugador
                        estadoTurno = JUGADOR;
                        ultimoTurno = estado;
                        aplicarTurnos(ataqueJugador); // Llamar a la función de turno del jugador
                    } 
                    else if (pokeEnemigo.velocidad > pokeJugador.velocidad) {
                        estado = TURNOENEMIGO; // Cambiar al estado de turno del enemigo
						estadoTurno = ENEMIGO;
                        ultimoTurno = estado;
                        aplicarTurnos(ataqueJugador); // Llamar a la función de turno del enemigo
                    }
                    seleccionAtq = false; // Desactivar el modo de ataque
					estadoVisual = ESPERATURNO; // Cambiar al estado de espera de turno
                    glutPostRedisplay(); // Redibujar la ventana
                }
                else if (filaSelec == 0 && colSelec == 1) {
                    reproducirSonido("select", 0);
                    ataqueJugador = 1;
                    pokeJugador.ataque2.pp--; // Reducir los PP del ataque
                    if (pokeJugador.velocidad > pokeEnemigo.velocidad || pokeJugador.velocidad == pokeEnemigo.velocidad) {
                        estado = TURNOJUGADOR; // Cambiar al estado de turno del jugador
						estadoTurno = JUGADOR;
                        ultimoTurno = estado;
                        aplicarTurnos(ataqueJugador); // Llamar a la función de turno del jugador
                    }
                    else if (pokeEnemigo.velocidad > pokeJugador.velocidad) {
                        estado = TURNOENEMIGO; // Cambiar al estado de turno del enemigo
                        estadoTurno = ENEMIGO;
                        ultimoTurno = estado;
                        aplicarTurnos(ataqueJugador); // Llamar a la función de turno del enemigo
                    }
                    menuActivo = 0; // Volver al menú principal
                    filaSelec = 0;
                    colSelec = 0;
                    seleccionMenu = true; // Volver al modo de selección de menú
                    seleccionAtq = false; // Desactivar el modo de ataque
                    estadoVisual = ESPERATURNO; // Cambiar al estado de espera de turno
                    glutPostRedisplay(); // Redibujar la ventana
                }
            }
        }

        if (key == 8) {
            reproducirSonido("select", 0);
            estado = MENU;
            menuActivo = 0; // Volver al menú principal
            filaSelec = 0;
            colSelec = 0;
            seleccionMenu = true; // Volver al modo de selección de menú
        }
        break;

    case MENUFIN:
        if (key == 13) {
            if (colSelec == 0) { // Reintentar
                // Reiniciar el juego
                detenerMusica();
                reproducirSonido("select", 0);
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
                reproducirMusica("titles", -1);
                glutPostRedisplay();
                return;
            }
            else if (colSelec == 1) { // Salir
                cerrarAudio();
                glutLeaveMainLoop();
                return;
            }
        }
        break;

        if (key == 8) {
            if (menuActivo == 1) {
                reproducirSonido("select", 0);
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
                reproducirSonido("select", 0);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (colSelec < 2) {
                colSelec++;
                reproducirSonido("select", 0);
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
                reproducirSonido("select", 0);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (colSelec < 1) {
                colSelec++;
                reproducirSonido("select", 0);
            }
            break;
        case GLUT_KEY_UP:
            if (filaSelec > 0) {
                filaSelec--;
                reproducirSonido("select", 0);
            }
            break;
        case GLUT_KEY_DOWN:
            if (filaSelec < 1) {
                filaSelec++;
                reproducirSonido("select", 0);
            }
            break;
        default:
            break;
        }
    }

    else if (estadodeCombate == FINCOMBATE) {
        switch (key) {
        case GLUT_KEY_LEFT:
            if (colSelec > 0) { 
                colSelec--; 
                reproducirSonido("select", 0);
            }
            break;
        case GLUT_KEY_RIGHT:
            if (colSelec < 1) { 
                colSelec++;
                reproducirSonido("select", 0);
            }
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
    
    // Cargar sonidos y musica
    iniciarAudio();
    if (!iniciarAudio()) {
        std::cerr << "No se pudo inicializar el audio, saliendo..." << std::endl;
        exit(1);
    }
	cargarMusica("battle", "assets/Music/battle.mp3");
	cargarMusica("victory", "assets/Music/victory.mp3");
	cargarMusica("titles", "assets/Music/titlescreen.mp3");
    cargarSonido("lowerstat","assets/SFX/bajar.wav");
    cargarSonido("bulbead", "assets/SFX/bulbdead.wav");
	cargarSonido("sqrtdead", "assets/SFX/sqrtdead.wav");
	cargarSonido("chardead", "assets/SFX/chardead.wav");
	cargarSonido("danio", "assets/SFX/danio.wav");
	cargarSonido("growl", "assets/SFX/growl.wav");
	cargarSonido("tailwhip", "assets/SFX/tailwhip.wav");
	cargarSonido("select", "assets/SFX/select.wav");
    cargarSonido("lowhp", "assets/SFX/hpbaja.wav");
    

    // Limpiar pantalla al iniciar
    glutPostRedisplay();
}

void titleScreen1(int value) {
    title = 1;
}

void titleScreen2(int value) {
    title = 2;
    if (estadoVisual == TITLE) {
        estado = TITLESCREEN; // Cambiar al estado de pantalla de título
    }
}

void cambioTitulo(int value) {
    estadoVisual = SELECCIONPOKEMON;
    estado = SELECCION;
    pulsado = false;
    volumenMusica(32);
    glutPostRedisplay();
}