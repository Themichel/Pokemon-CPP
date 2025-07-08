#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
using namespace std;

bool iniciarAudio();
void cerrarAudio();

void cargarMusica(const string& nombre, const string& ruta);
void cargarSonido(const string& nombre, const string& ruta);

void reproducirMusica(const string& nombre, int loops = -1);
void volumenMusica(int volumen);
void pausarMusica();
void reanudarMusica();
void detenerMusica();

void reproducirSonido(const string& nombre, int loops);