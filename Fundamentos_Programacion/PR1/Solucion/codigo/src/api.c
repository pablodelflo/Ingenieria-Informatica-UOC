#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include "customer.h"
#include "hotel.h"

void appData_init(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the customer table */
	customerTable_init(&(object->customers));
	
	/* Initialize the hotels table */
	hotelTable_init(&(object->hotels));
}

void appData_load(tAppData *object, tError *retVal) {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Load the table of hotels */
	sprintf(path,"%shotels.txt", object->path);
	hotelTable_load(&(object->hotels), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of hotels\n");
	}

	/* Load the table of customers */
	sprintf(path,"%scustomers.txt", object->path);
	customerTable_load(&(object->customers), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of customers\n");
	}
}

void appData_save(tAppData object, tError *retVal)  {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Save the table of hotels */
	sprintf(path,"%shotels.txt", object.path);
	hotelTable_save(object.hotels, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of hotels\n");
	}
	
	/* Save the table of customers */
	sprintf(path,"%scustomers.txt", object.path);
	customerTable_save(object.customers, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of customers\n");
	}
}

void appData_setPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, 255);	
}


/*********************** 
 *        API
 **********************/

void getHotels(tAppData object, tHotelTable *result) {
	*result = object.hotels;	
}

void getHotel(tAppData object, tHotelId hotelId, tHotel *hotel, tError *retVal) {
	
	int i;
	*retVal = OK;

	/* Check if there is a hotel with this id */
	i = hotelTable_find(object.hotels, hotelId);
	if (i!=NO_HOTEL) {
		hotel_cpy(hotel,object.hotels.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addHotel(tAppData *object, tHotel hotel, tError *retVal) 
{
	*retVal = OK;
	tHotel tmp;

	/* Check if there is another hotel with the same id */
	getHotel(*object, hotel.id, &tmp, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new hotel using the hotel table method */
		hotelTable_add(&(object->hotels), hotel, retVal);
	}
}

void getCustomers(tAppData object, tCustomerTable *result) {
	*result = object.customers;	
}

void getCustomer(tAppData object, tCustomerId id, tCustomer *customer, tError *retVal) {
	
	int i;
	*retVal = OK;
	
	/* Check if there is a customer with this id */
	i = customerTable_find(object.customers, id);
	if (i!=NO_CUSTOMER) {
		customer_cpy(customer,object.customers.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addCustomer(tAppData *object, tCustomer customer, tError *retVal) {
	*retVal = OK;
	tCustomer tmpCustomer;
    
	/* Check if there is another customer with the same id */
	getCustomer(*object, customer.id, &tmpCustomer, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new customer using the customer table method */
		customerTable_add(&(object->customers), customer, retVal);
	}
}

void removeCustomer(tAppData *object, tCustomer customer) 
{	
	/* Call the method from the customers table*/
	customerTable_del(&(object->customers), customer);
}
