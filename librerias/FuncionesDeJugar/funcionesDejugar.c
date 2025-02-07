#include "funcionesDeJugar.h"
#include <windows.h>
int cargarJugadores(tLista *pLista)
{
    tJugador juga;
    char *pAux,opc;
    size_t tamReg=sizeof(tJugador);


    do{
    system("cls");
    printf("Ingrese nombre: ");
    fgets(juga.nombre,TAM_NOM,stdin);
    pAux=strchr(juga.nombre,'\n');
    if(*pAux)
        *pAux='\0';
    do
    {
        juga.idJugador = rand()%100;
    }while( buscarClave(pLista,&juga,compId) );

    if( insertarOrdenado(pLista,&juga,tamReg,compId,NULL,MENOR_A_MAYOR)!=SALIO_BIEN )
    {
        vaciarLista(pLista);
        return TE_FALTA_MEMORIA;
    }

    printf("Ingresar mas jugadores? (s/n): ");
        opc=getchar();
        while( getchar()!='\n' );
    }while(A_MINUSCULA(opc)=='s');

    system("cls");
    printf("Orden de los jugadores:\n");
    mapearLista(pLista,resetearPuntajeImprimirNombre);
    system("pause");
    return SALIO_BIEN;
}
