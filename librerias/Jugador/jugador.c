#include "jugador.h"

int compPuntaje(const void*pIzq,const void*pDer)
{
    tJugador *j1=(tJugador*)pIzq,*j2=(tJugador*)pDer;

    return j1->puntaje-j2->puntaje;
}
void resetearPuntajeImprimirNombre(void*p)
{
    tJugador *j=(tJugador*)p;

    j->puntaje=0;
    printf("%s\n",j->nombre);
}
