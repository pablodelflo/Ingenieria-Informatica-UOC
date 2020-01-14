#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
int getOption(int numOptions);

/* Define the main menu options type */
typedef enum {MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_CUSTOMER, 
                MAIN_MENU_HOTEL, MAIN_MENU_STAT,
                MAIN_MENU_EXIT} tMainMenuOptions;

/* Define the customers management menu options type */
typedef enum {CUSTOMER_MENU_LIST, CUSTOMER_MENU_ADD, CUSTOMER_MENU_DEL, 
                CUSTOMER_MENU_CLEAR_ALL, CUSTOMER_MENU_SELECT_URBAN_CUSTOMERS,
                CUSTOMER_MENU_SATISFIED_CUSTOMERS,
                CUSTOMER_MENU_EXIT} tCustomerMenuOptions;

/* Define the hotels management menu options type */
typedef enum {HOTEL_MENU_LIST, HOTEL_MENU_ADD, HOTEL_MENU_TYPE, HOTEL_MENU_URBAN_HOTELS,
                HOTEL_CUSTOMERS_RECOMMENDATION,
                HOTEL_MENU_EXIT} tHotelMenuOptions;

/* Define the stats menu options type */
typedef enum {STAT_MENU_NUM_AVG_POINTS_PER_BOOKING, STAT_MENU_MAX_SATISFACTION_PER_AGE_INTERVAL,
                STAT_MENU_AVG_OCCUPATION, STAT_MENU_MAX_ROOM_PRICE,
                STAT_MENU_EXIT} tStatMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the customer management menu options */
void printCustomerMenuOptions();

/* Get the option for the customer management menu */
tCustomerMenuOptions getCustomerMenuOption();

/* Perform the actions for the customer management menu */
void customerMenu(tAppData *appData);

/* Print the hotels management menu options */
void printHotelMenuOptions();

/* Get the option for the hotels management menu */
tHotelMenuOptions getHotelMenuOption();

/* Perform the actions for the hotels management menu */
void hotelMenu(tAppData *appData);

/* Print the stats menu options */
void printStatMenuOptions();

/* Get the option for the status menu */
tStatMenuOptions getStatMenuOption();

/* Perform the actions for the status menu */
void statMenu(tAppData appData);

/* Prints recommended hotels for each customer. Hotels are based in the specified city
 * and have a desired price, distante to center and points. */
void allCustomersRecommendation(tAppData appData,
                                char *city, float price, float distance, int points);