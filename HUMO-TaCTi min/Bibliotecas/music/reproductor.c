#include "reproductor.h"

void reproducirSonido(char *nombreSonido, unsigned bucle){

    char ruta[40] = "";

    strcat(ruta, "Bibliotecas/music/");
    strcat(ruta, nombreSonido);
    strcat(ruta, ".wav");

    PlaySound(ruta, NULL, SND_FILENAME | SND_ASYNC | bucle);
    //SND_FILENAME indica que el primer argumento es una ruta.
    //SND_ASYNC hace que no se detenga la ejecución del programa.
    //SND_LOOP hace que no se repita el sonido cuando finaliza
}

void mutearSonido(){
    PlaySound(NULL, 0, 0);
}
