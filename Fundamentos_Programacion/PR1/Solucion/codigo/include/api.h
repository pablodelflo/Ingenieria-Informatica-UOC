#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appData_init(tAppData *object);

/* Load the application data from file */
void appData_load(tAppData *object, tError *error);

/* Save the application data to a file */
void appData_save(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appData_setPath(tAppData *object, const char *path);

/* 
 * API
 */

/* Return a table with the customers */
void getCustomers(tAppData object, tCustomerTable *result);

/* Get the customer information */
void getCustomer(tAppData object, tCustomerId customerId, tCustomer *customer, tError *retVal);

/* Add a new customer */
void addCustomer(tAppData *object, tCustomer customer, tError *retVal);

/* Remove a certain customer */
void removeCustomer(tAppData *object, tCustomer customer);

/* Return the table of hotels */
void getHotels(tAppData object, tHotelTable *result);

/* Get the hotel information */
void getHotel(tAppData object, tHotelId hotelId, tHotel *hotel, tError *retVal);

/* Add a new hotel */
void addHotel(tAppData *object, tHotel hotel, tError *retVal);
