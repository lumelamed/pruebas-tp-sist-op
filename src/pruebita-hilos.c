/*
 * pruebita-hilos.c
 *
 *  Created on: May 28, 2021
 *      Author: utnso
 */

#include "pruebita-hilos.h"

int main(void)
{
	idsPatota = 1;
	idsTripulante = 1;
	listaDePatotas = list_create();

	leer_consola();

	return EXIT_SUCCESS;
}

void leer_consola(void)
{
	char* leido;

	printf("Para INICIAR_PATOTA ingrese 0 \n");
	printf("Para LISTAR_TRIPULANTES ingrese 1 \n");
	printf("Para EXPULSAR_TRIPULANTE ingrese 2 \n");
	printf("Para ver la info de un trip en particular ingrese 3 \n");

	printf("Consola escuchando");

	leido = readline(">");

	while(strcmp(leido, "") != 0)
	{
		printf("consola leyo: %s \n", leido);
		atender_consola(leido);
		free(leido);
		leido = readline(">");
	}

	//leido = "INICIAR_PATOTA 5 /home/utnso/tareas/tareasPatota5.txt 1|1 3|4";
}

void atender_consola(char* leido)
{
	int numero = atoi(leido);

	switch(numero){
		case 0:;
			//DECLARO VARIABLES
			uint32_t cantTripulantes;
			char* rutaTareas;
			char* posicionEnMemoria;
			Patota* patota;
			t_list* listaDeTareas;

			//PIDO PARAMETROS
			printf("Ingrese la cantidad de tripulantes que quieras tener en la patota");
			cantTripulantes =(uint32_t)atoi(readline(">"));

			printf("Ingrese la ruta del archivo de tareas");
			rutaTareas = readline(">");

			listaDeTareas = list_create();
			listaDeTareas = leerArchivoDeTareas(rutaTareas);

			patota = crearPatota(idsPatota, (uint32_t)0, cantTripulantes); //el 0 es la posicion de memoria de las tareas
			list_add(listaDePatotas, patota);
			idsPatota++;

			//int socketPatota = crear_conexion(IPRAM, puertoRAM);
			//paquete(socketPatota, NULL, INICIAR_PATOTA); //ver si va NULL o necesita que le mandemos algo
			// se cierra conexion? o agregamos la conexion al struct patota?

			for(int i = 0; i < cantTripulantes; i++)
			{
				printf("Ingrese la posicion de memoria del tripulante %d con el formato X|Y, o -1 si no desea especificarla", i + 1);
				posicionEnMemoria = readline(">");

				if(strcmp(posicionEnMemoria, "-1") == 0){
					strcpy(posicionEnMemoria, "0|0");
				}


				crearHiloTripulante(patota, idsTripulante, posicionEnMemoria);
				idsTripulante ++;
			}

			// crear conexion con i-Mongo para escuchar a ver si hay sabotajes

			break;

		case 1:;
			void iteradorDeTripulantes(Tripulante* tripulante)
			{
				printf("------------------------------------------------------- \n");
				printf("Tripulante: %d \t Patota: %d \t Status: %c \n", tripulante->TID, *(tripulante->punteroPCB), tripulante->estado);
				printf("------------------------------------------------------- \n");
			}

			void iteradorDePatotas(Patota* patota)
			{
				list_iterate(patota->tripulantes, iteradorDeTripulantes);
			}

			printf("Estado de la Nave \n ");


			list_iterate(listaDePatotas, iteradorDePatotas);


			break;

		case 2:;

		//expulsar

			break;
		case 3:;
			uint32_t idTrip;
			Tripulante* tripulante = malloc(sizeof(Tripulante));

			printf("Ingrese un id de trip");
			idTrip =(uint32_t)atoi(readline(">"));
			tripulante = buscarTripulantePorId(idTrip);

			printf("TRIPULANTE ENCONTRADO: \n");
			printf("TID: %d \n", tripulante->TID);
			printf("ESTADO: %c \n", tripulante->estado);
			printf("POS X: %d \n", tripulante->posicionX);
			printf("POS Y: %d \n", tripulante->posicionY);
			printf("PROXIMA INST: %d \n", tripulante->proximaInstruccion);
			printf("PUNTERO PCB: %d \n", *(tripulante->punteroPCB));
			printf("SOCKET RAM: %d \n", tripulante->socket_RAM);
			printf("SOCKET MONGO: %d \n", tripulante->socket_Mongo);

			break;
		default:;
		printf("esta prueba solo lee los numeros 0, 1, 2, 3");
		break;
	}
}

void crearHiloTripulante(Patota* patota, uint32_t idTrip, char* direccionesDeTripulantes)
{
	char** arrayConLas2Direcc = string_n_split(direccionesDeTripulantes, 2, "|"); //["1", "1"]

	uint32_t posicionX = (uint32_t)atoi(arrayConLas2Direcc[0]);
	uint32_t posicionY = (uint32_t)atoi(arrayConLas2Direcc[1]);

	pthread_t nuevoTrip;

	void crearTripulanteDeUnParametro(Patota* patota)
	{
		printf("estoy por crear el trip, le pase la patota con PID %d \n", patota->PID);
		crearTripulante(idTrip, 'N', posicionX, posicionY, 0, &patota->PID, patota); //0--> (la ram nos la tiene que devolver)
	}

	pthread_create(&nuevoTrip, NULL, (void*)crearTripulanteDeUnParametro, patota);

	pthread_join(nuevoTrip, NULL );
	//pthread_detach(nuevoTrip);
}

void crearTripulante(uint32_t TID, char estado, uint32_t x, uint32_t y, uint32_t instruccion, uint32_t* PCB, Patota* patota)
{
	Tripulante* tripulante = malloc(sizeof(Tripulante));
	tripulante->punteroPCB = malloc(sizeof(uint32_t));

	tripulante->TID =TID;
	tripulante->estado = estado;
	tripulante->posicionX = x;
	tripulante->posicionY = y;
	tripulante->proximaInstruccion = instruccion;
	tripulante->punteroPCB = PCB;
	tripulante->socket_RAM = 0; //crear_conexion(IPRAM, puertoRAM);
	tripulante->socket_Mongo = 0; //crear_conexion(IPiMongo, puertoImongo);

	list_add(patota->tripulantes, tripulante);

	printf("TRIPULANTE CREADO: \n");
	printf("TID: %d \n", tripulante->TID);
	printf("ESTADO: %c \n", tripulante->estado);
	printf("POS X: %d \n", tripulante->posicionX);
	printf("POS Y: %d \n", tripulante->posicionY);
	printf("PROXIMA INST: %d \n", tripulante->proximaInstruccion);
	printf("PUNTERO PCB: %d \n", *(tripulante->punteroPCB));
	printf("SOCKET RAM: %d \n", tripulante->socket_RAM);
	printf("SOCKET MONGO: %d \n", tripulante->socket_Mongo);


	printf("aca se supone que lo agrega al estado new \n");

	//agregarAEstado(estadoNew, tripulante);
	//paquete(tripulante->socket_RAM, &tripulante , TRIPULANTE_MAPA);

}

Patota* crearPatota(uint32_t PID, uint32_t tareas,int cantTrip)
{
	Patota* patota= malloc(sizeof(Patota));

	patota->PID = PID;
	patota->tareas = tareas;
	patota->cantTripulantes = cantTrip;
	patota->tripulantes = list_create();

	printf("PATOTA CREADA: \n");
	printf("PID: %d \n", patota->PID);

	return patota;
}

void eliminarUnTrip(t_list* listaDeTrips, Tripulante* tripulante) {

	bool esElTripulante(void* unTrip) {
		Tripulante* otroTrip = unTrip;
		return otroTrip->TID == tripulante->TID;
	}

	list_remove_by_condition(listaDeTrips, esElTripulante);
}

Tripulante* buscarTripulantePorId(uint32_t id){

	Tripulante* tripulante = malloc(sizeof(Tripulante));

	bool idEsIgual(Tripulante* trip){
		return trip->TID == id;
	}

	void iteradorDePatotas(Patota* patota)
	{
		Tripulante* trip = list_find(patota->tripulantes, idEsIgual);
		if(trip != NULL){
			tripulante = trip;
			return;
		}
	}

	list_iterate(listaDePatotas, iteradorDePatotas);

	return tripulante;
}
