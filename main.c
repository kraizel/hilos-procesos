#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

 struct hilo_info{ //Informacion que manejara cada hilo
	int lineas[2]; //Cantidad de lineas que trabajara cada hilo
	int hilo_actual;
};

/*Calcula si x es primo
int x = numero a calcular si es primo*/
int primo(int x)
{
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


int lecturaarchivo()
{	
/**/
FILE *archivoentrada;
int cantLinea=0;
/*Apertura de archivo*/
archivoentrada = fopen ( "prueba.txt", "r" );   
char caracteres[100];
	if (archivoentrada==NULL) {
        printf("Error"); 	
		}
		else{
			while (feof(archivoentrada) == 0){
 				cantLinea++;
				fgets(caracteres,100,archivoentrada);
                int numero = atoi(caracteres);
				printf("%i->%i \n",numero,primo(numero)); 
            }
		}
/*Clausura de archivo*/
fclose ( archivoentrada );
return cantLinea;   
}



int main()
{
 //Creacion de los hilos
	pthread_t hilo1;
	pthread_t hilo2;
	pthread_t hilo3;
	pthread_t hilo4;
	
	/* printf("Introduzca la cantidad de procesos hijos a crear:");
	scanf("%d",hijos); */

	int lineas=lecturaarchivo();

	

	return 0;
}


