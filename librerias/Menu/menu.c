#include "menu.h"

char menuPrin()
{

    char opcion='z';

    while( (opcion<65 || opcion>67) )
    {
        printf("[A]Jugar\n"
               "[B]Ver ranking equipo\n"
               "[C]Salir\n");
        printf("Opcion: ");
        scanf("%c",&opcion);
        getchar();
        opcion=A_MAYUSCULA(opcion);
    }
    return opcion;
}
