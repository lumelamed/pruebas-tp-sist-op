/*
 * pruebita-hilos.h
 *
 *  Created on: May 28, 2021
 *      Author: utnso
 */

#ifndef PRUEBITA_HILOS_H_
#define PRUEBITA_HILOS_H_

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include <stdbool.h>
#include<commons/collections/list.h>
#include<pthread.h>
#include<semaphore.h>
#include<commons/string.h>
#include<commons/temporal.h>
#include<unistd.h>
#include<netdb.h>

#include "pruebita-leer-archivos.h"

typedef  struct
{
	uint32_t 	TID;
	char     	estado;
	uint32_t 	posicionX;
	uint32_t 	posicionY;
	uint32_t 	proximaInstruccion;
	uint32_t* 	punteroPCB; // PID de la patota
	int		 	socket_RAM;
	int		 	socket_Mongo;
} Tripulante; //podria agregarse semaforos como parte del struct!

typedef struct
{
	uint32_t 	PID;
	uint32_t 	tareas; //Dirección lógica del inicio de las Tareas
	uint32_t 	cantTripulantes;
	t_list*		tripulantes;
} Patota;


t_list* listaDePatotas;
uint32_t idsPatota;
uint32_t idsTripulante;

char* fecha;
const char* tareasDeIO = "GENERAR_OXIGENO CONSUMIR_OXIGENO GENERAR_COMIDA CONSUMIR_COMIDA GENERAR_BASURA DESCARTAR_BASURA";

void leer_consola(void);
void atender_consola(char*);
void crearHiloTripulante(Patota* , uint32_t , char* );
void crearTripulante(uint32_t , char , uint32_t , uint32_t , uint32_t , uint32_t* , Patota* );
Patota* crearPatota(uint32_t , uint32_t ,int );
void eliminarUnTrip(t_list* , Tripulante* );
Tripulante* buscarTripulantePorId(uint32_t );
Tarea pedirTarea (Tripulante*, char*);
void hacerMovimientoDePosiciones(Tripulante*, Tarea);

#endif /* PRUEBITA_HILOS_H_ */
