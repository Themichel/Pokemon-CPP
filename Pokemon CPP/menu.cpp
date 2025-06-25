#include "menu.h"
#include "game.h"
#include <GL/freeglut.h>

// Matriz de seleccion de Pokemon
boton menuPokemon[1][3] = {
    {
        {120, WINDOW_HEIGHT / 2 - 60, 150, 150, "Bulbasaur"},
        {320, WINDOW_HEIGHT / 2 - 60, 150, 150, "Squirtle"},
        {520, WINDOW_HEIGHT / 2 - 60, 150, 150, "Charmander"}
    }
};

// Matriz de menu con botones
boton menuMain[2][2] = {
        {
            {420, 90, 150, 60, "Atacar"},
            {620, 90, 150, 60, "Mochila"}
        },
        {
            {420, 20, 150, 60, "Pokemon"},
            {620, 20, 150, 60, "Huir"}
        }
};

boton menuFin[1][2] = {
    {
        {WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2 - 80, 150, 60, "Reintentar"},
        {WINDOW_WIDTH / 2 + 30, WINDOW_HEIGHT / 2 - 80, 150, 60, "Salir"}
    }
};

// Matriz de menu de ataque con botones
boton menuAtq[2][2] = {
    {
        {70, 90, 150, 60,"----"},{270,90,150,60,"----"}

    },
    {
        {70,20,150,60,"----"},{270,20,150,60,"----"}
    }
};

// Variables de control del menu
bool seleccionMenu = true, seleccionAtq = false;
int menuActivo = 0;
int filaSelec = 0, colSelec = 0;

// Funcion para dibujar botones
void dibujarBoton(const boton& b, bool seleccionado) {

    // Chequea si el botón está seleccionado o no
    if (seleccionado) {
        glColor3f(0.0f, 1.0f, 0.0f); // Color verde para el botón seleccionado
    }
    else {
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo para el botón no seleccionado
    }

    // Dibuja el boton tomando los valores de la estructura
    glBegin(GL_QUADS);
    glVertex2i(b.x, b.y);
    glVertex2i(b.x + b.width, b.y);
    glVertex2i(b.x + b.width, b.y + b.height);
    glVertex2i(b.x, b.y + b.height);
    glEnd();

    // Dibuja el texto del boton
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco para el texto
    int text_x = b.x + b.width / 4; // Posición X del texto
    int text_y = b.y + b.height / 2; // Posicion Y del texto
    glRasterPos2d(text_x, text_y); // Posiciona el texto
    for (const char* c = b.texto; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}