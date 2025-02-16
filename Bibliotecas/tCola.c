#include "tCola.h"

void crearCola(t_cola *cola)
{
    cola->fin = NULL;
    cola->inicio = NULL;
}

int agregarCola(t_cola *cola, const void *dato, unsigned tam)
{
    tc_nodo *nuevoNodo = malloc(sizeof(tc_nodo));

    if(NULL == nuevoNodo)
    {
        return 0;
    }

    nuevoNodo->dato = malloc(tam);

    if(NULL == nuevoNodo->dato)
    {
        free(nuevoNodo);
        return 0;
    }

    memcpy(nuevoNodo->dato, dato, tam);
    nuevoNodo->tam = tam;
    nuevoNodo->s_nodo = NULL;

    if(cola->inicio != NULL)
    {
        (cola->fin)->s_nodo = nuevoNodo;
    }
    else
    {
        cola->inicio = nuevoNodo;
    }

    cola->fin = nuevoNodo;

    return 1;
}

int verInicio(t_cola *cola, void *dato, unsigned tam)
{
    if(NULL == cola->inicio)
    {
        return 0;
    }

    memcpy(dato, (cola->inicio)->dato, MINIMO(tam, (cola->inicio)->tam));

    return 1;
}

int quitarDeCola(t_cola *cola, void *dato, unsigned tam)
{

    tc_nodo *aux;

    if(NULL == cola->inicio)
    {
        return 0;
    }

    memcpy(dato, (cola->inicio)->dato, MINIMO(tam, (cola->inicio)->tam));

    aux = cola->inicio;

    cola->inicio = cola->inicio->s_nodo;

    free(aux->dato);

    free(aux);

    return 1;
}

int colaLlena(unsigned tam)
{
    return 1;
}

int colaVacia(t_cola *cola)
{
    return cola->inicio == NULL;
}

void vaciarCola(t_cola *cola)
{

    tc_nodo *aux;

    while(cola->inicio != NULL)
    {
        aux = cola->inicio;
        cola->inicio = cola->inicio->s_nodo;

        free(aux->dato);
        free(aux);
    }

}
