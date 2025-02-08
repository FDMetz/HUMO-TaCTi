#include "Bibliotecas/TaCTi.h"

int main()
{
    char opcion;
    int juegoIniciado = 0;
    tLista lista;
    crearLista(&lista);
    t_cola cola;
    crearCola(&cola);
    srand(time(NULL));
    system("cls");

    printf("\033[5;1;36m|------- Bienvenido a TaCTi -------|\n");
    printf("\033[0m");

    do
    {
        printf("[A] Jugar\n");
        printf("[B] Ver ranking equipo\n");
        printf("[C] Salir\n");
        printf("\n");
        printf("Seleccione una opcion: ");
        scanf("%c", &opcion);
        getchar();

        switch(opcion)
        {
        case 'A':
        case 'a':
            cargarJugadores(&lista);
            if(!juegoIniciado){
                cargarCoordenadas(&cola);
            }
            iniciarJuego(&lista, &cola);
            vaciarLista(&lista); //Para que no quede colgada la lista, más adelante se saca.
            break;

        case 'B':
        case 'b':
            break;

        case 'C':
        case 'c':
            printf("\nSaliendo del programa. Hasta luego!\n");
            break;

        default:
            printf("\nOpcion no valida. Intente nuevamente.\n");
            printf("\nPresione cualquier tecla para continuar...\n");
            getchar(); // Esperar una tecla para continuar
            getchar(); // Asegurar que no se salte por buffer
            break;
        }
    }
    while (opcion != 'C' && opcion != 'c');

    return 1;
}
