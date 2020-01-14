/***************************************************************
* Fichero: main.c
* Autor: Pablo J. Delgado Flores
* Fecha: 18/11/2019
* Descripcion: Este fichero contiene la solucion al ejercicio
* planteado en la PEC7 de Fundamentos de Programacion
* Se adjuntan tambien los ficheros hotel.h y hotel.c
***************************************************************/

#include <stdio.h>
#include "hotel.h"

int main(int argc, char **argv)
{
	tHotel hotel1;
	tHotel hotel2;
	tHotel bestHotel;
	
	printf("INTRODUCE DATA FOR HOTEL 1 \n");
	hotelRead(&hotel1);
	printf("INTRODUCE DATA FOR HOTEL 2 \n");
	hotelRead(&hotel2);
	
	hotelCmpPoints(hotel1,hotel2,&bestHotel);
	printf("THE BEST CHOICE IS >> \n");
	hotelWrite(bestHotel);
	
	return 0;
}
