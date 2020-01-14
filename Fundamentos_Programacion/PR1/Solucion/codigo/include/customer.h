#include "data.h"

/* Get a textual representation of a customer */
void getCustomerStr(tCustomer customer, int maxSize, char *str);
	
/* Get a customer object from its textual representation */
void getCustomerObject(const char *str, tCustomer *customer);

/* Compare two dates */
int date_cmp( tDate d1, tDate d2 );

/* Compares two strings in uppercase */
int strcmpUpper( char *s1, char *s2 );

/* Compare two customers */
int customer_cmp(tCustomer customer1, tCustomer customer2);

/* Copy the customer data in src to dst*/
void customer_cpy(tCustomer *dst, tCustomer src);

/* Initialize the table of customers */
void customerTable_init(tCustomerTable *table);

/* Add a new customer to the table of customers */
void customerTable_add(tCustomerTable *table, tCustomer customer, tError *retVal);

/* Find a customer in the table and returns its position */
int customerTable_find(tCustomerTable table, tCustomerId id);

/* Remove the first occurence of a customer in the table */
void customerTable_del(tCustomerTable *table, tCustomer customer);

/* Load the table of customers from a file */
void customerTable_load(tCustomerTable *table, const char* filename, tError *retVal);

/* Save a table of customers to a file */
void customerTable_save(tCustomerTable table, const char* filename, tError *retVal);

/* Selects urban customers for a given city */
void customerTable_selectCustomers(tCustomerTable customers, char *city, tCustomerTable *result);

/* Selects satisfied customers */
void customerTable_selectSatisfiedCustomers(tCustomerTable customers, tCustomerTable *result);

/* Calculates the average points obtained per booking */
float customerTable_getAvgPointsPerBooking(tCustomerTable tabCustomer);

/* Calculates the maximum satisfaction percentage per age interval */
void customerTable_getMaxSatisfactionPerAgeInterval(tCustomerTable tabCustomer,
     float *upto29, float *between30and44, float *between45and59, float *from60);