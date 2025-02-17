#include "TaCTi.h"

void menu()
{
    char opcion;
    int partidaJugada = 0;
    tLista listaJugadores;
    tLista listaRanking;
    tLista listaRankingAPI;
    t_cola cola;
    Config config;

    // Crear listaJugadores y cola
    crearLista(&listaJugadores);
    crearLista(&listaRanking); //Ranking para el informe local
    crearLista(&listaRankingAPI); //Ranking para la API
    crearCola(&cola);

    // Leer configuración desde el archivo
    if (!leerConfig("config.txt", &config))
    {
        printf("Error al cargar la configuración. Saliendo del programa...\n");
        return;
    }

    srand(time(NULL));

    do
    {
        if(config.estadoMusica)
        {
            reproducirSonido("song1", 1);
        }


        system("cls");
        printf("\033[5;1;36m|<><><><><>|\033[5;1;35m Bienvenidos a Ta-C-Ti \033[5;1;36m|<><><><><>|\n\033[0m\n");
        printf("[A] Jugar\n");
        printf("[B] Ver ranking equipo\n");
        printf("[C] Salir\n");
        printf("\n");
        printf("Seleccione una opcion: ");
        scanf("%c", &opcion);

        while(getchar()!='\n');

        switch (opcion)
        {
        case 'A':
        case 'a':
            reproducirSonido("op3", 0);
            printf("\nCargando jugadores y coordenadas...\n");

            // Cargar jugadores y coordenadas
            cargarJugadores(&listaJugadores);

            if(!partidaJugada)
                cargarCoordenadas(&cola);

            if(config.estadoMusica)
            {
                reproducirSonido("song2", 1);
            }

            // Iniciar el juego con la cantidad de partidas de la configuración
            iniciarJuego(&listaJugadores, &listaRanking, &cola, config.cantidadPartidas);
            partidaJugada = 1;
            guardarRanking(&listaRanking, config.url, config.codigoGrupo); //Guardar los jugadores en la API

            // Vaciar la listaJugadores después del juego para evitar datos colgados
            vaciarLista(&listaJugadores);
            vaciarLista(&listaRanking);
            break;

        case 'B':
        case 'b':
            mutearSonido();
            system("cls");
            printf("\033[0;33m|[][][][][]|\033[1;33m RANKING DE JUGADORES \033[0;33m|[][][][][]|\n\033[0m\n");

            obtenerRanking(&listaRankingAPI, config.url, config.codigoGrupo); //Obtener los jugadores desde la API
            mostrarRanking(&listaRankingAPI);

            reproducirSonido("op2", 0);
            vaciarLista(&listaRankingAPI);
            printf("\nPresione cualquier tecla para continuar...\n");
            getchar(); // Esperar una tecla para continuar
            break;

        case 'C':
        case 'c':
            system("cls");
            printf("\033[1;37m%30s\n\nEsto fue una creacion del grupo HUMO - UNLaM \n\033[0m", "!Gracias por jugar!");
            break;

        default:
            system("cls");
            printf("Opcion no valida. Intente nuevamente.\n");
            printf("\nPresione cualquier tecla para continuar...\n");
            getchar(); // Esperar una tecla para continuar
            break;
        }
    }
    while (opcion != 'C' && opcion != 'c');
}

int iniciarJuego(tLista *pl, tLista *listaRanking, t_cola *cCoordenadas, int maxPartidas)
{
    int i;
    int puntos;
    int idJugadorInicial;
    unsigned tamJugador = sizeof(tJugador);
    tJugador *jugadorActual = malloc(tamJugador);

    if(!jugadorActual)
    {
        printf("No se pudo iniciar el juego...");
        return 0;
    }

    //Creación del archivo informe
    FILE *pfInforme;

    if(!crearInforme(&pfInforme))
    {
        printf("No se pudieron crear los archivos del juego...");
        return 0;
    }

    // Sacar al primer jugador de la lista
    sacarInicioLista(pl, jugadorActual, tamJugador);

    idJugadorInicial = jugadorActual->idJugador;

    do
    {
        // Cada jugador juega la cantidad de partidas especificada
        for (i = 0; i < maxPartidas; i++)
        {
            puntos = iniciarPartida(jugadorActual, cCoordenadas, pfInforme, i+1);
            agregarAInforme(pfInforme, jugadorActual, i+1, puntos);//Agregamos al informe los datos de esta partida
        }

        fprintf(pfInforme, "Puntos totales: %d\n\n", jugadorActual->puntaje); //Esta bien usarlo asi? (!)
        // Reinsertar el jugador al final de la lista
        insertarAlFinal(pl, jugadorActual, tamJugador);
        //Inseratamos ordenadamente al jugador en la lista del ranking:
        insertarOrdenadamente(listaRanking, jugadorActual, tamJugador, 1, compararPuntos);
    }
    while (sacarInicioLista(pl, jugadorActual, tamJugador) &&
            (idJugadorInicial != jugadorActual->idJugador));

    fprintf(pfInforme, "Resultado final:\n");
    mapearListaConArchivo(listaRanking, pfInforme, agregarRankingAInforme); // Leemos la lista y la cargamos en el archivo

    free(jugadorActual);
    fclose(pfInforme);

    return 1;
}

int iniciarPartida(tJugador *jugadorActual, t_cola *cCoordenadas, FILE *pfInforme, unsigned nPartida)
{
    srand(time(NULL));

    int tablero[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    int coordenadaX=-1;
    int coordenadaY=-1;
    int nJugada = 0;
    int victoria = 0;
    int turno = rand() % 2; // 0 -> Empieza el usuario || 1 -> Empieza la IA
    int turnoInicial = turno;
    int puntos = 0;


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
                do
                {
                    printf("Seleccione una coordenada \033[0;35mY\033[0m del tablero: ");
                    scanf("%d", &coordenadaY);
                    while( getchar()!='\n');
                }
                while(coordenadaY<0 || coordenadaY>2);

                do
                {
                    printf("Seleccione una coordenada \033[1;34mX\033[0m del tablero: ");
                    scanf("%d", &coordenadaX);
                    while( getchar()!='\n');
                }
                while(coordenadaX<0 || coordenadaX>2);

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
                    puntos = 3;


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
                            puntos = -1;
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
        puntos = 2;
        system("cls");
        printf("\033[1;33mSE PRODUJO UN EMPATE! +2 PUNTOS --> PUNTAJE ACTUAL: %d\n\033[1;37m", jugadorActual->puntaje);
        mostrarTablero(tablero, 3, 3, turnoInicial);
        printf("\nPresione cualquier tecla para continuar...\n");
        getchar(); // Esperar una tecla para continuar
    }

    return puntos;
}

int comprobarVictoria(t_cola *cCoordenadas, int tablero[][3], int idJugador)
{

    int victoria = 0;
    int i = 0;
    int x1, y1, x2, y2, x3, y3; //Representan las posiciones de la matriz
    unsigned tamCoords = sizeof(t_coords);

    t_coords *coords = malloc(tamCoords);

    while(i<9 && !victoria)  //9 es la maxima cantidad de lineas posibles.
    {
        quitarDeCola(cCoordenadas, coords, tamCoords); //Recuperamos las coordenadas
        agregarCola(cCoordenadas, coords, tamCoords);  //Las volvemos a agregar para no perderlas

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
    unsigned tamCoords = sizeof(t_coords);

    t_coords *coords = (t_coords*)malloc(tamCoords);

    if(!coords)
    {
        return 0;
    }

    while(!jugadaVictoria && i<9)  //Mientras no haya una jugada de victoria y no se hayan recorrido todas las lineas
    {
        //Coordenadas de una linea, ej: {0,0}   {1,0}   {2,0} -> columna1
        //{y1,x1} {y2,x2} {y3,x3}
        quitarDeCola(cCoordenadas, coords, tamCoords); //Recuperamos las coordenadas de la cCoordenadas
        agregarCola(cCoordenadas, coords, tamCoords);  //Las volvemos a agregar al final para no perderlas

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

    unsigned tamCoords = sizeof(t_coords);

    FILE *pf;

    pf = fopen("Bibliotecas/coordenadas.dat", "rb");

    if(!pf)
    {
        return 0;
    }

    t_coords *coord = malloc(tamCoords);

    fread(coord, tamCoords, 1, pf);

    while(!feof(pf))
    {
        agregarCola(cCoordenadas, coord, tamCoords);
        fread(coord, tamCoords, 1, pf);
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
        if(i<fil-1)
        {
            printf("             ------+-----+------\n"); // Línea entre filas
        }
        else
        {
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
