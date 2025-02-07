#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdio.h>
#define TAM_NOM 21

typedef struct
{
    char nombre[TAM_NOM];
    int puntaje;
    int idJugador;
}tJugador;

int compId(const void*,const void*);
void resetearPuntajeImprimirNombre(void*);
#endif // JUGADOR_H_INCLUDED
