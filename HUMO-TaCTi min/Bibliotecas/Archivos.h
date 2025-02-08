#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char url[256];
    char codigoGrupo[10];
    int cantidadPartidas;
}Config;

int leerConfig(const char *nombreArchivo, Config *config);

#endif // ARCHIVOS_H_INCLUDED
