#include <stdio.h>
#include <string.h>
#include "hotel.h"

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

void hotelCmpPoints(tHotel hotel1,tHotel hotel2,tHotel *h){
	float acceptablePrice;
	float acceptableDistance;
	int pointsOfH1;
	int pointsOfH2;
	
	printf("WHAT'S THE OPTIMAL DISTANCE? >> \n");
	scanf("%f",&acceptableDistance);
	printf("WHAT'S THE OPTIMAL PRICE? >> \n");
	scanf("%f",&acceptablePrice);
	
	pointsOfH1=hotelComputePoints(hotel1,acceptablePrice,acceptableDistance);
	pointsOfH2=hotelComputePoints(hotel2,acceptablePrice,acceptableDistance);
	
	if (pointsOfH1>=pointsOfH2){
		hotelCopy(hotel1,h);
	} else {
		hotelCopy(hotel2,h);
	}
	
}

int hotelComputePoints(tHotel hotel,float price, float distance){
	
	float calc=0;
	int points=0;
	
	if(hotel.hasGym || hotel.hasPool) calc+=5;
	if(hotel.closeToSubway) calc+=5;
	calc+=(100*(price-hotel.priceDouble)/price);
	calc+=(100*(distance-hotel.distanceFromCityCenter)/distance);
	points=(int)calc;
	printf("PUNCTUATION FOR HOTEL %s: %d\n",hotel.name,points);
	
	return points;
}

void hotelCopy(tHotel src,tHotel *dst){
	dst->id=src.id;
	strcpy(dst->brand, src.brand);
	strcpy(dst->name, src.name);
	dst->type=src.type;
	strcpy(dst->city, src.city);
	dst->category=src.category;
	dst->priceDouble=src.priceDouble;
	dst->distanceFromCityCenter=src.distanceFromCityCenter;
	dst->hasPool=src.hasPool;
	dst->hasGym=src.hasGym;
	dst->closeToSubway=src.closeToSubway;
	dst->percentOccupation=src.percentOccupation;
}