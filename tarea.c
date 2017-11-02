#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


struct data{
int lineas;
int id;
int totalprimos;
};



/////////////////////////////////////////////////////
void calcularlineasaleer(int cantidad_procesos , int *procesos , int lineas){


/*Calculo de lineas a leer para cada proceso*/
	for(int i=0;i<cantidad_procesos;i++){


			if(i==(cantidad_procesos-1) ){
			procesos[i]=(lineas/(i+1)) + (lineas%(i+1));
			}
			else{
			procesos[i]=lineas/(i+1);
			}


	}//End for


/*Imprime la cant de lineas que le toca leer a cada proceso*/
	for(int j=0 ;j<cantidad_procesos;j++){

	printf("%i \n",procesos[j]);

	}



}
/////////////////////////////////////////////////////






////////////////////////////////////////////////////
/*Calcula si x es primo
*int x = numero a calcular si es primo*/
int primo(int x){

	/*EL cero y el 1 no son primos*/
    if(x<2){return 0;}

    for(int i=(x-1); i>1 ; i-- ){

		/*Numero no primo*/
		if(  (x%i)  == 0  ){
		return 0;
		}

	}

/*Numero primo*/
return 1;

}
////////////////////////////////////////////////





///////////////////////////////////////////////
/*Calcula la longitud del archivo recibido por parametro
*char arch = nombre archivo a abrir
*/
int calcularlongarchivo(){


FILE *archivoentrada;
int contador=0;   
char caracteres[100];



/*Apertura de archivo*/
archivoentrada = fopen ( "prueba.txt", "r" ); 

 

	if (archivoentrada==NULL) {
		printf("Error"); 
		
		}

		else{

			while (feof(archivoentrada) == 0){
				fgets(caracteres,100,archivoentrada);
 				contador++;
				
 	    	}


		}

     


/*Clausura de archivo*/
fclose ( archivoentrada );

return (contador);

}
//////////////////////////////////////////////





/////////////////////////////////////////////
/*Lee de un archivo y escribe en otro la cant de lineas asignadas 
*Escribe el numero y al lado si es primo o no
lineas_lectura=cant de lineas a leer
*ident=numero de proceso*/
void lecturaarchivo(struct data *datos){

int lineas_lectura=datos->lineas;
int ident=datos->id;
int totalprimos= datos->totalprimos;

/**/
FILE *archivoentrada;
FILE *archivosalida;
char itxt[10]={0};
char caracteres[100];
int contador_lineas=0;


/*Convierte el entero "ident" a string y lo almacena en el char "itxt"*/
sprintf(itxt, "%i", ident);

/*Le concatena al string "itxt" el string ".txt"*/
strcat(itxt,".txt");


/*Apertura de archivo en modo lectura*/
archivoentrada = fopen ( "prueba.txt", "r" );   

/*Apertura de archivo en modo escritura*/
archivosalida = fopen ( itxt, "w" );



	if (archivoentrada==NULL) {
		printf("Error"); 
		
		}

		else{



			while (feof(archivoentrada) == 0){
 			    contador_lineas++;

				fgets(caracteres,100,archivoentrada);

				/*Convierte el string "caracteres" en int y lo almacena en "numero"*/
                int numero = atoi(caracteres);

				/*Calcula si el numero es primo y almacena el resultado en el entero "primou"*/
				int primou=primo(numero);
				totalprimos++;

				//printf("%i->%i \n",numero,primou);
				
				char buffer[100]="";
			
				/*Almaecena a los enteros "numero" y "primo" en el string "buffer" y luego los almacena en el "archivosalida"*/
				fprintf (archivosalida, "%s %d %d \n", buffer, numero,primou);

				
				/*Condicion de parada , si el "contador_lineas" se iguala a las lineas a leer y escribir "lineas_lectura" me salgo del ciclo while*/
              	if(contador_lineas==lineas_lectura){
				break;
				}


 	    	}
			 fprintf(archivosalida,"Total de Primos: %d", totalprimos);

		}

     
/*Clausura de los archivos*/
fclose ( archivosalida );
fclose ( archivoentrada );


}
//////////////////////////////////////////





/*Problema1 con procesos
cantidad_procesos = cantidad de procesos a crear y ejecutar*/
/////////////////////////////////////////
void inicio_procesos(int cantidad_procesos){


int procesos[cantidad_procesos];
int lineas = calcularlongarchivo();

/*Calcula las lineas a leer para cada proceso (se almacenan en un array para cada proceso)*/
calcularlineasaleer(cantidad_procesos,procesos,lineas);


int ident=0;


for(int k=0 ;k<cantidad_procesos;k++){

		if( fork() == 0){
			ident=k;
			break;
		}
}

struct data datos={procesos[ident],ident};
lecturaarchivo(&datos);
}
/////////////////////////////////////////





/////////////////////////////////////////
void inicio_hilos(int n_hilos){
pthread_t hilos[n_hilos];

int totalprimos;
int procesos[n_hilos];
int lineas = calcularlongarchivo();

/*Calcula las lineas a leer para cada proceso (se almacenan en un array para cada proceso)*/
calcularlineasaleer(n_hilos,procesos,lineas);



		for(int i=0;i<(n_hilos);i++){

			struct data datos={procesos[i],i,totalprimos};

			pthread_create(&hilos[i], NULL,(void*)lecturaarchivo,(void*)&datos);

			pthread_join(hilos[i],NULL);
		}
		//printf()


}
/////////////////////////////////////////




/////////////////////////////////////////
int main(){

//scanf(" %c", &res);

/*Crea y ejecuta los procesos*/
//inicio_procesos(5);

/*Crea y ejecuta los hilos*/
inicio_hilos(5);


return 0;
}
////////////////////////////////////////









