#include <stdio.h>
#include "hotel.h"

int main(int argc, char **argv)
{
	char file[11+1];
	tHotelTable hotelsTable;
	tHotelTable selectedHotelsTable;
	char desiredCity[15+1];
	float acceptablePrice = 0;
	float acceptableDistance = 0;
	int neededPoints = 0;
	int k;
	float percentOccupation = 0;
	
	printf("LOAD DATA FROM FILENAME? >> \n");
	scanf("%s",file);
	hotelsTableLoadDataFromFile(&hotelsTable,file);
	printf("HOTELS SUCCESSFULLY LOADED! \n");
	printf("CITY NAME? >> \n");
	scanf("%s",desiredCity);
	printf("WHAT'S THE OPTIMAL PRICE? >> \n");
	scanf("%f",&acceptablePrice);
	printf("WHAT'S THE OPTIMAL DISTANCE? >> \n");
	scanf("%f",&acceptableDistance);
	printf("NUMBER OF NEEDED POINTS? >> \n");
	scanf("%d",&neededPoints);
	hotelsTableSelect(hotelsTable,desiredCity,acceptablePrice,acceptableDistance,neededPoints,&selectedHotelsTable);
	if(selectedHotelsTable.nHotels==0){
		printf("THERE ARE NO AVAILABLE HOTELS WITH THIS CRITERION \n");
	} else {
		printf("WE FOUND %d HOTELS\n",selectedHotelsTable.nHotels);
		printf("LIST OF SELECTED HOTELS >> \n");
		for(k=0;k<selectedHotelsTable.nHotels;k++){
			hotelWrite(selectedHotelsTable.hotels[k]);
		}
	}
	
	percentOccupation=hotelsComputeAverageOccupation(hotelsTable,desiredCity);
	printf("THE MEAN PERCENTAGE OCCUPATION FOR THE CITY OF %s IS %.2f\n",desiredCity,percentOccupation);
}