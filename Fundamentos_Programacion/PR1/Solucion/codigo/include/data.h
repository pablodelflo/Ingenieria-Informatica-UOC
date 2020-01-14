/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

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

/* Definition of a boolean type */
typedef enum {FALSE, TRUE} boolean;

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
              ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
              ERR_ENTRY_NOT_FOUND=-6,
              ERR_NO_CUSTOMER=-7,ERR_NO_HOTEL=-8,ERR_NO_FREE_GAP=-9} tError;

typedef int tCustomerId;
typedef int tHotelId;

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
} tHotel;

typedef struct {
	tHotel table[MAX_HOTELS];
	int nHotels;
} tHotelTable;


typedef enum {SINGLE, MARRIED, SEPARATED, DIVORCED, WIDOWED} tCivilState;
typedef enum {FAMILIAR, CONSERVATIVE, ADVENTUROUS, LONELY, CURIOUS, INNOVATIVE, DARED} tProfile; 

typedef struct {
  int day, month, year;
} tDate;

typedef struct {
    tCustomerId id;
    char name[MAX_NAME];
    char surname[MAX_SURNAME];
    char docNumber[MAX_DOC_NUMBER];
    tDate birthDate;
    char birthCity[MAX_CITY];
    tCivilState status;
    tProfile profile;
    int unsigned bookingsCounter;
    int unsigned points;
    float satisfaction;
} tCustomer;

typedef struct {
	tCustomer table[MAX_CUSTOMERS];
	int nCustomers;
} tCustomerTable;

/* Definition of the application data structure */
typedef struct {
	/* Path where data will be stored */
	char path[MAX_PATHNAME];
	
	/* Hotels table */
	tHotelTable hotels;
	
	/* Customers table */
	tCustomerTable customers;
	
} tAppData;

#endif /*__DATA_H*/