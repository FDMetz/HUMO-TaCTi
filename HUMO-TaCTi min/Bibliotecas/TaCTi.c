#include "TaCTi.h"

void menu()
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

    printf("\033[5;1;36m|<><><><><>|\033[5;1;35mBienvenidos a TaCTi\033[5;1;36m|<><><><><>|\n\033[0m");

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
}

void iniciarJuego(tLista *pl, t_cola *cCoordenadas, int maxPartidas)
{
    int i;
    tJugador *jugadorInicial = malloc(sizeof(tJugador));
    tJugador *jugadorActual = malloc(sizeof(tJugador));

    // Sacar al primer jugador de la lista
    sacarInicioLista(pl, jugadorActual, sizeof(tJugador));
    memcpy(jugadorInicial, jugadorActual, sizeof(tJugador));

    do
    {
        // Cada jugador juega la cantidad de partidas especificada
        for (i = 0; i < maxPartidas; i++)
        {
            iniciarPartida(jugadorActual, cCoordenadas);
        }
        // Reinsertar el jugador al final de la lista
        insertarAlFinal(pl, jugadorActual, sizeof(tJugador));
    }
    while (sacarInicioLista(pl, jugadorActual, sizeof(tJugador)) &&
            (jugadorInicial->idJugador != jugadorActual->idJugador));

    free(jugadorActual);
    free(jugadorInicial);
}

int iniciarPartida(tJugador *jugadorActual, t_cola *cCoordenadas)
{
    srand(time(NULL));

    int tablero[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    int coordenadaX;
    int coordenadaY;
    int nJugada = 0;
    int victoria = 0;
    int turno = rand() % 2; // 0 -> Empieza el usuario || 1 -> Empieza la IA
    int turnoInicial = turno;


    while(nJugada < 9 && !victoria)  //El máximo de movimientos es 9
    {
        if(turno == 0)
        {
            system("cls");
            printf("[Es el turno de \033[1;36m%s\033[0m - PUNTAJE ACTUAL: %d]\n", jugadorActual->nombre, jugadorActual->puntaje);
            mostrarTablero(tablero, 3, 3, turnoInicial);
            printf("\nJuega con el simbolo: %c\n", devolverCaracter(1, turnoInicial));
            do
            {
                do{
                    printf("Seleccione una coordenada \033[0;35mY\033[0m del tablero: ");
                    scanf("%d", &coordenadaY);
                    getchar();
                }while(coordenadaY!=0 && coordenadaY!=1 && coordenadaY !=2);

                do{
                    printf("Seleccione una coordenada \033[1;34mX\033[0m del tablero: ");
                    scanf("%d", &coordenadaX);
                    getchar();
                }while(coordenadaX!=0 && coordenadaX!=1 && coordenadaX !=2);

                printf("\n");
            }
            while(tablero[coordenadaY][coordenadaX]!=0);  //Si el casillero está ocupado le pedimos que ingrese otra coordenada


            tablero[coordenadaY][coordenadaX] = 1;

            if(nJugada>=4+turnoInicial)  //Apartir de 4ta o 5ta jugada (depende de quien empieza) el usuario puede comprobar si gano
            {
                if(comprobarVictoria(cCoordenadas, tablero, 1))  //Se pasa el numero que se quiere comprobar si completa una linea en el tablero
                {
                    victoria = 1;
                    jugadorActual->puntaje += 3;

                    system("cls");
                    printf("\033[1;32m!Gana %s! +3 PUNTOS --> PUNTAJE ACTUAL: %d\n\033[1;37m", jugadorActual->nombre, jugadorActual->puntaje);
                    mostrarTablero(tablero, 3, 3, turnoInicial);
                    printf("\nPresione cualquier tecla para continuar...\n");
                    getchar(); // Esperar una tecla para continuar
                }
            }
            turno = 1;
        }
        else
        {
            if(!victoria && nJugada < 9)  //Si no gano el usuario con el movimiento anterior y la jugada no fue la ultima (nJugada<9)
            {
                if(nJugada < 3 + turnoInicial)  //Si el turno inicial es del usuario (turno=0) entonces antes de 3 + 0 = 3 no hay posibilidad de bloqueo o de victoria.
                {
                    //Si el turno inicial es de la IA (turno=1) entonces antes de 3 + 1 = 4 no hay posibiidad de bloqueo o de victoria.
                    fichaAlAzar(tablero);
                }
                else
                {
                    if(!buscarJugadaIA(cCoordenadas, tablero))
                    {
                        fichaAlAzar(tablero);
                    }
                    else
                    {
                        if(comprobarVictoria(cCoordenadas, tablero, 2))
                        {
                            jugadorActual->puntaje -= 1;
                            victoria = 1;

                            system("cls");
                            printf("\033[1;31m!Gana la IA! -1 PUNTOS --> PUNTAJE ACTUAL: %d\n\033[1;37m", jugadorActual->puntaje);
                            mostrarTablero(tablero, 3, 3, turnoInicial);
                            printf("\nPresione cualquier tecla para continuar...\n");
                            getchar(); // Esperar una tecla para continuar
                        }
                    }
                }
            }
            turno = 0;
        }

        nJugada++;
    }

    if(!victoria)
    {
        jugadorActual->puntaje += 2;
        system("cls");
        printf("\033[1;33mSE PRODUJO UN EMPATE! +2 PUNTOS --> PUNTAJE ACTUAL: %d\n\033[1;37m", jugadorActual->puntaje);
        mostrarTablero(tablero, 3, 3, turnoInicial);
        printf("\nPresione cualquier tecla para continuar...\n");
        getchar(); // Esperar una tecla para continuar
    }

    return 0;
}

int comprobarVictoria(t_cola *cCoordenadas, int tablero[][3], int idJugador)
{

    int victoria = 0;
    int i = 0;
    int x1, y1, x2, y2, x3, y3; //Representan las posiciones de la matriz

    t_coords *coords = malloc(sizeof(t_coords));

    while(i<9 && !victoria)  //9 es la maxima cantidad de lineas posibles.
    {
        quitarDeCola(cCoordenadas, coords, sizeof(t_coords)); //Recuperamos las coordenadas
        agregarCola(cCoordenadas, coords, sizeof(t_coords));  //Las volvemos a agregar para no perderlas

        y1 = (coords->coord1)[0];
        x1 = (coords->coord1)[1];
        y2 = (coords->coord2)[0];
        x2 = (coords->coord2)[1];
        y3 = (coords->coord3)[0];
        x3 = (coords->coord3)[1];

        if(tablero[y1][x1] == idJugador && tablero[y2][x2] == idJugador && tablero[y3][x3] == idJugador)  //Si todas las coordenadas de la línea tienen
        {
            //el numero del jugador => ganó
            victoria = 1;
        }

        i++;
    }

    free(coords);

    return victoria;
}

int buscarJugadaIA(t_cola *cCoordenadas, int tablero[][3])
{

    int i = 0;
    int j;
    int contadorIA = 0;
    int contadorUser = 0;
    int jugadaVictoria = 0;
    int jugadaBloqueo = 0;
    unsigned tamVec = 6;
    int vCoords[tamVec];
    int vCoordsBloqueo[tamVec];

    t_coords *coords = (t_coords*)malloc(sizeof(t_coords));

    if(!coords)
    {
        return 0;
    }

    while(!jugadaVictoria && i<9)  //Mientras no haya una jugada de victoria y no se hayan recorrido todas las lineas
    {
        //Coordenadas de una linea, ej: {0,0}   {1,0}   {2,0} -> columna1
        //{y1,x1} {y2,x2} {y3,x3}
        quitarDeCola(cCoordenadas, coords, sizeof(t_coords)); //Recuperamos las coordenadas de la cCoordenadas
        agregarCola(cCoordenadas, coords, sizeof(t_coords));  //Las volvemos a agregar al final para no perderlas

        vCoords[0] = (coords->coord1)[0];
        vCoords[1] = (coords->coord1)[1];
        vCoords[2] = (coords->coord2)[0];
        vCoords[3] = (coords->coord2)[1];
        vCoords[4] = (coords->coord3)[0];
        vCoords[5] = (coords->coord3)[1];

        for(j=0; j<tamVec; j+=2)
        {
            if(tablero[vCoords[j]][vCoords[j+1]]==1)
            {
                contadorUser++;
            }
            else if(tablero[vCoords[j]][vCoords[j+1]]==2)
            {
                contadorIA++;
            }
        }

        if(contadorIA == 2 && contadorUser == 0)  //Si la IA tiene 2 casilleros ocupados hacemos que ocupe el que queda para ganar
        {
            realizarJugadaIA(vCoords, tamVec, tablero);
            jugadaVictoria = 1;
        }
        else if(contadorIA == 0 && contadorUser == 2)   //Si es al revés guardamos las coordenadas de bloqueo para seguir buscando una linea de victoria
        {
            memcpy(vCoordsBloqueo, vCoords, sizeof(vCoords));
            jugadaBloqueo = 1;
        }

        contadorIA = 0;
        contadorUser = 0;

        i++;
    }

    if(jugadaBloqueo && !jugadaVictoria)
    {
        realizarJugadaIA(vCoordsBloqueo, tamVec, tablero);
    }

    free(coords);

    return (jugadaBloqueo || jugadaVictoria);
}

void realizarJugadaIA(int *vCoords, unsigned tamVec, int tablero[][3])
{
    int i = 0;

    while(i<tamVec && tablero[*(vCoords+i)][*(vCoords+i+1)] != 0)  //Buscamos el lugar disponible dentro de esa linea
    {
        i+=2;
    }

    tablero[*(vCoords+i)][*(vCoords+i+1)] = 2;
}

int cargarCoordenadas(t_cola *cCoordenadas)
{

    FILE *pf;

    pf = fopen("Bibliotecas/coordenadas.dat", "rb");

    if(!pf)
    {
        return 0;
    }

    t_coords *coord = malloc(sizeof(t_coords));

    fread(coord, sizeof(t_coords), 1, pf);

    while(!feof(pf))
    {
        agregarCola(cCoordenadas, coord, sizeof(t_coords));
        fread(coord, sizeof(t_coords), 1, pf);
    }

    fclose(pf);
    free(coord);

    return 1;
}


void fichaAlAzar(int tablero[][3])
{
    int xRand = rand() % 3;
    int yRand = rand() % 3;

    while(tablero[xRand][yRand]!=0)
    {
        xRand = rand() % 3;
        yRand = rand() % 3;
    }

    tablero[xRand][yRand] = 2;
}

void mostrarTablero(int tablero[][3], int fil, int col, int turnoInicial)
{
    int i, j;

    // Imprimir encabezados de columnas
    printf("\n");
    printf("\033[1;34m                0     1     2\n\033[0m");

    printf("             -------------------\n");

    for (i = 0; i < fil; i++)
    {
        // Etiqueta de fila
        printf("\033[0;35m           %d \033[0m|", i);

        for (j = 0; j < col; j++)
        {
            // Imprime el valor del tablero usando devolverCaracter()
            printf("  %c  |", devolverCaracter(tablero[i][j], turnoInicial)); //La función ya devuelve y poner directamente el ' ', no hay que comprobarlo y ponerlo manualmente
        }

        printf("\n");
        if(i<fil-1){
            printf("             ------+-----+------\n"); // Línea entre filas
        }else{
            printf("             -------------------\n");
        }

    }

    printf("\n");
}

char devolverCaracter(int id, int turnoInicial)
{
    if((id == 1 && turnoInicial == 0) || (id == 2 && turnoInicial == 1))
    {
        return 'X';
    }
    else if((id == 1 && turnoInicial == 1) || (id == 2 && turnoInicial == 0))
    {
        return 'O';
    }
    else
    {
        return ' ';
    }
}
