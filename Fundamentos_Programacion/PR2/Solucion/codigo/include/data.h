/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

/*********************** 
 *     CONSTANTS
 **********************/
 
#define MAX_HOTELS 50
#define MAX_BRAND 15+1
#define MAX_HOTEL_NAME 15+1
#define MAX_ADDRESS 15+1
#define MAX_CITY 15+1

#define MAX_NAME 15+1
#define MAX_SURNAME 15+1
#define MAX_COUNTRY_CODE 2+1
#define MAX_DOC_NUMBER 9+1
#define MAX_CUSTOMERS 100
#define MAX_PATHNAME 500
#define MAX_LINE 514
#define NO_HOTEL -1
#define NO_CUSTOMER -1
#define NO_BOOKING -1
#define MAX_FLOORS 4
#define MAX_ROOMS_PER_FLOOR 10
#define MAX_MOVEMENTS 5
#define MAX_ROOMS_PER_BOOKING 4
#define MAX_BOOKINGS 10

#define BREAKFAST_PRICE  10.0
#define HALF_BOARD_PRICE 25.0
#define FULL_BOARD_PRICE 40.0

#define SINGLE_ROOM_PRICE_FACTOR   0.75
#define DOUBLE_ROOM_PRICE_FACTOR   1.0
#define TRIPLE_ROOM_PRICE_FACTOR   1.5
#define QUAD_ROOM_PRICE_FACTOR     1.75
#define LATE_CHECKOUT_PRICE_FACTOR 1.2

/*********************** 
 *     DATA TYPES
 **********************/

/* Definition of a boolean type */
typedef enum {FALSE, TRUE} boolean;

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6,
              ERR_NO_CUSTOMER=-7,ERR_NO_HOTEL=-8,ERR_NO_FREE_GAP=-9} tError;

typedef int tCustomerId;
typedef int tHotelId;

typedef struct {
  int day, month, year;
} tDate;

typedef enum { BUDGET, INN, RESORT, CONDO, LUXURY, COUNTRY } tTypeHotel; 

typedef struct {
    tHotelId id; 
    char brand[MAX_BRAND]; 
    char name[MAX_NAME]; 
    char city[MAX_CITY]; 
    int category;
    tTypeHotel type;
    int numRooms; 	
    float price; /* reference price: double room */
    float distanceFromCityCenter;
    boolean hasPool;
    boolean hasGym;
    boolean closeToSubway;
    float percentOccupation;
    int occupiedRooms;
    boolean layout[MAX_FLOORS][MAX_ROOMS_PER_FLOOR];
} tHotel;

typedef struct {
	tHotel table[MAX_HOTELS];
	int nHotels;
} tHotelTable;

typedef enum {
  SINGLE, MARRIED, SEPARATED, DIVORCED, WIDOWED
} tCivilState;

typedef enum {
  FAMILIAR, CONSERVATIVE, ADVENTUROUS, LONELY, CURIOUS, INNOVATIVE, DARED
} tProfile;

typedef struct {
    tCustomerId id;
    char name[MAX_NAME];
    char surname[MAX_SURNAME];	
    char docNumber[MAX_DOC_NUMBER];	
    tDate birthDate;
    char birthCity[MAX_CITY];
    tCivilState status;
    tProfile profile;
    int bookingsCounter;
    int points;
    float satisfaction;
} tCustomer;

typedef struct {
	tCustomer table[MAX_CUSTOMERS];
	int nCustomers;
} tCustomerTable;

typedef enum {
  ROOM_ONLY, ROOM_AND_BREAKFAST, HALF_BOARD, FULL_BOARD
} tRegime;

typedef struct {
    tCustomerId id;
    int nGuests;
    tDate checkInDate;
    tDate checkOutDate;
    tRegime regime;
    float price;
    int nAssignedRooms;
    int assignedRooms[MAX_ROOMS_PER_BOOKING];
} tBooking;

typedef struct {
	tBooking table[MAX_BOOKINGS];
	unsigned int nElem;
} tBookingList;

typedef struct {
	tCustomerId table[MAX_CUSTOMERS];
	unsigned int nElem;
} tCustomerQueue;

typedef struct {
    tHotelId id;
    tDate date;
    tBookingList pendingBookings;
    tBookingList currentBookings;
    tBookingList completedBookings;
    tCustomerQueue checkinQueue;
    tCustomerQueue checkoutQueue;
} tMovement;

typedef struct {
    tMovement table[MAX_MOVEMENTS];
    int nMovements;
} tMovementTable;

/* Definition of the application data structure */
typedef struct 
{
	/* Path where data will be stored */
	char path[MAX_PATHNAME];

	/* Hotels table */
	tHotelTable hotels;

	/* Customers table */
	tCustomerTable customers;

	/* Movements table */
    tMovementTable movements;

} tAppData;

/*********************** 
 *    COMMON HEADERS
 **********************/

/* Compare two dates */
int date_cmp( tDate d1, tDate d2 );

/* Copy a date onto another date */
void date_cpy( tDate *d1, tDate d2 );

#endif /*__DATA_H*/