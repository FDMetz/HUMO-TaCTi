#include "Archivos.h"

int leerConfig(const char *nombreArchivo, Config *config)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo)
    {
        printf("Error al abrir el archivo de configuración.\n");
        return 0;
    }

    // Leer la URL y codigo
    if (fscanf(archivo, "%s | %s", config->url, config->codigoGrupo) != 2)
    {
        printf("Error al leer la URL y el código del grupo.\n");
        fclose(archivo);
        return 0;
    }

    // Leer la cantidad de partidas
    if (fscanf(archivo, "%d", &config->cantidadPartidas) != 1)
    {
        printf("Error al leer la cantidad de partidas.\n");
        fclose(archivo);
        return 0;
    }

    fclose(archivo);
    return 1;
}
