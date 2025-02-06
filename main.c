#include <stdlib.h>
#include "menu.h"

int main()
{
    char opcion='a';

    while( A_MAYUSCULA(opcion)!=83)
    {
        opcion=menuPrin();
        switch(opcion)
        {
        case 'A':
            break;
        case 'B':
            break;
        case 'C':
            printf("Seguro que desea salir del juego?(s/n)\n");
            scanf("%c",&opcion);
            getchar();
            break;
        }
    }
    return 0;
}
