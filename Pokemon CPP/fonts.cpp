#include "fonts.h"
#include <map>
#include <string>
#include <iostream>
using namespace std;

map<char, CoordLetras> mapaFuente = {
    // Fila 0 - A-Z
    {'A', {0, 0}}, {'B', {0, 1}}, {'C', {0, 2}}, {'D', {0, 3}}, {'E', {0, 4}}, {'F', {0, 5}},
    {'G', {0, 6}}, {'H', {0, 7}}, {'I', {0, 8}}, {'J', {0, 9}}, {'K', {0,10}}, {'L', {0,11}},
    {'M', {0,12}}, {'N', {0,13}}, {'O', {0,14}}, {'P', {0,15}}, {'Q', {0,16}}, {'R', {0,17}},
    {'S', {0,18}}, {'T', {0,19}}, {'U', {0,20}}, {'V', {0,21}}, {'W', {0,22}}, {'X', {0,23}},
    {'Y', {0,24}}, {'Z', {0,25}},

    // Fila 1 - a-z
    {'a', {1, 0}}, {'b', {1, 1}}, {'c', {1, 2}}, {'d', {1, 3}}, {'e', {1, 4}}, {'f', {1, 5}},
    {'g', {1, 6}}, {'h', {1, 7}}, {'i', {1, 8}}, {'j', {1, 9}}, {'k', {1,10}}, {'l', {1,11}},
    {'m', {1,12}}, {'n', {1,13}}, {'o', {1,14}}, {'p', {1,15}}, {'q', {1,16}}, {'r', {1,17}},
    {'s', {1,18}}, {'t', {1,19}}, {'u', {1,20}}, {'v', {1,21}}, {'w', {1,22}}, {'x', {1,23}},
    {'y', {1,24}}, {'z', {1,25}},

    // Fila 2 - números y símbolos
    {'0', {2, 0}}, {'1', {2, 1}}, {'2', {2, 2}}, {'3', {2, 3}}, {'4', {2, 4}}, {'5', {2, 5}},
    {'6', {2, 6}}, {'7', {2, 7}}, {'8', {2, 8}}, {'9', {2, 9}}, {'!', {2,10}}, {'?', {2,11}},
    {'.', {2,12}}, {'-', {2,13}}, {'/', {2,14}}
};

void renderizarTexto(const string& texto, float x, float y, float escala, GLuint texturaFuente) {
    const int columnas = 26;
    const int filas = 3;
    const int letraAncho = 6;
    const int letraAlto = 11;
    const int texturaAncho = 156;
    const int texturaAlto = 33;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaFuente);

    float cursorX = x;

    for (char c : texto) {
        if (c == ' ') {
            cursorX += letraAncho * escala; // Espacio manual
            continue;
        }

        if (mapaFuente.count(c) == 0) continue;

        CoordLetras coord = mapaFuente[c];

        // Calcular coordenadas UV
        float u1 = (coord.columna * letraAncho) / float(texturaAncho);
        float u2 = ((coord.columna + 1) * letraAncho) / float(texturaAncho);
        float v1 = (coord.fila * letraAlto) / float(texturaAlto);
        float v2 = ((coord.fila + 1) * letraAlto) / float(texturaAlto);

        float w = letraAncho * escala;
        float h = letraAlto * escala;
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(u1, v2); glVertex2f(cursorX, y);
        glTexCoord2f(u2, v2); glVertex2f(cursorX + w, y);
        glTexCoord2f(u2, v1); glVertex2f(cursorX + w, y + h);
        glTexCoord2f(u1, v1); glVertex2f(cursorX, y + h);
        glEnd();
        cursorX += w;
    }
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}