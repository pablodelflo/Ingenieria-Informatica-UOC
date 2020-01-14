/***************************************************************
* Fichero: PEC6.c
* Autor: Pablo J. Delgado Flores
* Fecha: 11/11/2019
* Descripcion: Este fichero contiene la solucion al ejercicio
* planteado en la PEC6 de Fundamentos de Programacion
* tomando como base el fichero .c adjunto en el .zip
* del enunciado
***************************************************************/
#include <stdio.h>
#include <string.h>

//DECLARACION DE CONSTANTES
#define MAX_BRAND 16
#define MAX_NAME 16
#define MAX_CITY 16

//DECLARACION DE TYPEHOTEL, BOLEAN Y STRUCT PARA THOTEL
typedef enum {BUDGET,INN,RESORT,CONDO,LUXURY,COUNTRY} tTypeHotel;
typedef enum {FALSE,TRUE} tBoolean;

typedef struct {
  int id;
  char brand[MAX_BRAND];
  char name[MAX_NAME];
  char city[MAX_CITY];
  int category;
  tTypeHotel type;
  float priceDouble; /* reference price: double room */
  float distanceFromCityCenter;
  tBoolean hasPool;
  tBoolean hasGym;
  tBoolean closeToSubway;
  float percentOccupation;
} tHotel;

//DEFINICION DE HEADERS DE FUNCIONES
void hotelRead(tHotel *h);
void hotelWrite(tHotel h);
int hotelCmp(tHotel h1,tHotel h2);
tBoolean hotelAcceptable(tHotel h,float acceptablePrice, float acceptableDistance);

//to complete

/*INICIO DEL MAIN PRINCIPAL*/
int main(int argc, char **argv)
{
  tHotel h1;
  tHotel h2;
  tHotel h;
  int bestHotel;
  float acceptablePrice;
  float acceptableDistance;
  tBoolean isH1Acceptable;
  tBoolean isH2Acceptable;
  
  printf("ENTER DATA FOR HOTEL 1\n");
  hotelRead(&h1);
  printf("ENTER DATA FOR HOTEL 2\n");
  hotelRead(&h2);
  printf("WHAT'S THE MAXIMUM ACCEPTABLE PRICE? >> \n");
  scanf("%f",&acceptablePrice);
  printf("WHAT'S THE MAXIMUM ACCEPTABLE DISTANCE FROM CITY CENTER? >> \n");
  scanf("%f",&acceptableDistance);
  isH1Acceptable=hotelAcceptable(h1,acceptablePrice,acceptableDistance);
  isH2Acceptable=hotelAcceptable(h2,acceptablePrice,acceptableDistance);
  if ((isH1Acceptable == TRUE) && (isH2Acceptable == TRUE) && (strcmp(h1.city,h2.city)==0)){
  	bestHotel=hotelCmp(h1,h2);
  	if (bestHotel==-1){
  		printf("THE HOTEL 1 SUITS YOU BETTER, AND THE DATA ARE \n");
  		hotelWrite(h1);
  		printf("THE SECOND BEST HOTEL IS HOTEL 2 AND THE DATA ARE \n");
  		hotelWrite(h2);
	  } else if (bestHotel==1){
	  	printf("THE HOTEL 2 SUITS YOU BETTER, AND THE DATA ARE \n");
	  	hotelWrite(h2);
	  	printf("THE SECOND BEST HOTEL IS HOTEL 1 AND THE DATA ARE \n");
  		hotelWrite(h1);
	  } else {
	  	printf("THE HOTELS CAN'T BE COMPARED");
	  }
  } else {
  	printf("THE HOTELS CAN'T BE COMPARED");
  }
  return 0;
}

//CUERPO DE LAS FUNCIONES
void hotelRead(tHotel *h)
{
  printf("ID >> \n");
  scanf("%d",&h->id);
  printf("BRAND >> \n");
  scanf("%s",h->brand);
  printf("NAME >> \n");
  scanf("%s",h->name);
  printf("CITY >> \n");
  scanf("%s",h->city);
  printf("CATEGORY (AN INTEGER) >> \n");
  scanf("%d",&h->category);
  printf("TYPE (0-BUDGET, 1-INN, 2-RESORT, 3-CONDO, 4-LUXURY, 5-COUNTRY) >> \n");
  scanf("%u",&h->type);
  printf("PRICE FOR A DOUBLE ROOM >> \n");
  scanf("%f",&h->priceDouble);
  printf("DISTANCE TO CITY CENTER? (IN KM) >> \n");
  scanf("%f",&h->distanceFromCityCenter);
  printf("IS IT CLOSE TO A SUBWAY STATION? (0-FALSE, 1-TRUE) >> \n");
  scanf("%u",&h->closeToSubway);
  printf("HAS SWIMMING POOL? (0-FALSE, 1-TRUE) >> \n");
  scanf("%u",&h->hasPool);
  printf("HAS GYM? (0-FALSE, 1-TRUE) >> \n");
  scanf("%u",&h->hasGym);
  printf("PERCENT OCCUPATION >> \n");
  scanf("%f",&h->percentOccupation);
}


void hotelWrite(tHotel h)
{
  printf("HOTEL'S DATA: \n");
  printf("ID: %d\n", h.id);
  printf("BRAND: %s\n", h.brand);
  printf("NAME: %s\n", h.name);
  printf("CITY: %s\n", h.city);
  printf("CATEGORY: %d\n", h.category);
  printf("TYPE: %u\n", h.type);
  printf("PRICE FOR A DOUBLE ROOM: %.2f\n", h.priceDouble);
  printf("DISTANCE TO CITY CENTER: %.2f\n", h.distanceFromCityCenter);
  printf("CLOSE TO A SUBWAY STATION: ");
  if (h.closeToSubway) printf ("YES\n");
  else printf("NO\n");
  printf("HAS SWIMMING POOL: ");
  if (h.hasPool) printf ("YES\n");
  else printf("NO\n");
  printf("HAS A GYM: ");
  if (h.hasGym) printf ("YES\n");
  else printf("NO\n");
  printf("PERCENT OCCUPATION: %.2f\n", h.percentOccupation);
}

//code for hotelCmp and hotelAcceptable
int hotelCmp(tHotel h1, tHotel h2)
{
	int bestHotelF=0;
	if (strcmp(h1.brand,h2.brand)<0){
		bestHotelF=-1;
	} else {
		if (strcmp(h1.brand,h2.brand)>0){
			bestHotelF=1;
		} else {
			if (h1.category<h2.category){
				bestHotelF=-1;
			} else {
				if (h2.category<h1.category){
					bestHotelF=1;
				} else {
					if (h1.priceDouble<h2.priceDouble){
						bestHotelF=-1;
					} else {
						if (h2.priceDouble<h1.priceDouble){
							bestHotelF=1;
						} else {
							if (h1.distanceFromCityCenter<h2.distanceFromCityCenter){
								bestHotelF=-1;
							} else {
								if (h2.distanceFromCityCenter<h1.distanceFromCityCenter){
									bestHotelF=1;
								} else {
									if (h1.percentOccupation<h2.percentOccupation){
										bestHotelF=-1;
									} else {
										if (h2.percentOccupation<h1.percentOccupation){
											bestHotelF=1;
										} else {
											if (h1.closeToSubway>h2.closeToSubway){
												bestHotelF=-1;
											} else {
												if (h2.closeToSubway>h1.closeToSubway){
													bestHotelF=1;
												} else {
													if (h1.hasPool==0){
														bestHotelF=-1;
													} else {
														if (h2.hasPool==0){
															bestHotelF=1;
														} else {
															if (h1.hasGym==0){
																bestHotelF=-1;
															} else {
																if (h2.hasGym==0){
																	bestHotelF=1;
																} else {
																	bestHotelF=0;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return bestHotelF;
}

tBoolean hotelAcceptable(tHotel h,float acceptablePrice, float acceptableDistance) {
	tBoolean hAccepF;
	if (((h.hasPool==1) || (h.hasGym==1)) && ((h.distanceFromCityCenter<acceptableDistance) || (h.closeToSubway==1)) && (h.priceDouble<acceptablePrice)){
		hAccepF=TRUE;
	} else {
		hAccepF=FALSE;
	}
	return hAccepF;
}