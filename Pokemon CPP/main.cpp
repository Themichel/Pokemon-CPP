#include <GL/freeglut.h>
#include "game.h"
#include "menu.h"
#include "pokemon.h"
#include "textura.h"
#include "animations.h"
#include "fonts.h"
#include "audio.h"
#include <ctime>
int main(int argc, char** argv) {
	srand(static_cast<unsigned int>(time(0))); // Inicializa la semilla del generador de números aleatorios
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pokemon");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    initJuego(); // Inicializa estados
	reproducirMusica("titles", -1);
	volumenMusica(64);
	cargarTexturas(); // Carga las texturas del juego
	glutKeyboardFunc(teclado); // Inicializa teclado
	glutSpecialFunc(teclasEspeciales); // Inicializa teclas especiales
	glutDisplayFunc(display); // Inicializa la funcion de dibujo
	glutTimerFunc(1, animarPokemones, 0); // Inicializa el temporizador de una animacion
	glutMainLoop(); // Inicia el bucle principal de GLUT
    return 0;
}