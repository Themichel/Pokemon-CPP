#pragma once
extern float animAtaqueOffset;
extern bool animAtaqueEnCurso;
extern bool animAtaqueIda; // true: va hacia el defensor, false: regresa
extern int animAtaqueTurno;   // 0: jugador ataca, 1: enemigo ataca
extern float animOffsetJugador;
extern int animDirJugador;
extern bool animAtaqueJugador;
extern bool animCircularEnCurso;
extern bool animCircularJugador;
extern float animAnguloCircular;
extern float animRadioCircular;
extern float offsetXCircular;
extern float offsetYCircular;

void animarPokemones(int value);
void animarAtaque1(int value);
void animarAtaque2(int value);
void animarCircularJugador1(int value);
void animarCircularJugador2(int value);