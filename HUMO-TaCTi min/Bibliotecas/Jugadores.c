#include "Jugadores.h"

int compId(const void*pIzq,const void*pDer)
{
    tJugador *j1=(tJugador*)pIzq,*j2=(tJugador*)pDer;

    return j1->idJugador-j2->idJugador;
}
void resetearPuntajeImprimirNombre(void*p)
{
    tJugador *j=(tJugador*)p;

    j->puntaje=0;

    printf("- %s\n",j->nombre);
}

int cargarJugadores(tLista *pLista)
{
    tJugador juga;
    char *pAux,opc;
    size_t tamReg=sizeof(tJugador);


    do
    {
        system("cls");
        printf("Ingrese Nombre del Jugador: ");
        fgets(juga.nombre,TAM_NOM,stdin);
        pAux=strchr(juga.nombre,'\n');
        if(*pAux)
            *pAux='\0';
        do
        {
            juga.idJugador = rand()%100;
        }
        while( buscarClave(pLista,&juga,compId) );

        if( insertarOrdenado(pLista,&juga,tamReg,compId,NULL,MENOR_A_MAYOR)!=SALIO_BIEN )
        {
            vaciarLista(pLista);
            return TE_FALTA_MEMORIA;
        }

        printf("\nIngresar Mas Jugadores? (s/n): ");
        opc=getchar();
        while(getchar()!='\n' );
    }
    while(A_MINUSCULA(opc)=='s');

    system("cls");
    printf("Orden de los Jugadores:\n");
    mapearLista(pLista,resetearPuntajeImprimirNombre);
    printf("\nPresione cualquier tecla para continuar...\n");
    getchar(); // Esperar una tecla para continuar
    //getchar(); // Asegurar que no se salte por buffer

    return SALIO_BIEN;
}

int compararPuntos(const void *a, const void *b){
  return ((tJugador*)a)->puntaje - ((tJugador*)b)->puntaje;
}

void agregarAInforme(FILE *pfInforme, tJugador *jugadorActual, unsigned nPartida, unsigned condicion){

    char condicionTxt[10];
    int puntos;

    if(nPartida-1 == 0){
        fprintf(pfInforme, "Partidas jugadas por %s:\n", jugadorActual->nombre);
    }

    switch(condicion){
        case 0:
            strcpy(condicionTxt, "Empató");
            puntos = 2;
        break;
        case 1:
            strcpy(condicionTxt, "Ganó");
            puntos = 3;
        break;
        case 2:
            strcpy(condicionTxt, "Perdió");
            puntos = -1;
        break;
    }

    fprintf(pfInforme, "- Partida %d | Condición: %s | Puntos: %d\n", nPartida, condicionTxt, puntos);
}
void agregarRankingAInforme(void *dato, FILE *pfInforme){
    tJugador *jugador = (tJugador*)dato;
    fprintf(pfInforme, "Jugador: %s | Puntos: %d\n", jugador->nombre, jugador->puntaje);
}

