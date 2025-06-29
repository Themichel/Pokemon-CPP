#include <GL/freeglut.h>
#include <iostream>
using namespace std;
struct CoordLetras {
	int fila;
	int columna;
};

void renderizarTexto(const string& texto, float x, float y, float escala, GLuint texturaFuente);
void pruebaTextura(GLuint texturaFuente);