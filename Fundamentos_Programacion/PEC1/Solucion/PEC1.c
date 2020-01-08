/***************************************************************
* Fichero: PEC1.c
* Autor: Pablo J. Delgado Flores
* Fecha: 30/09/2019
* Descripcion: Este fichero contiene la solución al ejercicio
* planteado en la PEC1 de Fundamentos de Programación
***************************************************************/
#include <stdio.h>

/*Definición del enumerado y booleano*/
typedef enum {BUDGET,INN,RESORT,CONDO,LUXURY,COUNTRY} tHotelT;
typedef enum {FALSE,TRUE} boolean;

int main(int argc, char **argv){
    /*Definicion de variables del programa*/
    int idHotel;                //Número de identificación del hotel
    tHotelT hotelType;          //Tipo de hotel
    int hotelCat;               //Categoría del hotel (número estrellas)
    char hotelRating;           //Valoración interna de UOCBookings
    int roomsNumber;            //Número de habitaciones
    float priceDRoom;           //Precio de las habitaciones dobles
    float centerDistance;       //Distancia desde el hotel al centro de la ciudad
    boolean hasPool;            //Registrar si el hotel tiene piscina o no
    float occupationPercent;    //Porcentaje de ocupación
    
    /*Lectura de información*/
    printf("Introduce el ID del hotel: ");
    scanf("%d", &idHotel);
    printf("Introduce el numero de estrellas del hotel: ");
    scanf("%d", &hotelCat);
    getchar();
    printf("Introduce la valoracion de UOCBookings: ");
    scanf("%c", &hotelRating);
    printf("Introduce el numero de habitaciones: ");
    scanf("%d", &roomsNumber);
    printf("Introduce el precio de una habitacion doble: ");
    scanf("%f", &priceDRoom);
    printf("Introduce la distancia que hay hasta el centro: ");
    scanf("%f", &centerDistance);
    printf("Introduce el porcentaje de ocupacion del hotel: ");
    scanf("%f", &occupationPercent);
    
    /*Pintar información introducida por pantalla*/
	printf("\n\n");
    printf("ID del hotel: %d\n", idHotel);
    printf("Categoria del hotel (en numero de estrellas): %d\n", hotelCat);
    printf("Introduce la valoracion de UOCBookings: %c\n", hotelRating);
    printf("Numero de habitaciones: %d\n", roomsNumber);
    printf("Precio de la habitacion doble: %.2f\n", priceDRoom);
    printf("Distancia hasta el centro: %.2f\n", centerDistance);
    printf("Porcentaje de ocupacion del hotel: %.2f\n", occupationPercent);
	printf("\n\n");
    
	return 0;
}