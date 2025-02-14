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

int crearInforme(FILE **pfInforme)
{
    char buffer[50];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, sizeof(buffer), "Informes\\informe-juego_%04d-%02d-%02d-%02d-%02d.txt",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

    *pfInforme = fopen(buffer, "wt");
    if(!(*pfInforme))
    {
        printf("No se pudo crear el informe...");
        return 0;
    }

    return 1;
}

void init_string(struct string *s)
{
    s->len = 0;
    s->ptr = malloc(1);
    if (s->ptr)
    {
        s->ptr[0] = '\0';
    }
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr)
    {
        memcpy(s->ptr + s->len, ptr, size * nmemb);
        s->ptr[new_len] = '\0';
        s->len = new_len;
    }
    return size * nmemb;
}

void guardarRanking(tLista *p, const char* urlBase, const char* codigoGrupo)
{
    if (!p || !*p || !urlBase || !codigoGrupo)
    {
        printf("Lista vacia o URL invalida\n");
        return;
    }

    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl)
    {
        //URL SIN el código de grupo en la URL
        char urlPost[300];
        snprintf(urlPost, sizeof(urlPost), "%s", urlBase);

        ///printf("Enviando a URL (POST): %s\n", urlPost);

        //onstruir JSON con "nombre" y "puntos"
        cJSON *json = cJSON_CreateObject();
        cJSON_AddStringToObject(json, "CodigoGrupo", codigoGrupo);
        cJSON *jugadoresArray = cJSON_AddArrayToObject(json, "Jugadores");

        tNodo *actual = *p;
        while (actual)
        {
            tJugador *jugador = (tJugador *)actual->info;
            cJSON *jugadorJson = cJSON_CreateObject();
            cJSON_AddStringToObject(jugadorJson, "nombre", jugador->nombre);
            cJSON_AddNumberToObject(jugadorJson, "puntos", jugador->puntaje);
            cJSON_AddItemToArray(jugadoresArray, jugadorJson);
            actual = actual->sig;
        }

        char *jsonData = cJSON_PrintUnformatted(json);
        cJSON_Delete(json);  // Liberar memoria de cJSON

        //Configurar encabezados
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        //Configurar cURL para POST
        curl_easy_setopt(curl, CURLOPT_URL, urlPost);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        //Ejecutar la solicitud
        res = curl_easy_perform(curl);

        //Obtener código de respuesta HTTP
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        ///printf("Código de respuesta HTTP (POST): %ld\n", http_code);

        //Manejo de errores
        if (res != CURLE_OK)
        {
            fprintf(stderr, "Error en la solicitud POST: %s\n", curl_easy_strerror(res));
        }
        else if (http_code != 204) // La API debería responder con 204 No Content
        {
            printf("Error: La API respondió con código HTTP %ld (debería ser 204)\n", http_code);
        }
        /*else
        {
            printf("Jugadores enviados correctamente.\n");
        }*/

        ///Depuración
        ///printf("JSON enviado: %s\n", jsonData);

        //iberar memoria y cerrar conexión
        free(jsonData);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
}

void obtenerRanking(tLista *lista, const char *urlBase, const char *codigoGrupo)
{
    if (!lista || !urlBase || !codigoGrupo)
    {
        printf("Lista vacía o URL inválida\n");
        return;
    }

    CURL *curl;
    CURLcode res;
    struct string s;
    init_string(&s);

    //Construir la URL con el código de grupo
    char urlGet[300];
    snprintf(urlGet, sizeof(urlGet), "%s/%s", urlBase, codigoGrupo);

    ///printf("Obteniendo ranking desde URL: %s\n", urlGet);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, urlGet);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        ///printf("Codigo de respuesta HTTP (GET): %ld\n", http_code);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "Error en la solicitud GET: %s\n", curl_easy_strerror(res));
        }
        else if (http_code == 200)
        {
            ///printf("Respuesta JSON: %s\n", s.ptr);

            //Parsear el JSON recibido
            cJSON *jsonArray = cJSON_Parse(s.ptr);
            if (!jsonArray || !cJSON_IsArray(jsonArray))
            {
                printf("Error: La respuesta de la API no es un array JSON valido.\n");
            }
            else
            {
                int idJugador = 1;
                cJSON *jugadorJson;
                cJSON_ArrayForEach(jugadorJson, jsonArray)
                {
                    tJugador jugador;
                    cJSON *nombre = cJSON_GetObjectItem(jugadorJson, "nombreJugador");
                    cJSON *puntaje = cJSON_GetObjectItem(jugadorJson, "puntaje");

                    if (cJSON_IsString(nombre) && cJSON_IsNumber(puntaje))
                    {
                        strncpy(jugador.nombre, nombre->valuestring, TAM_NOM - 1);
                        jugador.puntaje = puntaje->valueint;
                        jugador.idJugador = idJugador++;

                        listaPonerOrd(lista, &jugador, sizeof(jugador), compararJugadores);
                    }
                }
            }
            cJSON_Delete(jsonArray);
        }
        else
        {
            printf("Error: Codigo HTTP inesperado (%ld). No se pudo obtener el ranking.\n", http_code);
        }

        free(s.ptr);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
