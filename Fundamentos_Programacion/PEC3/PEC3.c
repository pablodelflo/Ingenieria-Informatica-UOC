/***************************************************************
* Fichero: PEC3.c
* Autor: Pablo J. Delgado Flores
* Fecha: 14/10/2019
* Descripcion: Este fichero contiene la solucion al ejercicio
* planteado en la PEC3 de Fundamentos de Programacion
***************************************************************/
#include <stdio.h>

/*Definimos las constantes que usaremos en el programa*/
#define NAME_HOTEL1 "SUN"
#define NAME_HOTEL2 "MOON"
#define NAME_HOTEL3 "EARTH"
#define NUM_HOTELS 3
#define MAX_DISCOUNT 50
#define HOTEL1 1
#define HOTEL2 2
#define HOTEL3 3

/*Comenzamos la definicion del programa principal*/
int main(int argc, char **argv)
{
	/*Definicion de variables*/
	//boolean hasPool;
	int prices[NUM_HOTELS];
	int discount[NUM_HOTELS];
	int guests;
	float priceWithDiscount[3];
	float totalPricePerDay[3];
	/*Comenzamos a pedir los precios y descuentos*/
	printf("Introduce el precio por habitacion doble del primer hotel (%s): ",NAME_HOTEL1);
	scanf("%d",&prices[0]);
	printf("Introduce el precio por habitacion doble del segundo hotel (%s): ",NAME_HOTEL2);
	scanf("%d",&prices[1]);
	printf("Introduce el precio por habitacion doble del tercer hotel (%s): ",NAME_HOTEL3);
	scanf("%d",&prices[2]);
	printf("Introduce el descuento del primer hotel: ");
	scanf("%d",&discount[0]);
	printf("Introduce el descuento del segundo hotel: ");
	scanf("%d",&discount[1]);
	printf("Introduce el descuento del tercer hotel: ");
	scanf("%d",&discount[2]);
	if ((discount[0]>=0 && discount[0]<=MAX_DISCOUNT) && (discount[1]>=0 && discount[1]<=MAX_DISCOUNT) && (discount[2]>=0 && discount[2]<=MAX_DISCOUNT)){
		printf("Introduce el numero de personas que iran al hotel: ");
		scanf("%d",&guests);
		if(guests>10){
			priceWithDiscount[0]=(((float)100 - discount[0]) / 100) * prices[0];
			priceWithDiscount[1]=(((float)100 - discount[1]) / 100) * prices[1];
			priceWithDiscount[2]=(((float)100 - discount[2]) / 100) * prices[2];
			totalPricePerDay[0]=((guests/2)+(guests%2))*priceWithDiscount[0];
			totalPricePerDay[1]=((guests/2)+(guests%2))*priceWithDiscount[1];
			totalPricePerDay[2]=((guests/2)+(guests%2))*priceWithDiscount[2];
			if((totalPricePerDay[0]<totalPricePerDay[1] && totalPricePerDay[0]<totalPricePerDay[2]) || (totalPricePerDay[0]==totalPricePerDay[1]) || (totalPricePerDay[0]==totalPricePerDay[2])){
				printf("El hotel mas barato es el %d, %s con un precio de %.2f\n",HOTEL1,NAME_HOTEL1,totalPricePerDay[0]);
			} else if ((totalPricePerDay[1]<totalPricePerDay[0] && totalPricePerDay[1]<totalPricePerDay[2]) || (totalPricePerDay[1]==totalPricePerDay[2])){
				printf("El hotel mas barato es el %d, %s con un precio de %.2f\n",HOTEL2,NAME_HOTEL2,totalPricePerDay[1]);
			} else {
				printf("El hotel mas barato es el %d, %s con un precio de %.2f\n",HOTEL3,NAME_HOTEL3,totalPricePerDay[2]);
			}
		}
	} else {
		printf("\n=================================================================================================================\n");
		printf("ERROR:El descuento introducido es erroneo, debe ser una cantidad entre 0 y 50, ambos inclusive.\n");
		printf("Programa finalizado");
		printf("\n=================================================================================================================\n");
	}
	
}
