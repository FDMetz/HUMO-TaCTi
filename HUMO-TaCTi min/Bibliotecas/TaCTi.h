#ifndef TACTI_H_INCLUDED
#define TACTI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "tLista.h"
#include "tCola.h"
#include "Jugadores.h"
#include "Archivos.h"

typedef struct
{
    int coord1[2];
    int coord2[2];
    int coord3[2];
}t_coords;

int iniciarPartida(tJugador *jugadorActual, t_cola *cola);
void iniciarJuego(tLista *pl, t_cola *cCoordenadas, int maxPartidas) ;
int cargarCoordenadas(t_cola *cola);
int buscarJugadaIA(t_cola *cola, int tablero[][3]);
void mostrarTablero(int tablero[][3], int fil, int col, int turnoInicial);
void realizarJugadaIA(int *vCoords, unsigned tamVec, int tablero[][3]);
void fichaAlAzar(int tablero[][3]);
int comprobarVictoria(t_cola *cola, int tablero[][3], int idJugador);
char devolverCaracter(int id, int turnoInicial);


#endif // TACTI_H_INCLUDED
