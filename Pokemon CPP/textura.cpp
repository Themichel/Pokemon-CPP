#define STB_IMAGE_IMPLEMENTATION
#include <C:\Users\themi\Documents\Proyectos C++\Pokemon CPP\Pokemon CPP\include\stb_image.h>
#include <GL/freeglut.h>
#include <iostream>
using namespace std;

GLuint cargarTexturaDesdePNG(const char* ruta) {
    int ancho, alto, canales;
    unsigned char* data = stbi_load(ruta, &ancho, &alto, &canales, STBI_rgb_alpha);
    if (!data) {
        std::cerr << "Error cargando " << ruta << std::endl;
        exit(1);
    }
    else {
        std::cout << "Textura cargada: " << ruta << " (" << ancho << "x" << alto << ")" << std::endl;
    }
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);
    return id;
}