#include "Bibliotecas/TaCTi.h"

int main()
{

    char opcion;
    int partidaJugada = 0;
    tLista lista;
    t_cola cola;
    Config config;

    // Crear lista y cola
    crearLista(&lista);
    crearCola(&cola);

    // Leer configuración desde el archivo
    if (!leerConfig("config.txt", &config))
    {
        printf("Error al cargar la configuración. Saliendo del programa...\n");
        return;
    }

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

        switch (opcion)
        {
        case 'A':
        case 'a':
            printf("\nCargando jugadores y coordenadas...\n");

            // Cargar jugadores y coordenadas
            cargarJugadores(&lista);

            if(!partidaJugada){
                cargarCoordenadas(&cola);
            }

            // Iniciar el juego con la cantidad de partidas de la configuración
            iniciarJuego(&lista, &cola, config.cantidadPartidas);

            partidaJugada = 1;

            // Vaciar la lista después del juego para evitar datos colgados
            vaciarLista(&lista);
            break;

        case 'B':
        case 'b':
            printf("\nNope.\n");
            break;

        case 'C':
        case 'c':
            printf("\nSaliendo del programa. Hasta luego!\n");
            break;

        default:
            printf("\nOpción no válida. Intente nuevamente.\n");
            printf("\nPresione cualquier tecla para continuar...\n");
            getchar(); // Esperar una tecla para continuar
            break;
        }
    }
    while (opcion != 'C' && opcion != 'c');

    return 1;
}
