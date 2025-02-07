#include "./librerias/FuncionesDeJugar/funcionesDeJugar.h"
#include "./librerias/Menu/menu.h"
#include "./librerias/AlgoritmoJuego/TaCti.h"

int main()
{
    char opcion='a';
    tLista lista;

    crearLista(&lista);
    srand(time(NULL));
    while( A_MAYUSCULA(opcion)!=83)
    {
        opcion=menuPrin();
        switch(opcion)
        {
        case 'A':
            cargarJugadores(&lista);
//            iniciarJuego();
            vaciarLista(&lista); //Para que no quede colgada la lista, más adelante se saca.
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
