#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include "cJSON.h"
#include "Jugadores.h"

typedef struct
{
    char url[256];
    char codigoGrupo[10];
    int cantidadPartidas;
    int estadoMusica;
} Config;

struct string
{
    char *ptr;
    size_t len;
};

int leerConfig(const char *nombreArchivo, Config *config);
void agregarAInforme(FILE *pfInforme, tJugador *jugadorActual, unsigned nJugada, unsigned condicion);
int crearInforme(FILE **pfInforme);

void init_string(struct string *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);
void guardarRanking(tLista *p, const char* urlBase, const char* codigoGrupo);
void obtenerRanking(tLista *lista, const char *urlBase, const char *codigoGrupo);

#endif // ARCHIVOS_H_INCLUDED
