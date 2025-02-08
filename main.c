#include "./librerias/FuncionesDeJugar/funcionesDeJugar.h"
#include "./librerias/Menu/menu.h"
#include "./librerias/AlgoritmoJuego/TaCti.h"
#include "./librerias/PrimitivasCola/PrimitivasCola.h"

int main()
{
    char opcion='a';
    tLista lista;

    crearLista(&lista);
    srand(time(NULL));
    system("cls");
    printf("\033[5;1;36m|-------Bienvenido a TaCTi-------|\n");
    printf("\033[0m");
    while( A_MAYUSCULA(opcion)!=83)
    {
        printf("\nElige una opcion\n");
        opcion=menuPrin();
        switch(opcion)
        {
        case 'A':
            cargarJugadores(&lista);

            t_cola cola;

            crearCola(&cola);

            cargarCoordenadas(&cola); //Buscar como reubicar esto (!)

            iniciarJuego(&lista, &cola);

            vaciarLista(&lista); //Para que no quede colgada la lista, más adelante se saca.
            break;
        case 'B':
            break;
        case 'C':
            printf("Seguro que desea salir del juego?(s/n)\n");
            opcion=getchar();
            while( getchar()!='\n' );
            break;
        }
    }
    return 0;
}
