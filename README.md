# TaCTi
TaCti es un minijuego de Ta-Te-Ti desarrollado en C como parte del trabajo práctico de la materia "Algoritmos y Estructuras de Datos". El juego permite a los jugadores enfrentarse a una inteligencia artificial básica, registrando los resultados en un servidor mediante una API y generando informes locales con estadísticas de las partidas.
## Grupo
Nombre de Grupo: HUMO
Codigo de Grupo: HUMOR
## Integrantes:
* Mascasin Muñoz Maximiano
* Metz Federico Daniel
* Suarez Gonzalo
## Requisitos
* Compilador compatible con C
* Conexion a internet para integracion con la API
* Archivo de configuracion 'config.txt' para los parametros del juego.
## Reglas
* El jugador con la ficha **X** tendra el primer turno.
* El orden de los jugadores se sorteara de manera aleatoria.
* Al finalizar todas las patidas de un jugador empizaran las del siguiente jugador.
* Al finalizar una partida se ganan o pierden puntos:
    * +3 si gana el jugador.
    * +2 si el jugador empata contra la maquina.
    * -1 si el jugador pierde.
* Por defecto cada jugador jugara 1 partida.
## ¿Cómo jugar?
1. Al iniciar el programa, se mostrará un menú con tres opciones:
   [A] Jugar: Permite iniciar una partida contra la IA.
   [B] Ver ranking equipo: Consulta los puntajes registrados.
   [C] Salir: Cierra el programa.
2. Al iniciar la partida, se le solicita al usuario a ingresar los nombre de los jugadores, cuyos turnos seran decididos aleatoriamente si importar el orden de ingreso. Luego al usuario se le mostrara la lista de jugadores
3. A continuacion se le presentara el siguiente tablero al jugador:

![Tablero de referencia](https://github.com/user-attachments/assets/5870e58b-be7b-4505-a4fa-27c79310816c)

4. El programa le pedira ingresar las coordenadas en 'Y' y 'X' para marcar en el tablero con su ficha designada, si el espacio ya esta ocupado se le pedira que ingrese las coordenadas nuevamente.
5. Una vez terminada sus partidas sera el turno del siguiente jugador en la lista.
6. Al terminar todas las partidas de los jugadores, el puntaje total de cada jugador sera subido a la API para registrarlo en el ranking Global y se creara un informe detallado de cada partida en la carpeta 'HUMO-TaCTi\Informes'.
## Configuranciones
* Se puede cambiar la cantidad de partidas jugadas por cada jugador y activar/desactivar la música del juego, abrir el archivo **Configuracion** ubicado en la carpeta HUMO-TaCTi y cambiar el número de partidas.  

![Archivo configuracion abierto en el bloc de notas](https://github.com/user-attachments/assets/af2a68a1-af30-47f2-bb42-8e6343672b79)
