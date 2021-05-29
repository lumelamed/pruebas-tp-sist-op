# pruebas-tp-sist-op

se utilizan las commons, una biblioteca creada por la catedra
- commons
- readline
- pthread
- semaphore?

## pruebita-hilos
simula la consola del discordiador

## pruebita-leer-archivo-txt
lee el archivo del tp de sist op de tareas con el formato:
NOMBRE_TAREA 0;1;2;3

donde 0 es un numero que se utiliza como parametro (suele ser la "cantidad"), por ejemplo: GENERAR_OXIGENO 12... genera 12 tubos de oxigeno
1 y 2 son posiciones X e Y
3 tiempo (supongo son ciclos de CPU)

despues de leerlo guarda en una lista de tareas todas las tareas que leyo

### el archivo termina con un enter (\n), es importante


