#include "audio.h"
#include <map>
#include <iostream>
using namespace std;

map <string, Mix_Music*> musics;
map <string, Mix_Chunk*> snds;

bool iniciarAudio() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		cout << "Error al iniciar SDL_mixer: " << Mix_GetError() << endl;
		return false;
	}
	return true;
}

void cerrarAudio() {
	for (auto& m : musics) {
		Mix_FreeMusic(m.second);
	}
	for (auto& s : snds) {
		Mix_FreeChunk(s.second);
	}

	musics.clear();
	snds.clear();

	Mix_CloseAudio();
}

void cargarMusica(const string& nombre, const string& ruta) {
	Mix_Music* musica = Mix_LoadMUS(ruta.c_str());
	if (!musica) {
	cerr << "Error al cargar la música: " << Mix_GetError() << endl;
	} else {
		musics[nombre] = musica;
	}
}

void cargarSonido(const string& nombre, const string& ruta) {
	Mix_Chunk* sonido = Mix_LoadWAV(ruta.c_str());
	if (!sonido) {
		cerr << "Error al cargar el sonido: " << Mix_GetError() << endl;
	} else {
		snds[nombre] = sonido;
	}
}

void reproducirMusica(const string& nombre, int loops) {
	if (musics.count(nombre)) {
		Mix_PlayMusic(musics[nombre], loops);
	}
}

void volumenMusica(int volumen) {
	Mix_VolumeMusic(volumen); // 0 a 128
}

void pausarMusica() {
	Mix_PauseMusic();
}
void reanudarMusica() {
	Mix_ResumeMusic();
}
void detenerMusica() {
	Mix_HaltMusic();
}

void reproducirSonido(const string& nombre, int loops) {
	if (snds.count(nombre)) {
		Mix_PlayChannel(-1, snds[nombre], loops);
	}
}