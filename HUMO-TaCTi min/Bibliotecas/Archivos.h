#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jugadores.h"

typedef struct {
    char url[256];
    char codigoGrupo[10];
    int cantidadPartidas;
}Config;

int leerConfig(const char *nombreArchivo, Config *config);
void agregarAInforme(FILE *pfInforme, tJugador *jugadorActual, unsigned nJugada, unsigned condicion);
int crearInforme(FILE **pfInforme);
#endif // ARCHIVOS_H_INCLUDED
