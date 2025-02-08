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

int compId(const void*,const void*);
void resetearPuntajeImprimirNombre(void*);
int cargarJugadores(tLista *pLista);

#endif // JUGADORES_H_INCLUDED
