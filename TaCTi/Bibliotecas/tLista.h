#ifndef TLISTA_H_INCLUDED
#define TLISTA_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TE_FALTA_MEMORIA -1
#define MAYOR_A_MENOR 1
#define MENOR_A_MAYOR 0
#define SALIO_BIEN 1
#define SALIO_MAL 0
#define DUPLICADO 2
#define MINIMO(X,Y) (X)<(Y)?(X):(Y)

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;
typedef tNodo* tLista;

typedef int(*CMP)(const void*, const void*);
typedef int(*funCmp)(const void*,const void*);
typedef void(*funAct)(void*,const void*);
typedef void(*funAccion)(void*);
typedef void(*funAccionConArch)(void*, FILE*);

void crearLista(tLista*);
void vaciarLista(tLista*);
int insertarOrdenado(tLista*,const void*,unsigned,funCmp,funAct actualizar,bool orden);
bool buscarClave(tLista*,void*,funCmp);
void mapearLista(tLista*,funAccion);
void mapearListaConArchivo(tLista*, FILE*, funAccionConArch);

int insertarAlFinal(tLista *iniLista, const void *dato, unsigned tam);
int sacarInicioLista(tLista *iniLista, void *dato, unsigned tam);
int insertarOrdenadamente(tLista *lista, const void *dato, unsigned tam, int dup, int cmp(const void*,const void*));

int listaPonerUlt(tLista* p, void* dato, unsigned tam);
int listaPonerOrd(tLista *p, void *d, unsigned tam, CMP cmp);

#endif // TLISTA_H_INCLUDED
