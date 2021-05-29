/*
 ============================================================================
 Name        : pruebita-includes.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "pruebita-leer-archivos.h"

//int principal(void);

/*int principal(void) {
	puts("!!!Hello World!!!");


	char* pathArchivoTareas = "/home/utnso/Desktop/TP-SO/tp-2021-1c-GrupoChicasSistOp2021/tareasPatota.txt";

	t_list* listaTareas;
	listaTareas = list_create();

	listaTareas = leerArchivoDeTareas(pathArchivoTareas);


	return 0;
}*/


char* leer_nombreTarea(FILE* archivo){

	char* linea = string_new();

	char* a = malloc(2);
	a[1] = '\0';

	if (fread(a,1,1,archivo) != 1){
		return "FIN";
	}

	while (*a!= ' '){
		string_append(&linea, a);
		fread(a,1,1,archivo);
	}

	free(a);

	return linea;
}


char* leer_numeros(FILE* archivo){

	char* linea = string_new();
	char* a = malloc(2);
	a[0] = '0'; // si no lee nada, tiene por default 0
	a[1] = '\0';

	fread(a,1,1,archivo);
	while (*a!= ';'){
		if(strcmp(a,"\n") == 0){
			break;
		}
		string_append(&linea, a);
		fread(a,1,1,archivo);
	}

	free(a);

	return linea;
}

t_list* leerArchivoDeTareas(char* path){

		FILE* fArchivoTareas = fopen(path,"r");

		Tarea* tarea = malloc(sizeof(Tarea) + sizeof(char*));

		t_list* listaTareas;
		listaTareas = list_create();

		//char* primeraLinea = malloc(sizeof(Tarea) + sizeof(char*) + 1); //hay tres ; y 1 del /0

		//fread(primeraLinea, sizeof(Tarea) + sizeof(char*) + 1, 1, fArchivoTareas);
			//	printf("%s", primeraLinea);

		//printf("%s", tarea->nombreTarea);

		//long int aDondeEstoy = ftell(fArchivoTareas);

		//fseek(fArchivoTareas, aDondeEstoy, SEEK_SET);

		char* linea = leer_nombreTarea(fArchivoTareas);

		while(strcmp(linea, "FIN") != 0){
			strcpy(&tarea->nombreTarea, &linea);

			tarea->parametros = atoi(leer_numeros(fArchivoTareas));
			tarea->posX = atoi(leer_numeros(fArchivoTareas));
			tarea->posY = atoi(leer_numeros(fArchivoTareas));
			tarea->tiempo = atoi(leer_numeros(fArchivoTareas));

			/*printf("%s \n",tarea->nombreTarea);
			printf("%d \n",tarea->parametros);
			printf("%d \n",tarea->posX);
			printf("%d \n",tarea->posY);
			printf("%d \n",tarea->tiempo);*/
			list_add(listaTareas, tarea);
			tarea = malloc(sizeof(Tarea) + sizeof(char*));
			linea = leer_nombreTarea(fArchivoTareas);
		}

		fclose(fArchivoTareas);

		printf("el size de la lista es %d \n",list_size(listaTareas));

		void iteradorDeTareas(Tarea* tarea)
		{
			printf("%s \n",tarea->nombreTarea);
			printf("%d \n",tarea->parametros);
			printf("%d \n",tarea->posX);
			printf("%d \n",tarea->posY);
			printf("%d \n",tarea->tiempo);
		}


		list_iterate(listaTareas, iteradorDeTareas);


		/*char* linea = leer_linea(fArchivoTareas);
		char* value = get_value_from_linea(linea);
		printf("%s", value);

		for (int i=0 ; i<atoi(value); i++){
			char* x = get_x_from_linea(linea);
			char* y = get_y_from_linea(linea);
			uint32_t xx =  atoi(x);
			uint32_t yy = atoi(y);
			list_add(lista_de_todo,&xx);
			list_add(lista_de_todo,&yy);

		}*/

		/*fread(&reg,sizeof(Tarea) + sizeof(char*), 1, fArchivoTareas); // el +1 se lo saco porque no tiene /0
		printf("%s",reg->nombreTarea);
		printf("%f",reg->parametros);
		printf("%u",reg->posX);
		printf("%u",reg->posY);
		printf("%f",reg->tiempo);*/

				//char** arrayConTarea = string_n_split(primeraLinea, 2, "|"); //["1", "1"]

				/*fscanf(csvFile, "%d,%f,%d,%c",
				                &(line_pointer + i)->value1,
				                &(line_pointer + i)->value3,
				                &(line_pointer + i)->value2,
				                &(line_pointer + i)->char1)*/


				/*printf("%s",reg->nombreTarea);
				printf("%f",reg->parametros);
				printf("%u",reg->posX);
				printf("%u",reg->posY);
				printf("%f",reg->tiempo);

		while(!feof (fArchivoTareas))
		{
			printf("%s",reg->nombreTarea);
			printf("%f",reg->parametros);
			printf("%u",reg->posX);
			printf("%u",reg->posY);
			printf("%f",reg->tiempo);
			//añadir el reg leido en la lsita
			fread(&tarea,sizeof(Tarea), 1, fArchivoTareas);
		}*/
		return listaTareas;
}

