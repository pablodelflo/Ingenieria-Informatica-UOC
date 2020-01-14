#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "hotel.h"
#include "customer.h"

int getOption(int numOptions) {
	int option=0;
		
	while(option<1 || option>numOptions) {
		/* Read the input */
		printf(">> ");
			scanf("%u", &option);
		getchar();
		
		/* Check the user input */
		if(option<1 || option>numOptions) {
			printf("Incorrect option.\n");
		}
	}
	 return option;
}

void readCustomer(tCustomer *customer, tError *retVal) 
{
	*retVal = OK;
    
    char buffer[MAX_LINE];
	int number;//, length;
    
    printf("Customer id (integer less than %d):\n>> ",MAX_CUSTOMERS);
    scanf("%d",&number);
    if(number>MAX_CUSTOMERS){
        *retVal = ERROR;
	} else {
		customer->id= (tCustomerId)(number);
	}
    getchar();
    
    printf("Customer name (max %d char, no spaces):\n>> ", MAX_NAME-1);
    scanf("%s",buffer);
    if (strlen(buffer)<MAX_NAME){
        strncpy(customer->name,buffer,MAX_NAME);
    } else {
		*retVal = ERROR;
	}
	getchar();
    
    printf("Customer surname (max %d char, no spaces):\n>> ", MAX_SURNAME-1);
    scanf("%s",buffer);
    if (strlen(buffer)<MAX_SURNAME){
        strncpy(customer->surname,buffer,MAX_SURNAME);
    } else {
		*retVal = ERROR;
	}
	getchar();
    
    printf("Customer Identity Document number (max %d char, no spaces, 8 digits and 1 letter):\n>> ", MAX_DOC_NUMBER-1);
    scanf("%s",buffer);
    if (strlen(buffer)<MAX_DOC_NUMBER){
        strncpy(customer->docNumber,buffer,MAX_DOC_NUMBER);
    } else {
		*retVal = ERROR;
	}
	getchar();

    printf("Customer birth date (day, in number):\n>> ");
    scanf("%d",&customer->birthDate.day);
    getchar();
    printf("Customer birth date (month, in number):\n>> ");
    scanf("%d",&customer->birthDate.month);
    getchar();
    printf("Customer birth date (year, in number):\n>> ");
    scanf("%d",&customer->birthDate.year);
    
    
    printf("Customer's city ​​of birth (max %d char, no spaces):\n>> ",MAX_CITY-1);
    scanf("%s",buffer);
    if (strlen(buffer)<MAX_DOC_NUMBER){
        strncpy(customer->birthCity,buffer,MAX_CITY);
    } else {
		*retVal = ERROR;
	}
	getchar();
    
    printf("Civil status (1 digit being 0=SINGLE, 1=MARRIED, 2=SEPARATED, 3=DIVORCED, 4=WIDOWED):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=4) {
		customer->status= (tCivilState)(number);
	} else {
		*retVal = ERROR;
	}
	getchar();
    
    printf("Customer profile (1 digit being 0=FAMILIAR, 1=CONSERVATIVE, 2=ADVENTUROUS, 3=LONELY, 4=CURIOUS, 5=INNOVATIVE, 6=DARED):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=6) {
		customer->profile= (tProfile)(number);
	} else {
		*retVal = ERROR;
	}
	getchar();
    
    customer->bookingsCounter=0;
    customer->points=0;
    customer->satisfaction=0;  
}

void readHotel(tHotel *hotel, tError *retVal) {	

	*retVal = OK;

	char buffer[MAX_LINE];
	int number, length;

	printf("Hotel id (integer less than %d):\n>> ",MAX_HOTELS);
	scanf("%d",&number);
	if(number>MAX_HOTELS) {
		*retVal = ERROR;
	} else {
		hotel->id= (tHotelId)(number);
	}
	getchar();
    
    printf("Hotel brand (max %d char, no spaces):\n>> ", MAX_BRAND-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_BRAND) {
		strncpy(hotel->brand,buffer,MAX_BRAND);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Hotel name (max %d char, no spaces):\n>> ", MAX_HOTEL_NAME-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_HOTEL_NAME) {
		strncpy(hotel->name,buffer,MAX_HOTEL_NAME);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Hotel nearest city (max %d char, no spaces):\n>> ", MAX_CITY-1);
    scanf("%s",buffer);
	length = strlen(buffer);
	if (length<MAX_CITY) {
		strncpy(hotel->city,buffer,MAX_CITY);
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Hotel category (i.e. number of stars, one digit):\n>> ");
	scanf("%d",&(hotel->category));
	getchar();

	printf("Hotel type (1 digit being 0=BUDGET 1=INN 2=RESORT 3=CONDO 4=LUXURY 5=COUNTRY):\n>> ");
	scanf("%d",&number);
	if(number>=0 && number <=5) {
		hotel->type= (tTypeHotel)(number);
	} else {
		*retVal = ERROR;
	}
	getchar();
	
	printf("Hotel number of rooms:\n>> ");
	scanf("%d",&(hotel->numRooms));
	getchar();
	
	printf("Hotel price for double rooms (in euros)\n>> ");
	scanf("%f",&(hotel->price));
	getchar();

	printf("Hotel distance to center of the nearest city (real value in meters):\n>> ");
	scanf("%f",&(hotel->distanceFromCityCenter));
	getchar();
	
	printf("Hotel has swimming pool? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		hotel->hasPool = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		hotel->hasPool = FALSE;
	} else {
		*retVal = ERROR;
	}
	getchar();

	printf("Hotel has gym? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		hotel->hasGym = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		hotel->hasGym = FALSE;
	} else {
		*retVal = ERROR;
	}
	getchar();
    
	printf("Hotel close to subway? (YES/NO):\n>> ");
	scanf("%s", buffer);
	if (strcmp(buffer,"YES") == 0 || strcmp(buffer,"yes") == 0) {
		hotel->closeToSubway = TRUE;
	} else if  (strcmp(buffer,"NO") == 0 || strcmp(buffer,"no") == 0) {
		hotel->closeToSubway = FALSE;
	} else {
		*retVal = ERROR;
	}
	getchar();
    
	printf("Hotel percentage of occupation (real number between 0 and 100)\n>> ");
	scanf("%f",&(hotel->percentOccupation));
	getchar();
}

void printHotel( tHotel hotel, int index ) 
{    
	char hotelStr[MAX_LINE];
    getHotelStr(hotel, MAX_LINE, hotelStr);
    printf("[%u] - %s\n", index, hotelStr);
}

void printHotelTable(tHotelTable table) {
    
  	int i;	
	
	if(table.nHotels==0) {
		printf("No hotels.\n");
	} else {
		for(i=0;i<table.nHotels;i++) {
            printHotel( table.table[i], i+1 );
		}		
	}
}

void printCustomer( tCustomer customer, int index ) 
{    
	char customerStr[MAX_LINE];
    getCustomerStr(customer, MAX_LINE, customerStr);
    printf("[%u] - %s\n", index, customerStr);
}

void printCustomerTable(tCustomerTable table) {
	int i;	
	
	if(table.nCustomers==0) {
		printf("No customers.\n");
	} else {
		for(i=0;i<table.nCustomers;i++) {
            printCustomer( table.table[i], i+1 );
		}		
	}
}

void allCustomersRecommendation(tAppData appData,
                                char *city, float price, float distance, int points) 
{
/*************** PR1 EX5B *****************/


	int i;
	int j;
	tAppData hotelsForCustomer;
	
	customerTable_selectCustomers(appData.customers,city,&hotelsForCustomer.customers);
	for(i=0;i<hotelsForCustomer.customers.nCustomers;i++){
		customerRecommendation(hotelsForCustomer.customers.table[i],appData.hotels,city,price,distance,points,&hotelsForCustomer.hotels);
		printf("RECOMMENDED HOTELS FOR CLIENT NUMBER: %d\n",i+1);
		printCustomer(hotelsForCustomer.customers.table[i],i+1);
		printf("THE LIST OF HOTELS FOR CUSTOMER: %d\n",i+1);
		for (j=0;j<hotelsForCustomer.hotels.nHotels;j++){
			printHotel(hotelsForCustomer.hotels.table[j],i+1);
		}
	}
}

/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Main Menu \n");
	printf("=======================\n");
	printf("1) Load data from file\n");
	printf("2) Save data to file\n");
	printf("3) Manage customers\n");
	printf("4) Manage hotels\n");
	printf("5) View statistics\n");
	printf("6) Exit\n");	
}

tMainMenuOptions getMainMenuOption() {
	/* Convert to the correct type */
	return (tMainMenuOptions)(getOption(6)-1);
}

void mainMenu(tAppData *appData) 
{
	tMainMenuOptions option;
	tError retVal;
		
	/* Assign the data path */
	appData_setPath(appData,"../");
		
	/* Start the menu */
    
    /* Show list of options and ask the user for an option */
    printMainMenuOptions();
    option=getMainMenuOption();
    
	while (option!=MAIN_MENU_EXIT) 
    {
		/* Do the action for the given option */
		if (option == MAIN_MENU_LOAD) {
			appData_load(appData,&retVal);
			if(retVal==OK) {
				printf("Data loaded\n");
			} else {	
				printf("No previous data loaded\n");
			}
		} else if (option == MAIN_MENU_SAVE) {
			appData_save(*appData,&retVal);
			if(retVal==OK) {
				printf("Data saved\n");
			} else {	
				printf("Cannot save the data\n");
			}
		} else if (option == MAIN_MENU_CUSTOMER) {
			customerMenu(appData);
		} else if (option == MAIN_MENU_HOTEL) {
			hotelMenu(appData);
		} else if (option == MAIN_MENU_STAT) {
			statMenu(*appData);
		} 
        
		/* Show list of options and ask the user for an option */
		printMainMenuOptions();
		option=getMainMenuOption();
	}
}

/*********************************
 **   CUSTOMER MANAGEMENT MENU **
*********************************/
void printCustomerMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Customers\n");
	printf("=======================\n");
	printf("1) List customers\n");	
	printf("2) Add customer\n");
	printf("3) Delete customer\n");	
	printf("4) Clear all customers\n");
	printf("5) Select urban customers in city\n");	
	printf("6) Get list of satisfied customers\n");	
	printf("7) Exit\n");	
}

tCustomerMenuOptions getCustomerMenuOption() {
	/* Convert to the correct type */
	return (tCustomerMenuOptions)(getOption(7)-1);
}

void customerMenu(tAppData *appData) {
	tCustomerMenuOptions option;
	tCustomer newCustomer;
	tCustomerTable customerTable,resultTable;
	char customerStr[MAX_LINE];
	char cityStr[MAX_LINE];
	int i, pos=0;
	tError retVal;
			
	/* Start the menu */
    /* Show list of options and ask the user for an option */
    printCustomerMenuOptions();
    option=getCustomerMenuOption();    
    
	while(option!=CUSTOMER_MENU_EXIT)
    {		
		/* Do the action for the given option */
		if (option == CUSTOMER_MENU_LIST ) {
			getCustomers(*appData, &customerTable);
			printCustomerTable(customerTable);
		} else if (option == CUSTOMER_MENU_ADD) {
			printf("Enter the information for the new customer:\n");
			readCustomer(&newCustomer,&retVal);
			getCustomerStr(newCustomer, MAX_LINE, customerStr);
			if(retVal==OK) {
				addCustomer(appData, newCustomer, &retVal);
				if(retVal==OK){
					printf("Customer added: %s\n", customerStr);
				} else if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("Duplicated customer not added: %s\n", customerStr);
				} else {
					printf("No more space. Customer not added: %s\n", customerStr);
				}
			} else {
				printf("Error in input. Customer not added: \n%s\n", customerStr);
			}
		} else if (option == CUSTOMER_MENU_DEL) {
			getCustomers(*appData, &customerTable);			
			/* Print the customers */			
			printCustomerTable(customerTable);		

			if (customerTable.nCustomers > 0) {
				/* Ask the number of the register to be removed */
				printf("Enter the number of the customer to delete:\n");
				pos=getOption(customerTable.nCustomers);
				/* Remove the selected customer */				
				removeCustomer(appData, customerTable.table[pos-1]);
			}
		} else if (option == CUSTOMER_MENU_CLEAR_ALL) {
			getCustomers(*appData, &customerTable);	
			for (i= 0; i< customerTable.nCustomers; i++) {
				/* Remove the customer */				
				removeCustomer(appData, customerTable.table[i]);
			}
		} else if (option == CUSTOMER_MENU_SELECT_URBAN_CUSTOMERS) {
            
			printf("City:\n");
			scanf("%s",cityStr);			
			getCustomers(*appData, &customerTable);
			customerTable_selectCustomers(customerTable,cityStr,&resultTable); 
			printCustomerTable(resultTable);
			
		} else if (option == CUSTOMER_MENU_SATISFIED_CUSTOMERS) {
            getCustomers(*appData, &customerTable);
			customerTable_selectSatisfiedCustomers(customerTable,&resultTable);
            printCustomerTable(resultTable);	
		}
        
        /* Show list of options and ask the user for an option */
        printCustomerMenuOptions();
        option=getCustomerMenuOption();        
	}
}

/********************************
 **   HOTEL MANAGEMENT MENU **
********************************/
void printHotelMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage hotels\n");
	printf("=======================\n");
	printf("1) List hotels\n");	
	printf("2) Add hotel\n");
	printf("3) List hotels by type\n");
	printf("4) List urban hotels\n");
    printf("5) List recommended hotels to customers\n");
	printf("6) Exit\n");	
}

tHotelMenuOptions getHotelMenuOption() {
	/* Convert to the correct type */
	return (tHotelMenuOptions)(getOption(6)-1);
}

void hotelMenu(tAppData *appData) {
	tError retVal = OK;
	tHotelMenuOptions option;
	tHotelTable hotelTable, typeTable, urbanTable;
	tHotel newHotel;
	char hotelStr[MAX_LINE];
	char cityStr[MAX_LINE];
	int type, points;
    float price, distance;
			
	/* Start the menu */
    /* Show list of options and ask the user for an option */
    printHotelMenuOptions();
    option=getHotelMenuOption();	
    
	while(option!=HOTEL_MENU_EXIT)
    {
		/* Do the action for the given option */
		if (option == HOTEL_MENU_LIST) {
			getHotels(*appData, &hotelTable);
			printHotelTable(hotelTable);
		} else if (option == HOTEL_MENU_ADD) {
			readHotel(&newHotel,&retVal);
			getHotelStr(newHotel, MAX_LINE, hotelStr);
			if(retVal==OK) {
				addHotel(appData, newHotel, &retVal);
				if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("ERROR: A hotel with the same ID already exists\n");
				} else {
					printf("Hotel added: %s\n", hotelStr);
				}
			} else {
				printf("Error in input. Hotel not added: \n%s\n", hotelStr);
			}
		} else if (option == HOTEL_MENU_TYPE) {
			getHotels(*appData, &hotelTable);
			printf("Hotel type (1 digit being 0=BUDGET 1=INN 2=RESORT 3=CONDO 4=LUXURY 5=COUNTRY):\n");
			scanf("%d",&type);
			hotelTable_filterByType(hotelTable, (tTypeHotel)type, &typeTable);
			printHotelTable(typeTable);
		} else if (option == HOTEL_MENU_URBAN_HOTELS) {
			getHotels(*appData, &hotelTable);
			hotelTable_getUrbanHotels(hotelTable, &urbanTable);
			printHotelTable(urbanTable);
		} else if (option == HOTEL_CUSTOMERS_RECOMMENDATION) { 
			printf("Search in city:\n");
			scanf("%s",cityStr);			
			printf("Objective price:\n");
			scanf("%f",&price);	
			printf("Desired distance:\n");
			scanf("%f",&distance);			
			printf("Minimum points:\n");
			scanf("%d",&points);			
            allCustomersRecommendation(*appData, cityStr, price, distance, points);
        }
        
		/* Show list of options and ask the user for an option */
		printHotelMenuOptions();
		option=getHotelMenuOption();
    }
}

/******************
 **   STAT MENU **
******************/
void printStatMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Stats \n");
	printf("=======================\n");
	printf("1) Get average points per booking\n");	
	printf("2) Get max satisfaction per year interval\n");	
	printf("3) Get average hotel occupation for a hotel of a city\n");	
	printf("4) Get maximum hotel room price\n");	
	printf("5) Exit\n");	
}

tStatMenuOptions getStatMenuOption() {
	/* Convert to the correct type */
	return (tStatMenuOptions)(getOption(5)-1);
}

void statMenu(tAppData appData) 
{
	tStatMenuOptions option;
	tCustomerTable customerTable;
	tHotelTable hotelTable;
	char hotelStr[MAX_LINE];
    float avg, upto29, between30and44, between45and59, from60;
	
	/* Start the menu */
    /* Show list of options and ask the user for an option */
    printStatMenuOptions();
    option=getStatMenuOption();
    
	while(option!=STAT_MENU_EXIT)
    {
		/* Do the action for the given option */
		if (option == STAT_MENU_NUM_AVG_POINTS_PER_BOOKING) {			
			getCustomers(appData, &customerTable);
			avg= customerTable_getAvgPointsPerBooking(customerTable);
            printf("Average points per booking: %.2f\n", avg);

		} else if (option == STAT_MENU_MAX_SATISFACTION_PER_AGE_INTERVAL) {
			getCustomers(appData, &customerTable);
			customerTable_getMaxSatisfactionPerAgeInterval(customerTable, 
                        &upto29, &between30and44, &between45and59, &from60);     
            printf("Max satisfaction for age interval up to 29 years old: %.2f\n", upto29);
            printf("Max satisfaction for ages in [30,44]: %.2f\n", between30and44);
            printf("Max satisfaction for ages in [45,59]: %.2f\n", between45and59);
            printf("Max satisfaction for from 60 years old: %.2f\n", from60);
		
		} else if (option == STAT_MENU_AVG_OCCUPATION) {
            getHotels(appData, &hotelTable);
            printf("Hotel nearest city (max %d char, no spaces):\n>> ", MAX_CITY-1);
            scanf("%s",hotelStr);
            printf("Average occupation of hotels in %s is %.2f %%\n", 
                   hotelStr, hotelTable_computeAverageOccupation(hotelTable,hotelStr));
		} else if (option == STAT_MENU_MAX_ROOM_PRICE) {
			getHotels(appData, &hotelTable);
			printf("Maximum hotel room price: %.2f euros\n", hotelTable_getMaxRoomPrice(hotelTable));
		} 

        /* Show list of options and ask the user for an option */
        printStatMenuOptions();
        option=getStatMenuOption();
    }
}
