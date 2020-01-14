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

/* Finds the booking of a customer within a list  */
int findCustomerBooking( tBookingList bookings, tCustomerId customerId );

/* Frees the rooms of a booking */
void freeRoomsOfBooking(tHotel *hotel, tBooking booking);

/* Calculates the price of a booking */
float calculatePrice(tHotel hotel, tBooking booking, tDate date);

/* Processes the checkouts in a hotel */
void processCheckouts( tHotel *hotel, tCustomerTable customers, tDate date, tCustomerQueue *queue, 
                       tBookingList *currentBookings, tBookingList *completedBookings );
                       
/* Returns the number of available rooms of a given capatity */
int availableRooms(tHotel hotel, int capacity);

/* Assigns a number of rooms of a given capacity in a hotel and register them in the booking */
void assignRoom(tHotel *hotel, int capacity, int amount, tBooking *booking);

/* Assigns the rooms of a booking */
void assignRoomsForBooking(tHotel *hotel, tBooking *booking);

/* Updates the occupation of the hotel according to ongoing bookings */
void updateHotelOccupation( tHotel *hotel, tBookingList currentBookings );

/* Processes the checkins in a hotel */
void processCheckins( tHotel *hotel, tCustomerTable customers, tDate date, tCustomerQueue *queue, 
                      tBookingList *pendingBookings, tBookingList *currentBookings );

/* Processes a hotel movements */
void processMovement( tMovement *movement, 
                      tCustomerTable *customers, tHotelTable *hotels, tError *retVal );

/* Processes all hotels movements */
void processAllMovements(tAppData *object, tError *retVal);
