#include "Jugadores.h"

int compId(const void*pIzq,const void*pDer)
{
    tJugador *j1=(tJugador*)pIzq,*j2=(tJugador*)pDer;

    return j1->idJugador-j2->idJugador;
}

int compararJugadores(const void *a, const void *b)
{
    const tJugador *j1 = (const tJugador *)a;
    const tJugador *j2 = (const tJugador *)b;

    return j1->puntaje - j2->puntaje;
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

void agregarAInforme(FILE *pfInforme, tJugador *jugadorActual, unsigned nPartida, unsigned puntos){

    char condicionTxt[10];

    if(nPartida-1 == 0){ //Si es la primera partida jugada agregamos el encabezado
        fprintf(pfInforme, "--------- RESUMEN DE PARTIDAS JUGADAS POR %s ---------\n", jugadorActual->nombre);
    }

    switch(puntos){
        case -1:
            strcpy(condicionTxt, "Perdió");
        break;
        case 2:
            strcpy(condicionTxt, "Empató");
        break;
        case 3:
            strcpy(condicionTxt, "Ganó");
        break;
    }

    fprintf(pfInforme, "- Partida %2d | Condición: %-7s | Puntos: %d\n", nPartida, condicionTxt, puntos);
}


void agregarRankingAInforme(void *dato, FILE *pfInforme){
    tJugador *jugador = (tJugador*)dato;
    fprintf(pfInforme, "Jugador: %-21s | Puntos: %d\n", jugador->nombre, jugador->puntaje);
}


void mostrarJug(void* d)
{
    tJugador jug = *(tJugador*)d;

    printf("JUGADOR: %s | PUNTAJE: %3d | ID: %d\n",jug.nombre,jug.puntaje, jug.idJugador);
}

void mostrarRanking(tLista *p)
{
    int i = 1;
    tJugador jug;

    while(*p)
    {
        sacarInicioLista(p, &jug, sizeof(tJugador));
        printf("LUGAR NRO %d -> JUGADOR: %-21s | PUNTAJE: %3d | ID: %d\n", i, jug.nombre,jug.puntaje, jug.idJugador);
        i++;
    }
}
