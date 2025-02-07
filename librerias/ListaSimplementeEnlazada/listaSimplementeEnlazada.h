#ifndef LISTASIMPLEMENTEENLAZADA_H_INCLUDED
#define LISTASIMPLEMENTEENLAZADA_H_INCLUDED

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
#define MINIMO(x,y) ((x)<=(y)) ? (x) : (y)
typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo* tLista;
typedef int(*funCmp)(const void*,const void*);
typedef void(*funAct)(void*,const void*);
typedef void(*funAccion)(void*);

void crearLista(tLista*);
void vaciarLista(tLista*);
int insertarOrdenado(tLista*,const void*,unsigned,funCmp,funAct actualizar,bool orden);
bool buscarClave(tLista*,void*,funCmp);
void mapearLista(tLista*,funAccion);

int insertarAlFinal(tLista *iniLista, const void *dato, unsigned tam);
int sacarInicioLista(tLista *iniLista, void *dato, unsigned tam);

#endif // LISTASIMPLEMENTEENLAZADA_H_INCLUDED
