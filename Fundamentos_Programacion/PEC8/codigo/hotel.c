#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"


void hotelRead(tHotel *h)
{
  printf("ID >> \n");
  scanf("%d",&h->id);
  printf("BRAND >> \n");
  scanf("%s",h->brand);
  getchar();
  printf("NAME >> \n");
  scanf("%s",h->name);
  getchar();
  printf("CITY >> \n");
  scanf("%s",h->city);
  getchar();
  printf("NUMBER OF ROOMS (AN INTEGER) >> \n");
  scanf("%d",&h->numRooms);
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

void hotelCopy(tHotel *dst, tHotel src) {
	dst->id=src.id;
	strcpy(dst->brand,src.brand);
	strcpy(dst->name,src.name);
	strcpy(dst->city,src.city);
	dst->category=src.category;
	dst->type=src.type;
	dst->numRooms=src.numRooms;
	dst->priceDouble=src.priceDouble;
	dst->distanceFromCityCenter=src.distanceFromCityCenter;
	dst->hasPool=src.hasPool;
	dst->hasGym=src.hasGym;
	dst->closeToSubway=src.closeToSubway;
	dst->percentOccupation=src.percentOccupation;
}

void getHotelObject(const char *str,tHotel *hotel) {
	int aux_id,aux_type,aux_pool,aux_gym,aux_subway;

	/* read hotel data */
	sscanf(str, "%d %s %s %s %d %d %d %f %f %d %d %d %f",
	&aux_id,hotel->brand,hotel->name,hotel->city,&hotel->category,
	&aux_type,&hotel->numRooms,&hotel->priceDouble,
	&hotel->distanceFromCityCenter,&aux_pool,&aux_gym,&aux_subway,
	&hotel->percentOccupation);

	hotel->id=aux_id;
	hotel->type=(tTypeHotel)aux_type;
	hotel->hasPool=(tBoolean)aux_pool;
	hotel->hasGym=(tBoolean)aux_gym;
	hotel->closeToSubway=(tBoolean)aux_subway;
}

void hotelsTableAddElement(tHotelTable *tabHotels, tHotel hotel) {
	/* Check if there enough space for the new hotel */
	if(tabHotels->nHotels>=MAX_HOTELS) {
		printf("ERROR ADDING A HOTEL INTO TABLE\n");
	}
	else {
		/* Add the new hotel to the end of the table */
		hotelCopy(&tabHotels->hotels[tabHotels->nHotels],hotel);
		tabHotels->nHotels++;
	}
}

void hotelsTableLoadDataFromFile(tHotelTable *tabHotels,const char* filename) {
	FILE *fin=0;
	char line[MAX_LINE];
	tHotel newHotel;

	/* Initialize the output table */
	hotelsTableInitialize(tabHotels);

	/* Open the input file */

	
	if((fin=fopen(filename,"r"))!=NULL) {
		/* Read all the hotels */
		while(!feof(fin) && tabHotels->nHotels<MAX_HOTELS) {
			/* Remove any content from the line */
			line[0]='\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line,MAX_LINE-1,fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getHotelObject(line,&newHotel);
				/* Add the new hotel to the output table */
				hotelsTableAddElement(tabHotels,newHotel);
			}
		}
		/* Close the file */
		fclose(fin);
	}
}

int hotelComputePoints(tHotel hotel,float price,float distance) {
	float points=0.0;

	points=(price-hotel.priceDouble)/price*100.0f;
	points=points+(distance-hotel.distanceFromCityCenter)/distance*100.0f;
	if(hotel.hasGym || hotel.hasPool) {
		points=points+5;
	}
	if(hotel.closeToSubway) {
		points=points+5;
	}
  printf("PUNCTUATION FOR HOTEL %s: %d\n",hotel.name,(int)points);
	return((int)points);
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
  printf("NUMBER OF ROOMS: %d\n", h.numRooms);
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


void hotelsTableInitialize(tHotelTable *selectedHotelsTable){
	selectedHotelsTable->nHotels=0;
}

void hotelsTableSelect(tHotelTable hotelsTable, char city[MAX_CITY], float price, float distance, int points, tHotelTable *selectedHotelsTable){	
	int i;
	int j=0;
	int puntuation = 0;
	
	hotelsTableInitialize(selectedHotelsTable);	
	for (i=0;i<hotelsTable.nHotels;i++){
		if(strcmp(hotelsTable.hotels[i].city,city)==0){
			puntuation=hotelComputePoints(hotelsTable.hotels[i],price,distance);
			if (puntuation >= points){
				hotelCopy(&selectedHotelsTable->hotels[j],hotelsTable.hotels[i]);
				selectedHotelsTable->nHotels++;
				j++;
			}
		}
	}
}

float hotelsComputeAverageOccupation(tHotelTable hotelTable,char city[MAX_CITY]){
	float occupation=0;
	int j;
	float totalRooms=0;
	float occupiedRooms=0;
	float aux=0;
	
	for(j=0;j<hotelTable.nHotels;j++){
		if(strcmp(hotelTable.hotels[j].city,city)==0){
			aux=((float)hotelTable.hotels[j].numRooms*hotelTable.hotels[j].percentOccupation)/100;
			totalRooms=totalRooms+(float)hotelTable.hotels[j].numRooms;
			occupiedRooms=occupiedRooms+aux;
		}
	}
	occupation=100*occupiedRooms/totalRooms;
	
	return occupation;
}