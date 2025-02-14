#include "tLista.h"

void crearLista(tLista* pl)
{
    *pl=NULL;
}
void vaciarLista(tLista* pl)
{
    tNodo *elim;
    while(*pl)
    {
        elim=*pl;
        *pl=elim->sig;
        free(elim->info);
        free(elim);
    }
}
int insertarOrdenado(tLista* pl,const void* info,unsigned tamInfo,funCmp comparar,funAct actualizar,bool orden)
{
    tNodo *nue=malloc(sizeof(tNodo));

    if( nue==NULL || (nue->info=malloc(tamInfo))==NULL )
    {
        free(nue);
        return TE_FALTA_MEMORIA;
    }
    if( orden==MAYOR_A_MENOR )
    {
        while( *pl!=NULL && comparar(info,(*pl)->info)<0 )
            pl=&(*pl)->sig;
    }
    else
    {
        while( *pl!=NULL && comparar(info,(*pl)->info)>0 )
            pl=&(*pl)->sig;
    }
    if( *pl && comparar(info,(*pl)->info)==0 )
    {
        if(actualizar)
            actualizar((*pl)->info,info);
        free(nue->info);
        free(nue);
        return DUPLICADO;
    }
    nue->tamInfo=tamInfo;
    memcpy(nue->info,info,tamInfo);
    nue->sig=*pl;
    *pl=nue;
    return SALIO_BIEN;
}

int insertarAlFinal(tLista *iniLista, const void *dato, unsigned tam){

    tNodo *nuevoNodo = malloc(sizeof(tNodo));

    if(!nuevoNodo){
        return 0;
    }

    nuevoNodo->info = malloc(tam);

    if(nuevoNodo->info == NULL){
        free(nuevoNodo);
        return 0;
    }

    memcpy(nuevoNodo->info, dato, tam);
    nuevoNodo->tamInfo = tam;
    nuevoNodo->sig = NULL;

    while(*iniLista != NULL){ //Recorremos toda la lista hasta encontrar el nodo
                              //que apunte a nulo.
        iniLista = &((*iniLista)->sig);
    }

    *iniLista = nuevoNodo;

    return 1;
}

int sacarInicioLista(tLista *iniLista, void *dato, unsigned tam){
    tNodo *aux;

    if(*iniLista==NULL){
        return 0;
    }

    memcpy(dato, (*iniLista)->info, MINIMO(tam, (*iniLista)->tamInfo));

    aux = *iniLista;

    *iniLista = (*iniLista)->sig;

    free(aux->info);
    free(aux);

    return 1;
}

bool buscarClave(tLista*pLista,void*clave,funCmp comparar)
{
    int resultado=-1;

    while( *pLista && (resultado=comparar(clave,(*pLista)->info))!=0 )
        pLista=&(*pLista)->sig;
    if(resultado!=0)
        return SALIO_MAL;
    return SALIO_BIEN;
}
void mapearLista(tLista*pLista,funAccion accion)
{
    while(*pLista)
    {
        accion((*pLista)->info);
        pLista=&(*pLista)->sig;
    }
}

void mapearListaConArchivo(tLista*pLista, FILE *arch, funAccionConArch accion)
{
    while(*pLista)
    {
        accion((*pLista)->info, arch);
        pLista=&(*pLista)->sig;
    }
}

int insertarOrdenadamente(tLista *lista, const void *dato, unsigned tam, int dup, int cmp(const void*,const void*)){

    int res;

    while(*lista != NULL && (res = cmp((*lista)->info, dato))>0){
        lista = &(*lista)->sig;
    }

    if(res==0 && !dup){
        return 2;
    }

    tNodo *nuevoNodo = malloc(sizeof(tNodo));

    if(!nuevoNodo){
        return 0;
    }

    nuevoNodo->info = malloc(tam);

    if(nuevoNodo->info == NULL){
        free(nuevoNodo);
        return 0;
    }

    memcpy(nuevoNodo->info, dato, tam);
    nuevoNodo->tamInfo = tam;

    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;

    return 1;
}

int listaPonerUlt(tLista* p, void* dato, unsigned tam)
{
    tNodo *nue = malloc(sizeof(tNodo));
    if(!nue)
        return 0;

    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    while(*p)
        p = &(*p)->sig;

    memcpy(nue->info, dato, tam);
    nue->tamInfo = tam;
    nue->sig = NULL;
    *p = nue;
    return 1;
}

int listaPonerOrd(tLista *p, void *d, unsigned tam, CMP cmp)
{
    tNodo *aux = *p;
    tNodo *nue = malloc(sizeof(tNodo));
    if (!nue)
        return 0;

    nue->info = malloc(tam);
    if (!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, d, tam);
    nue->tamInfo = tam;
    nue->sig = NULL;

    if (*p == NULL || cmp(d, (*p)->info) > 0)
    {
        nue->sig = *p;
        *p = nue;
        return 1;
    }

    while (aux->sig && cmp(d, aux->sig->info) <= 0)
    {
        aux = aux->sig;
    }

    nue->sig = aux->sig;
    aux->sig = nue;

    return 1;
}
