#include <GL/freeglut.h>
#include "game.h"
#include "menu.h"
#include "pokemon.h"
#include "textura.h"
#include <ctime>
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pokemon");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    initJuego(); // Inicializa texturas y estados
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclasEspeciales);
    glutDisplayFunc(display);
    glutTimerFunc(1, animarPokemones, 0);
    glutMainLoop();
    return 0;
}