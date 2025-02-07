#ifndef OPCIONES_H_INCLUDED
#define OPCIONES_H_INCLUDED

#include <time.h>
#include <time.h>
#include "../Jugador/jugador.h"
#include "../ListaSimplementeEnlazada/listaSimplementeEnlazada.h"

#define A_MINUSCULA(A) (A>=65 && A<=90?A+32:A)

int cargarJugadores(tLista*); //Esto tendría que devolver un puntero a lista

#endif // OPCIONES_H_INCLUDED
