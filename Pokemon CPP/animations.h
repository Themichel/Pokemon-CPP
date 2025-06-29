#pragma once
extern float animAtaqueOffset;
extern bool animAtaqueEnCurso;
extern bool animAtaqueIda; // true: va hacia el defensor, false: regresa
extern int animAtaqueTurno;   // 0: jugador ataca, 1: enemigo ataca
extern float animOffsetJugador;
extern int animDirJugador;

void animarPokemones(int value);
void animarAtaque(int value2);