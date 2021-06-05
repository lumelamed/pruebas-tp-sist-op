/*
 * pruebita-leer-archivos.h
 *
 *  Created on: May 28, 2021
 *      Author: utnso
 */

#ifndef PRUEBITA_LEER_ARCHIVOS_H_
#define PRUEBITA_LEER_ARCHIVOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/string.h>
#include <commons/collections/list.h>

typedef struct
{
	char* 		nombreTarea;
	int  		parametros;
	int 		posX;
	int 		posY;
	int  		tiempo;
} Tarea;

//GENERAR_OXIGENO 12;2;3;5

char* leer_nombreTarea(FILE*);
char* leer_numeros(FILE*);
t_list* leerArchivoDeTareasReturnTareasList(char* );
char* leerArchivoDeTareas(char* );
int archivo_obtenerTamanio(char*);
char*archivo_leer(char*);

#endif /* PRUEBITA_LEER_ARCHIVOS_H_ */
