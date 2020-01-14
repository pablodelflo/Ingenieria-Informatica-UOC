#include "data.h"

/* Get a textual representation of a hotel */
void getHotelStr(tHotel hotel, int maxSize, char *str);

/* Get a hotel object from its textual representation */
void getHotelObject(const char *str, tHotel *hotel);

/* Copy the hotel data in src to dst*/
void hotel_cpy(tHotel *dst, tHotel src);

/* Compares the hotel data of p1 and p2*/
int hotel_cmp(tHotel p1, tHotel p2);

/* Computes points for the given hotel according to the desired price and distance to center */
int computePoints(tHotel hotel, float price, float distance);

/* Initializes the given hotels table */
void hotelTable_init(tHotelTable *hotelTable);

/* Add a new hotel to the table of hotels */
void hotelTable_add(tHotelTable *tabHotels, tHotel hotel, tError *retVal);

/* Find a hotel in the table */
int hotelTable_find(tHotelTable tabHotels, tHotelId id);

/* Load the table of hotels from a file */
void hotelTable_load(tHotelTable *tabHotels, const char* filename, tError *retVal);

/* Save a table of hotels to a file */
void hotelTable_save(tHotelTable tabHotels, const char* filename, tError *retVal);

/* Obtain from a table of hotels those of a given type */
void hotelTable_filterByType(tHotelTable tabHotels, tTypeHotel type, tHotelTable *result);

/* Obtain from a table of hotels those that are urban */
void hotelTable_getUrbanHotels(tHotelTable tabHotels, tHotelTable *result);

/* Obtain from a table of hotels the average occupation by city */
float hotelTable_computeAverageOccupation(tHotelTable tabHotel, char *city);

/* Obtain from a table of hotels the maximum price per room of a hotel */
float hotelTable_getMaxRoomPrice(tHotelTable tabHotel);

/* Selects hotels in a city with -at least- the given amount of points according to
 *  its price and distance to center */
void hotelTable_select(tHotelTable tabHotel, char *city, 
     float price, float distance, int points,  
     tHotelTable *result);

/* Calulates the recommended hotels for the specified customer. Hotels are based in the specified city
 * and have a desired price, distante to center and points. */
void customerRecommendation(tCustomer customer, 
                            tHotelTable hotels,
                            char *city, float price, float distance, int points,
                            tHotelTable *result);