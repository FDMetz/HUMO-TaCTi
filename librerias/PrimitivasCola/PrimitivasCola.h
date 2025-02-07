#ifndef PRIMITIVASCOLA_H_INCLUDED
#define PRIMITIVASCOLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
    void *dato;
    unsigned tam;
    struct nodo *s_nodo;
}t_nodo;

typedef struct{
    t_nodo *inicio;
    t_nodo *fin;
}t_cola;

//1)Crear cola:
void crearCola(t_cola *cola);

//2)Agregar a la cola:
int agregarCola(t_cola *cola, const void *dato, unsigned tam);

//3)Ver inicio de la cola:
int verInicio(t_cola *cola, void *dato, unsigned tam);

//4)Quitar de la cola:
int quitarDeCola(t_cola *cola, void *dato, unsigned tam);

//5)Ver espacio:
int colaLlena(unsigned tam);

//6)Cola vacia:
int colaVacia(t_cola *cola);

//7)Vaciar cola:
void vaciarCola(t_cola *cola);



#endif // PRIMITIVASCOLA_H_INCLUDED
