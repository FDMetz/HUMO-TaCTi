#ifndef JUGADORES_H_INCLUDED
#define JUGADORES_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include "tLista.h"
#define TAM_NOM 21
#define A_MINUSCULA(A) (A>=65 && A<=90?A+32:A)

typedef struct
{
    char nombre[TAM_NOM];
    int puntaje;
    int idJugador;
}tJugador;

typedef void (*accion)(void*);

int compId(const void*,const void*);
int compararJugadores(const void *a, const void *b);
void resetearPuntajeImprimirNombre(void*);
int cargarJugadores(tLista *pLista);
int compararPuntos(const void *a, const void *b);
void agregarAInforme(FILE *pfInforme, tJugador *jugadorActual, unsigned nPartida, unsigned condicion);
void agregarRankingAInforme(void *dato, FILE *pfInforme);

void mostrarJug(void* d);
void mostrarRanking(tLista *p);

#endif // JUGADORES_H_INCLUDED
