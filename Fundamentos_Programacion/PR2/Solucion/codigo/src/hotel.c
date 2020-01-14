#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"

/* The content of the fields of the hotel structure is written into the string str */
void getHotelStr(tHotel hotel, int maxSize, char *str) {

    int length;
	    
    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d %s %s %s %d %d %d %.2f %.2f %d %d %d %.2f", 
             (int)hotel.id, hotel.brand, hotel.name, hotel.city, hotel.category,
			 (int)hotel.type, hotel.numRooms, hotel.price,
			 hotel.distanceFromCityCenter, (int)hotel.hasPool, 
			 (int)hotel.hasGym, (int)hotel.closeToSubway, hotel.percentOccupation);
	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the hotel structure */
void getHotelObject(const char *str, tHotel *hotel) {

	int aux_id, aux_type, aux_pool, aux_gym, aux_subway;

    /* read hotel data */
    sscanf(str, "%d %s %s %s %d %d %d %f %f %d %d %d %f", 
        &aux_id, hotel->brand, hotel->name, hotel->city, &hotel->category, 
        &aux_type, &hotel->numRooms, &hotel->price,  
        &hotel->distanceFromCityCenter, &aux_pool, &aux_gym, &aux_subway,
        &hotel->percentOccupation );

    hotel->id = (tHotelId)aux_id;
    hotel->type = (tTypeHotel)aux_type;
    hotel->hasPool = (boolean)aux_pool;
    hotel->hasGym = (boolean)aux_gym;
    hotel->closeToSubway = (boolean)aux_subway;
}

void hotel_cpy(tHotel *dst, tHotel src) 
{    
    dst->id = src.id;
    strcpy(dst->brand,src.brand);
	strcpy(dst->name,src.name);
	strcpy(dst->city,src.city);
	dst->category = src.category;
	dst->type = src.type;
	dst->numRooms = src.numRooms;
	dst->price = src.price;
	dst->distanceFromCityCenter = src.distanceFromCityCenter;
	dst->hasPool = src.hasPool;
	dst->hasGym = src.hasGym;
	dst->closeToSubway = src.closeToSubway;
	dst->percentOccupation = src.percentOccupation;
}

int hotel_cmp(tHotel d1, tHotel d2)
{
    int result = 0;
    	
    result= strcmp(d1.brand,d2.brand);
    if (result==0) 
    {
        result= strcmp(d1.name,d2.name);
        if (result==0)
        {
            result= strcmp(d1.city,d2.city);
            if (result==0)
            {
                if (d1.category > d2.category) 
                    result = 1;
                else if (d1.category < d2.category)
                    result = -1;
                else{
                    if (d1.type > d2.type)
                        result = 1;
                    else if (d1.type < d2.type)
                        result = -1;
                    else{
                        if (d1.numRooms > d2.numRooms)
                            result = 1;
                        else if (d1.numRooms < d2.numRooms)
                            result = -1;
                        else{
                            if (d1.price > d2.price)
                                result = 1;
                            else if (d1.price < d2.price)
                                result = -1;
                            else{
                                if (d1.distanceFromCityCenter > d2.distanceFromCityCenter)
                                    result = 1;
                                else if (d1.distanceFromCityCenter < d2.distanceFromCityCenter)
                                    result = -1;
                                else{
                                    if (d1.hasPool > d2.hasPool)
                                        result = 1;
                                    else if (d1.hasPool < d2.hasPool)
                                        result = -1;
                                    else{
                                        if (d1.hasGym > d2.hasGym)
                                            result = 1;
                                        else if (d1.hasGym < d2.hasGym)
                                            result = -1;
                                        else {
                                            if (d1.closeToSubway > d2.closeToSubway)
                                                result = 1;
                                            else if (d1.closeToSubway < d2.closeToSubway)
                                                result = -1;
                                            else{
                                                if (d1.percentOccupation > d2.percentOccupation)
                                                    result = 1;
                                                else if (d1.percentOccupation < d2.percentOccupation)
                                                    result = -1;
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

    return result;
}

int computePoints(tHotel hotel, float price, float distance)
{
    float points;
    
    points= 0.0;
    
    /* points for having gym or pool */
    if (hotel.hasGym || hotel.hasPool)
        points += 5.0;
        
    /* points for being close to subway */
    if (hotel.closeToSubway)
        points += 5.0;
        
    /* points for adjusted price */
    points += ((price - hotel.price) / price) * 100.0;

    /* points for centric location */
    points += ((distance - hotel.distanceFromCityCenter) / distance) * 100.0;

    return (int)(points + 0.5);
}

void hotelTable_init(tHotelTable *hotelTable) {
	
	hotelTable->nHotels= 0;
}

void hotelTable_add(tHotelTable *tabHotels, tHotel hotel, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new hotel */
	if(tabHotels->nHotels>=MAX_HOTELS)
		*retVal = ERR_MEMORY;
		
	if (*retVal == OK) {
		/* Add the new hotel to the end of the table */
		hotel_cpy(&tabHotels->table[tabHotels->nHotels],hotel);
		tabHotels->nHotels++;
	}
	
}

int hotelTable_find(tHotelTable tabHotels, tHotelId id) {

	int idx = NO_HOTEL;
	
	int i=0;
	while(i< tabHotels.nHotels && idx==NO_HOTEL) {
		/* Check if the id is the same */
		if(id==tabHotels.table[i].id)  {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void hotelTable_save(tHotelTable tabHotels, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all customers to the file */
        for(i=0;i<tabHotels.nHotels;i++) {
            getHotelStr(tabHotels.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void hotelTable_load(tHotelTable *tabHotels, const char* filename, tError *retVal) {
	
	*retVal = OK;

	FILE *fin=0;
	char line[MAX_LINE];
	tHotel newHotel;
	
	/* Initialize the output table */
	hotelTable_init(tabHotels);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the hotels */
		while(!feof(fin) && tabHotels->nHotels<MAX_HOTELS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getHotelObject(line, &newHotel);
				/* Add the new hotel to the output table */
				hotelTable_add(tabHotels, newHotel, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

void hotelTable_filterByType(tHotelTable tabHotels, tTypeHotel type, tHotelTable *result) {

	tError retVal;
	int i;
	hotelTable_init(result);
	for(i=0;i<tabHotels.nHotels;i++) {
		if (type == tabHotels.table[i].type){
			hotelTable_add(result, tabHotels.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabHotels which cannot have more than MAX_HOTELS*/
		}
	}

}

void hotelTable_getUrbanHotels(tHotelTable tabHotels, tHotelTable *result) {

	tError retVal;
	int i;
	hotelTable_init(result);
	for(i=0;i<tabHotels.nHotels;i++) {
		if (tabHotels.table[i].closeToSubway && 
            tabHotels.table[i].distanceFromCityCenter < 2.0){
            hotelTable_add(result, tabHotels.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabHotels which cannot have more than MAX_HOTELS*/
		}
	}
}

float hotelTable_computeAverageOccupation(tHotelTable tabHotel, char *city) {

	float avgOcc = 0.0;

	int totalRooms=0, i;
	int occupiedRooms = 0;
	
	for(i=0;i<tabHotel.nHotels;i++) {
		if (strcmp( tabHotel.table[i].city, city ) == 0){
			occupiedRooms += tabHotel.table[i].numRooms * tabHotel.table[i].percentOccupation / 100.0;			
			totalRooms += tabHotel.table[i].numRooms;
		}
	}
	if (totalRooms>0)
		avgOcc = 100.0 * (float)occupiedRooms / (float)totalRooms;

	return avgOcc;
}

float hotelTable_getMaxRoomPrice(tHotelTable tabHotel){

	float maxPrice = 0;
	
	int i;
	
	for(i=0;i<tabHotel.nHotels;i++) {
		if (tabHotel.table[i].price > maxPrice){
			maxPrice = tabHotel.table[i].price;
		}
	}

	return maxPrice;
}

void hotelTable_select(tHotelTable tabHotel, char *city, 
                        float price, float distance, int points,  
                        tHotelTable *result)
{
    int i, p;

	hotelTable_init(result);

    for (i= 0; i < tabHotel.nHotels; i++)
    {
        if (strcmp(tabHotel.table[i].city, city) == 0)
        {
            p= computePoints(tabHotel.table[i], price, distance);
            if ( p >= points) 
            {
                    hotel_cpy( &(result->table[ result->nHotels ]), tabHotel.table[i] );
                    result->nHotels= result->nHotels + 1;
            }
        }
    }
}

void customerRecommendation(tCustomer customer, 
                            tHotelTable hotels,
                            char *city, 
                            float price, float distance, int points,
                            tHotelTable *result) 
{
	int i;
    tError retVal;
    tHotelTable selectedHotels;
        
    hotelTable_select(hotels,city,price,distance,points,&selectedHotels);
    hotelTable_init(result);

	for(i=0;i<selectedHotels.nHotels;i++) 
    {
		if (strcmp( customer.birthCity, selectedHotels.table[i].city ) != 0) {
			hotelTable_add(result, selectedHotels.table[i], &retVal);
		}
	}
}
