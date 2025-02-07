#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../PrimitivasCola/PrimitivasCola.h"

int cargarCoordenadas(t_cola *cola);
int buscarJugadaIA(t_cola *cola, int tablero[][3]);
void mostrarTablero(int tablero[][3], int fil, int col, int turnoInicial);
void realizarJugadaIA(int *vCoords, unsigned tamVec, int tablero[][3]);
void fichaAlAzar(int tablero[][3]);

int comprobarVictoria(t_cola *cola, int tablero[][3], int idJugador);
char devolverCaracter(int id, int turnoInicial);

typedef struct{
    int coord1[2];
    int coord2[2];
    int coord3[2];
}t_coords;

/*
Valores del tablero para la lógica:
- 0 -> vacio/disponible
- 1 -> ocupado por el usuario
- 2 -> ocupado por la IA
*/

int iniciarJuego(void)
{
    t_cola cola;

    crearCola(&cola);

    cargarCoordenadas(&cola);

    srand(time(NULL));

    int tablero[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    int coordenadaX;
    int coordenadaY;
    int nJugada = 0;
    int victoria = 0;
    int turno = rand() % 2; // 0 -> Empieza el usuario || 1 -> Empieza la IA
    int turnoInicial = turno;

    while(nJugada < 9 && !victoria){ //El máximo de movimientos es 9
        if(turno == 0){
            printf("[Ahora le toca a usted]\n");
            mostrarTablero(tablero, 3, 3, turnoInicial);
            do{
                printf("Seleccione una coordenada X del tablero: ");
                scanf("%d", &coordenadaX);
                getchar();
                printf("Seleccione una coordenada Y del tablero: ");
                scanf("%d", &coordenadaY);
                getchar();
                printf("\n");
            }while(tablero[coordenadaX][coordenadaY]!=0); //Si el casillero está ocupado le pedimos que ingrese otra coordenada


            tablero[coordenadaX][coordenadaY] = 1;

            if(nJugada>=4+turnoInicial){ //Apartir de 4ta o 5ta jugada (depende de quien empieza) el usuario puede comprobar si gano
                if(comprobarVictoria(&cola, tablero, 1)){ //Se pasa el numero que se quiere comprobar si completa una linea en el tablero
                    victoria = 1;
                    printf("\n!Gana el usuario!\n");
                }
            }
            turno = 1;
        }else{
            printf("[La IA ha puesto una ficha]\n");
            if(!victoria && nJugada < 9){ //Si no gano el usuario con el movimiento anterior y la jugada no fue la ultima (nJugada<4)
                if(nJugada < 3 + turnoInicial){ //Si el turno inicial es del usuario (turno=0) entonces antes de 3 + 0 = 3 no hay posibilidad de bloqueo o de victoria.
                                                //Si el turno inicial es de la IA (turno=1) entonces antes de 3 + 1 = 4 no hay posibiidad de bloqueo o de victoria.
                    fichaAlAzar(tablero);
                }else{
                    if(!buscarJugadaIA(&cola, tablero)){
                        fichaAlAzar(tablero);
                    }else{
                        if(comprobarVictoria(&cola, tablero, 2)){
                            victoria = 1;
                            printf("\n!Gana la IA!\n");

                        }
                    }
                }
            }
            turno = 0;
        }

        nJugada++;
    }

    if(!victoria){
        printf("\nSE PRODUJO UN EMPATE!\n");
    }

    mostrarTablero(tablero, 3, 3, turnoInicial);

    return 0;
}

int comprobarVictoria(t_cola *cola, int tablero[][3], int idJugador){

    int victoria = 0;
    int i = 0;
    int x1, y1, x2, y2, x3, y3;

    t_coords *coords = malloc(sizeof(t_coords));

    while(i<9 && !victoria){ //9 es la maxima cantidad de lineas posibles.
        quitarDeCola(cola, coords, sizeof(t_coords)); //Recuperamos las coordenadas
        agregarCola(cola, coords, sizeof(t_coords));  //Las volvemos a agregar para no perderlas

        x1 = (coords->coord1)[0];
        y1 = (coords->coord1)[1];
        x2 = (coords->coord2)[0];
        y2 = (coords->coord2)[1];
        x3 = (coords->coord3)[0];
        y3 = (coords->coord3)[1];

        if(tablero[x1][y1] == idJugador && tablero[x2][y2] == idJugador && tablero[x3][y3] == idJugador){ //Si todas las coordenadas de la línea tienen
                                                                                                          //el numero del jugador => ganó
            victoria = 1;
        }

        i++;
    }

    free(coords);

    return victoria;
}

int buscarJugadaIA(t_cola *cola, int tablero[][3]){

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

    if(!coords){
        return 0;
    }

    while(!jugadaVictoria && i<9){ //Mientras no haya una jugada de victoria y no se hayan recorrido todas las lineas
        //Coordenadas de una linea, ej: {0,0}   {1,0}   {2,0} -> columna1
                                     //{x1,y1} {x2,y2} {x3,y3}
        quitarDeCola(cola, coords, sizeof(t_coords)); //Recuperamos las coordenadas de la cola
        agregarCola(cola, coords, sizeof(t_coords));  //Las volvemos a agregar al final para no perderlas

        vCoords[0] = (coords->coord1)[0];
        vCoords[1] = (coords->coord1)[1];
        vCoords[2] = (coords->coord2)[0];
        vCoords[3] = (coords->coord2)[1];
        vCoords[4] = (coords->coord3)[0];
        vCoords[5] = (coords->coord3)[1];

        for(j=0;j<tamVec;j+=2){
            if(tablero[vCoords[j]][vCoords[j+1]]==1){
                contadorUser++;
            }else if(tablero[vCoords[j]][vCoords[j+1]]==2){
                contadorIA++;
            }
        }

        if(contadorIA == 2 && contadorUser == 0){ //Si la IA tiene 2 casilleros ocupados hacemos que ocupe el que queda para ganar
            realizarJugadaIA(vCoords, tamVec, tablero);
            jugadaVictoria = 1;
        }else if(contadorIA == 0 && contadorUser == 2){ //Si es al revés guardamos las coordenadas de bloqueo para seguir buscando una linea de victoria
            memcpy(vCoordsBloqueo, vCoords, sizeof(vCoords));
            jugadaBloqueo = 1;
        }

        contadorIA = 0;
        contadorUser = 0;

        i++;
    }

    if(jugadaBloqueo && !jugadaVictoria){
        realizarJugadaIA(vCoordsBloqueo, tamVec, tablero);
    }

    free(coords);

    return (jugadaBloqueo || jugadaVictoria);
}

void realizarJugadaIA(int *vCoords, unsigned tamVec, int tablero[][3]){
    int i = 0;

    while(i<tamVec && tablero[*(vCoords+i)][*(vCoords+i+1)] != 0){ //Buscamos el lugar disponible dentro de esa linea
        i+=2;
    }

    tablero[*(vCoords+i)][*(vCoords+i+1)] = 2;
}

int cargarCoordenadas(t_cola *cola){

    FILE *pf;

    pf = fopen("librerias/AlgoritmoJuego/coordenadas.dat", "rb");

    if(!pf){
        return 0;
    }

    t_coords *coord = malloc(sizeof(t_coords));

    fread(coord, sizeof(t_coords), 1, pf);

    while(!feof(pf)){
        agregarCola(cola, coord, sizeof(t_coords));
        fread(coord, sizeof(t_coords), 1, pf);
    }

    fclose(pf);
    free(coord);

    return 1;
}


void fichaAlAzar(int tablero[][3]){
    int xRand = rand() % 3;
    int yRand = rand() % 3;

    while(tablero[xRand][yRand]!=0){
        xRand = rand() % 3;
        yRand = rand() % 3;
    }

    tablero[xRand][yRand] = 2;
}

void mostrarTablero(int tablero[][3], int fil, int col, int turnoInicial){
    int i;
    int j;

    printf("\n");

    for(i=0;i<fil;i++){
        printf("|");
        for(j=0;j<col;j++){
            printf("  %c  ", devolverCaracter(tablero[i][j], turnoInicial) );
            if(j<3){
                printf("|");
            }
        }
        printf("\n");

        if(i<2){
            printf("------+-----+------\n");
        }
    }

    printf("\n");
}

char devolverCaracter(int id, int turnoInicial){
    if((id == 1 && turnoInicial == 0) || (id == 2 && turnoInicial == 1)){
        return 'X';
    }else if((id == 1 && turnoInicial == 1) || (id == 2 && turnoInicial == 0)){
        return 'O';
    }else{
        return ' ';
    }
}
