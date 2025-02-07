#include "funcionesDeJugar.h"

int cargarJugadores(tLista *pLista)
{
    tJugador juga;
    char *pAux,opc;
    size_t tamReg=sizeof(tJugador);


    do{
    printf("Ingrese nombre: ");
    fgets(juga.nombre,TAM_NOM,stdin);
    pAux=strchr(juga.nombre,'\n');
    if(*pAux)
        *pAux='\0';
    do
    {
        juga.puntaje=rand()%100;
    }while( buscarClave(pLista,&juga,compPuntaje) );
    if( insertarOrdenado(pLista,&juga,tamReg,compPuntaje,NULL,MENOR_A_MAYOR)!=SALIO_BIEN )
    {
        vaciarLista(pLista);
        return TE_FALTA_MEMORIA;
    }
    printf("Ingresar mas jugadores? (s/n) ");
        opc=getchar();
        while( getchar()!='\n' );
    }while(A_MINUSCULA(opc)=='s');
    printf("Orden de los jugadores:\n");
    mapearLista(pLista,resetearPuntajeImprimirNombre);
    return SALIO_BIEN;
}
