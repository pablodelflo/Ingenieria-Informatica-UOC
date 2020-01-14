/***************************************************************
* Fichero: pec5.c
* Autor: Pablo J. Delgado Flores
* Fecha: 04/11/2019
* Descripcion: Este fichero contiene la solucion al ejercicio
* planteado en la PEC5 de Fundamentos de Programacion
***************************************************************/
#include <stdio.h>
#include <string.h>

/*Definimos las constantes que usaremos en el programa*/
#define MAX_CHARACTERS 15

/*Definimos el enumerado tHotelType y booleano*/
typedef enum {BUDGET,INN,RESORT,CONDO,LUXURY,COUNTRY} tHotelType;
typedef enum {FALSE,TRUE} boolean;

/*Definimos el struct tHotel*/
typedef struct {
	int id;
	char brand[MAX_CHARACTERS+1];
	char name[MAX_CHARACTERS+1];
	tHotelType hotelType;
	char city[MAX_CHARACTERS+1];
	int category;
	float priceDouble;
	float distanceFromCityCenter;
	boolean hasPool;
	boolean hasGym;
	boolean closeToSubway;
	float percentOccupation;
} tHotel;

/*Comenzamos la definicion del programa principal*/
int main(int argc, char **argv)
{
    tHotel hotel1;
    tHotel hotel2;
    tHotel hotel3;
    float maxPrice;
	char desiredCity[MAX_CHARACTERS+1];

    //Recogemos datos del HOTEL 1
    printf("==DATOS DEL HOTEL 1==\n");
    printf("ID del hotel: ");
    scanf("%d",&hotel1.id);
    printf("Cadena hotelera: ");
    scanf("%s",hotel1.brand);
    printf("Nombre del hotel: ");
    scanf("%s",hotel1.name);
    printf("Ciudad: ");
    scanf("%s",hotel1.city);
    printf("Tipo de hotel (0-Budget, 1-Inn, 2-Resort,3-Condo,4-Luxury,5-Country): ");
    scanf("%u",&hotel1.hotelType);
    printf("Numero de estrellas: ");
    scanf("%d",&hotel1.category);
    printf("Precio de habitacion doble: ");
    scanf("%f",&hotel1.priceDouble);
    printf("Distancia hasta el centro: ");
    scanf("%f",&hotel1.distanceFromCityCenter);
    printf("Piscina (0-No, 1-Si): ");
    scanf("%u",&hotel1.hasPool);
    printf("Gimnasio (0-No, 1-Si): ");
    scanf("%u",&hotel1.hasGym);
    printf("Estacion de metro cerca (0-No, 1-Si): ");
    scanf("%u",&hotel1.closeToSubway);
    printf("Porcentaje de ocupacion: ");
    scanf("%f",&hotel1.percentOccupation);

    //Recogemos datos del HOTEL 2
    printf("\n==DATOS DEL HOTEL 2==\n");
    printf("ID del hotel: ");
    scanf("%d",&hotel2.id);
    printf("Cadena hotelera: ");
    scanf("%s",hotel2.brand);
    printf("Nombre del hotel: ");
    scanf("%s",hotel2.name);
    printf("Ciudad: ");
    scanf("%s",hotel2.city);
    printf("Tipo de hotel (0-Budget, 1-Inn, 2-Resort,3-Condo,4-Luxury,5-Country): ");
    scanf("%u",&hotel2.hotelType);
    printf("Numero de estrellas: ");
    scanf("%d",&hotel2.category);
    printf("Precio de habitacion doble: ");
    scanf("%f",&hotel2.priceDouble);
    printf("Distancia hasta el centro: ");
    scanf("%f",&hotel2.distanceFromCityCenter);
    printf("Piscina (0-No, 1-Si): ");
    scanf("%u",&hotel2.hasPool);
    printf("Gimnasio (0-No, 1-Si): ");
    scanf("%u",&hotel2.hasGym);
    printf("Estacion de metro cerca (0-No, 1-Si): ");
    scanf("%u",&hotel2.closeToSubway);
    printf("Porcentaje de ocupacion: ");
    scanf("%f",&hotel2.percentOccupation);

    //Recogemos datos del HOTEL 3
    printf("\n==DATOS DEL HOTEL 3==\n");
    printf("ID del hotel: ");
    scanf("%d",&hotel3.id);
    printf("Cadena hotelera: ");
    scanf("%s",hotel3.brand);
    printf("Nombre del hotel: ");
    scanf("%s",hotel3.name);
    printf("Ciudad: ");
    scanf("%s",hotel3.city);
    printf("Tipo de hotel (0-Budget, 1-Inn, 2-Resort,3-Condo,4-Luxury,5-Country): ");
    scanf("%u",&hotel3.hotelType);
    printf("Numero de estrellas: ");
    scanf("%d",&hotel3.category);
    printf("Precio de habitacion doble: ");
    scanf("%f",&hotel3.priceDouble);
    printf("Distancia hasta el centro: ");
    scanf("%f",&hotel3.distanceFromCityCenter);
    printf("Piscina (0-No, 1-Si): ");
    scanf("%u",&hotel3.hasPool);
    printf("Gimnasio (0-No, 1-Si): ");
    scanf("%u",&hotel3.hasGym);
    printf("Estacion de metro cerca (0-No, 1-Si): ");
    scanf("%u",&hotel3.closeToSubway);
    printf("Porcentaje de ocupacion: ");
    scanf("%f",&hotel3.percentOccupation);

    //Hacemos las operaciones solicitadas
    printf("\n\nIntroduce el precio maximo que deseas pagar: ");
	scanf("%f",&maxPrice);
	printf("Ciudad donde buscas el hotel: ");
	scanf("%s",desiredCity);
	
	if(strcmp(hotel1.city,desiredCity)==0 && (hotel1.priceDouble <= maxPrice) && ((hotel1.priceDouble < hotel2.priceDouble) && (hotel1.priceDouble < hotel3.priceDouble) || (hotel1.priceDouble == hotel2.priceDouble) || (hotel1.priceDouble == hotel3.priceDouble))){
		printf("El hotel uno es el mejor. Estos son sus datos: \n");
		printf("Nombre: %s\n",hotel1.name);
		printf("Ciudad: %s\n",hotel1.city);
		printf("Precio por habitacion doble: %.2f\n",hotel1.priceDouble);
		printf("Categoria: %d estrellas\n",hotel1.category);
		printf("Tipo de hotel (0-Budget, 1-Inn, 2-Resort,3-Condo,4-Luxury,5-Country): %u\n",hotel1.hotelType);
	} else if (strcmp(hotel2.city,desiredCity)==0 && (hotel2.priceDouble <= maxPrice) && ((hotel2.priceDouble < hotel1.priceDouble) && (hotel2.priceDouble < hotel3.priceDouble) || (hotel2.priceDouble == hotel3.priceDouble))){
		printf("El hotel dos es el mejor. Estos son sus datos: \n");
		printf("Nombre: %s\n",hotel2.name);
		printf("Ciudad: %s\n",hotel2.city);
		printf("Precio por habitacion doble: %.2f\n",hotel2.priceDouble);
		printf("Categoria: %d estrellas\n",hotel2.category);
		printf("Tipo de hotel (0-Budget, 1-Inn, 2-Resort,3-Condo,4-Luxury,5-Country): %u\n",hotel2.hotelType);
	} else if (strcmp(hotel3.city,desiredCity)==0 && (hotel3.priceDouble <= maxPrice)){
		printf("El hotel tres es el mejor. Estos son sus datos: \n");
		printf("Nombre: %s\n",hotel3.name);
		printf("Ciudad: %s\n",hotel3.city);
		printf("Precio por habitacion doble: %.2f\n",hotel3.priceDouble);
		printf("Categoria: %d estrellas\n",hotel3.category);
		printf("Tipo de hotel (0-Budget, 1-Inn, 2-Resort,3-Condo,4-Luxury,5-Country): %u\n",hotel3.hotelType);
	} else {
		printf("No hay un hotel que cumpla las condiciones requeridas");
	}
}