/***************************************************************
* Fichero: PEC2.c
* Autor: Pablo J. Delgado Flores
* Fecha: 07/10/2019
* Descripcion: Este fichero contiene la solución al ejercicio
* planteado en la PEC2 de Fundamentos de Programación
***************************************************************/
#include <stdio.h>

/*Definimos las constantes que usaremos en el programa*/
#define NUM_FLOORS 5
#define NUM_ROOMS_FLOOR 20

/*Definimos el tipo enumerado para los booleanos*/
typedef enum {FALSE,TRUE} boolean;

/*Comenzamos la definicion del programa principal*/
int main(int argc, char **argv)
{
	/*Definicion de variables*/
	boolean hasPool;
	boolean hasGym;
	boolean closeToSubway;
	float distanceFromCityCenter;
	float priceDouble;
	int keyNumber;
	char code;
	float discount;
	int numGuests;
	
	/*Declaramos las variables necesarias para b1,b2,b3 y b4*/
	boolean b1;
	int b2;
	boolean b3;
	float b4;
	
	/*Recogemos los datos a almacenar en las variables*/
	printf("El hotel tiene piscina: ");
	scanf("%u",&hasPool);
	printf("El hotel tiene gimnasio: ");
	scanf("%u",&hasGym);
	printf("El hotel esta cerca de una estacion de metro: ");
	scanf("%u",&closeToSubway);
	printf("Distancia del hotel al centro de la ciudad: ");
	scanf("%f",&distanceFromCityCenter);
	printf("Precio de la habitacion doble: ");
	scanf("%f",&priceDouble);
	printf("Numero de la llave: ");
	scanf("%d",&keyNumber);
	getchar();
	printf("Codigo: ");
	scanf("%c",&code);
	printf("Descuento: ");
	scanf("%f",&discount);
	printf("Numero de huespedes: ");
	scanf("%d",&numGuests);
	
	/*Resolucion de los ejercicios*/
	
	/*b1*/
	b1=(code >= 'A' && code <= 'Z') || (code >= 'a' && code <= 'z');
	/*b2*/
	b2=((((keyNumber - 1) / NUM_ROOMS_FLOOR) * 100) + ((keyNumber - 1) % NUM_ROOMS_FLOOR) + 1);
	/*b3*/
	b3=(((hasPool) || (hasGym)) && ((distanceFromCityCenter < 5) || (closeToSubway)) && (priceDouble <= 100));
	/*b4*/
	b4=(((numGuests / 2) + (numGuests % 2)) *((100 - discount) / 100) * priceDouble);
	
	/*Pintar el resultado de los ejercicios*/
	printf("\n\n");
	printf("El caracter introducido es una letra (0 es falso y 1 es verdadero): %u\n",b1);
	printf("Numero de habitacion: %03d\n", b2);
	printf("Es un hotel con buenas caracteristicas (0 es falso y 1 es verdadero): %u\n",b3);
	printf("Precio final con descuento: %.2f\n",b4);
	
	return 0;
}