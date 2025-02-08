#ifndef TCOLA_H_INCLUDED
#define TCOLA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINIMO(X,Y) (X)<(Y)?(X):(Y)

typedef struct snodo
{
    void *dato;
    unsigned tam;
    struct snodo *s_nodo;
}tc_nodo;

typedef struct{
    tc_nodo *inicio;
    tc_nodo *fin;
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



#endif // TCOLA_H_INCLUDED
