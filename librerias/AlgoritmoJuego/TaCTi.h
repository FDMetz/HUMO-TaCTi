#ifndef TACTI_H_INCLUDED
#define TACTI_H_INCLUDED

#include "../ListaSimplementeEnlazada/listaSimplementeEnlazada.h"
#include "../PrimitivasCola/PrimitivasCola.h"
#include "../Jugador/jugador.h"

void iniciarJuego(tLista *pl, t_cola *coordenadas);
int cargarCoordenadas(t_cola *cCoordenadas);

#endif // TACTI_H_INCLUDED
