#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "customer.h"
#include "hotel.h"

#define CUSTOMER1 "10 LUISA MARTINEZ 38908321Y 1990 7 15 BARCELONA 0 3 25 100 90.00"    
#define CUSTOMER2 "20 JOHN DOE 44451217G 1976 3 14 LONDON 1 6 25 100 80.00"
#define CUSTOMER3 "30 PETER WILLIAMS 41072140T 1965 2 28 DUBLIN 3 0 10 50 70.00"
#define CUSTOMER4 "40 JUSTINE LECLERC 23169220R 1959 8 20 PARIS 2 1 30 20 85.00"
#define CUSTOMER5 "50 JUSTINE LEBLANC 23169221R 1988 4 22 CANNES 0 5 9 9 90.00"

#define HOTEL1 "1 IBIS RAVAL BARCELONA 2 0 50 50.00 7.00 0 0 1 95.00"
#define HOTEL2 "2 HILTON DIAGONAL BARCELONA 5 4 100 400.0 1.0 1 1 1 75.00"
#define HOTEL3 "3 PRESTIGE RECOLETOS MADRID 5 4 200 300.0 2.0 1 0 1 90.00"
    
void runTests() {	
	int passedTestPR1, passedTestPR2=0;
	int totalTestPR1, totalTestPR2=0;
	
	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 1 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR1(&totalTestPR1, &passedTestPR1);

	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");		
	printf("\tPR1: Passed %d of %d [%0.2f%%]\n", passedTestPR1, totalTestPR1, (float)passedTestPR1/totalTestPR1*100.0);
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR1+passedTestPR2, totalTestPR1+totalTestPR2, (float)(passedTestPR1+passedTestPR2)/(totalTestPR1+totalTestPR2)*100.0);
	printf("===================================\n");		
}

void runTestsPR1(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
	
	test_cpycmp(totalTest, passedTest);
	test_selection(totalTest, passedTest);
    test_filter_combination(totalTest, passedTest);
    test_statistics(totalTest, passedTest);
    test_table_operation(totalTest, passedTest);
}

void test_cpycmp(int *totalTest, int *passedTest) {	

	tCustomer d1, d2, d4, d5;

	printf("==================================\n");
	printf(" CUSTOMERS COMPARISON (Exercise 3)\n");
	printf("==================================\n");
	
	printf("\nTest 3.1: Compare equal customers");
	(*totalTest)++;
	getCustomerObject(CUSTOMER1, &d1);
    if (customer_cmp(d1,d1)==0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 3.2: Comparison, first customer greater than first");
	(*totalTest)++;
	getCustomerObject(CUSTOMER4, &d4);
	getCustomerObject(CUSTOMER5, &d5);
    if (customer_cmp(d4,d5)>0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.3: Comparison, second customer lower than second");
	(*totalTest)++;
    if (customer_cmp(d5,d4)<0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 3.4: Compare case-unsensitive strings");
	(*totalTest)++;
	customer_cpy(&d2,d1);
    /* Uncomment to test*/
    strcpy(d2.name, "Luisa");
    strcpy(d2.surname, "Martinez");
    strcpy(d2.docNumber, "38908321y");
    strcpy(d2.birthCity, "Barcelona");
    
    if (customer_cmp(d1,d2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}    
}	

void test_selection(int *totalTest, int *passedTest) {	
	tCustomerTable customers, result;
	tCustomer customer1, customer2, customer3, customer4, customer5;	
	tError retVal;
		
	printf("=================================================\n");
	printf(" CUSTOMER SELECTION (Exercise 4)\n");
	printf("=================================================\n");

	printf("\nTest 4.1: Select customers on an empty table");
	(*totalTest)++;
	customerTable_init(&customers);	
	customerTable_init(&result);

    customerTable_selectCustomers(customers, "BARCELONA", &result);
	if(result.nCustomers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nCustomers);
	}

	getCustomerObject(CUSTOMER1, &customer1);
	getCustomerObject(CUSTOMER2, &customer2);
    getCustomerObject(CUSTOMER3, &customer3);
    getCustomerObject(CUSTOMER4, &customer4);
    customerTable_add(&customers,customer1,&retVal);
    customerTable_add(&customers,customer2,&retVal);
    customerTable_add(&customers,customer3,&retVal);
    customerTable_add(&customers,customer4,&retVal);

	printf("\nTest 4.2: Customers from coincident city in non empty table");
	(*totalTest)++;	
    customerTable_selectCustomers(customers, "BARCELONA", &result);
	if(result.nCustomers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nCustomers);
	}

    getCustomerObject(CUSTOMER5, &customer5);
    customerTable_add(&customers,customer5,&retVal);	

	printf("\nTest 4.3: Customers from a non coincident city in non empty table");
	(*totalTest)++;	
    customerTable_selectCustomers(customers, "MADRID", &result);;
	if(result.nCustomers==2) {
		if((customer_cmp(result.table[0], customer1)!=0) ||
           (customer_cmp(result.table[1], customer5)!=0))  {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.nCustomers);
	}

	printf("\nTest 4.4: Selection criteria: year of birth");
	(*totalTest)++;
    /* Uncomment to test*/
    customers.table[0].birthDate.year= 1980;
	
	customerTable_init(&result);	
    customerTable_selectCustomers(customers, "MADRID", &result);;
	if(result.nCustomers==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 1, result.nCustomers);
	}
	
	printf("\nTest 4.5: Selection criteria: civil state");
	(*totalTest)++;
    /* Uncomment to test*/
    customers.table[4].status= MARRIED;
	
	customerTable_init(&result);	
    customerTable_selectCustomers(customers, "MADRID", &result);;
	if(result.nCustomers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nCustomers);
	}
	
	printf("\nTest 4.6: Selection criteria: profile");
	(*totalTest)++;
    /* Uncomment to test*/
    customers.table[4].status= SINGLE;
    customers.table[4].profile= ADVENTUROUS;
     
    customerTable_selectCustomers(customers, "MADRID", &result);;
	if(result.nCustomers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nCustomers);
	}
    
	printf("\nTest 4.7: Selection of satisfied customers (check satisfaction index)");
	(*totalTest)++;
    customerTable_selectSatisfiedCustomers(customers, &result);
	if(result.nCustomers==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 1, result.nCustomers);
	}    

	printf("\nTest 4.8: Selection of satisfied customers (check number of bookings)");
	(*totalTest)++;
    /* Uncomment to test*/
    customers.table[4].bookingsCounter++;
    
    customerTable_selectSatisfiedCustomers(customers, &result);
	if(result.nCustomers==2) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.nCustomers);
	}    
}

void test_filter_combination(int *totalTest, int *passedTest) 
{
    tCustomer customer1, customer2, customer3, customer4;
    tHotel hotel1, hotel2, hotel3;
    tCustomerTable customers;
    tHotelTable hotels;
    tHotelTable result;
	tError retVal;
    
	getCustomerObject(CUSTOMER1, &customer1);
	getCustomerObject(CUSTOMER2, &customer2);
    getCustomerObject(CUSTOMER3, &customer3);
    getCustomerObject(CUSTOMER4, &customer4);
    customerTable_init(&customers);    
    customerTable_add(&customers,customer1,&retVal);
    customerTable_add(&customers,customer2,&retVal);
    customerTable_add(&customers,customer3,&retVal);
    customerTable_add(&customers,customer4,&retVal);
    
    getHotelObject(HOTEL1, &hotel1);
    getHotelObject(HOTEL2, &hotel2);
    getHotelObject(HOTEL3, &hotel3);
    hotelTable_init(&hotels);
    hotelTable_add(&hotels,hotel1,&retVal);
    hotelTable_add(&hotels,hotel2,&retVal);
    hotelTable_add(&hotels,hotel3,&retVal);
    
	printf("=================================================\n");
	printf(" FILTER COMBINATION (Exercise 5)\n");
	printf("=================================================\n");
                            
	printf("\nTest 5.1: Customer recommendation: no match (one hotel in the same customer city");
	(*totalTest)++;
	customerRecommendation(customer1,hotels,"BARCELONA",250.0,5.0,40,&result);
	if (result.nHotels==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, result.nHotels);
	}

	printf("\nTest 5.2: Customer recommendation: match (one hotel in a different city than customer's)");
	(*totalTest)++;
	customerRecommendation(customer1,hotels,"MADRID",250.0,5.0,40,&result);
	if (result.nHotels==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, result.nHotels);
	}
    
	printf("\nTest 5.3: Customer recommendation: match (searhing hotels in the same customers city)");
	(*totalTest)++;
	customerRecommendation(customer2,hotels,"BARCELONA",250.0,5.0,40,&result);
	if (result.nHotels==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, result.nHotels);
	}
    
	printf("\nTest 5.4: Customer recommendation: match (relax point criteria)");
	(*totalTest)++;
	customerRecommendation(customer2,hotels,"BARCELONA",250.0,5.0,30,&result);
	if (result.nHotels==2) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 1, result.nHotels);
	}
}
	
void test_statistics(int *totalTest, int *passedTest) 
{
    float avg,upto29,between30and44,between45and59,from60;
    tCustomer customer1, customer2, customer3, customer4, customer5;
    tCustomerTable customers;
	tError retVal;

	getCustomerObject(CUSTOMER1, &customer1);
	getCustomerObject(CUSTOMER2, &customer2);
    getCustomerObject(CUSTOMER3, &customer3);
    getCustomerObject(CUSTOMER4, &customer4);
    getCustomerObject(CUSTOMER5, &customer5);
    customerTable_init(&customers);    
    
	printf("=================================================\n");
	printf(" STATISTICS (Exercise 6)\n");
	printf("=================================================\n");
                            
	printf("\nTest 6.1: Average of an empty table");
	(*totalTest)++;
    avg= customerTable_getAvgPointsPerBooking(customers);
	if (avg==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 0.0, avg);
	}
    
    customerTable_add(&customers,customer1,&retVal);
	printf("\nTest 6.2: Average of a single element");
	(*totalTest)++;
    avg= customerTable_getAvgPointsPerBooking(customers);
	if (avg==4.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 4.0, avg);
	}
    
    customerTable_add(&customers,customer2,&retVal);
    customerTable_add(&customers,customer3,&retVal);
    customerTable_add(&customers,customer4,&retVal);
    
	printf("\nTest 6.3: Average of several elements");
	(*totalTest)++;
    avg= customerTable_getAvgPointsPerBooking(customers);
	if (avg==3.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number average result. Expected %.2f and returned %.2f)\n", 3.0, avg);
	}
    
    customerTable_init(&customers); 

	printf("\nTest 6.4: Max satisfaction index of an empty table");
	(*totalTest)++;
    customerTable_getMaxSatisfactionPerAgeInterval(customers,&upto29,&between30and44,&between45and59,&from60);    
	if (upto29==0.0 && between30and44==0.0 && between45and59==0.0 && from60==0.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected results. Expected zero values and returned non-zero values)\n");
	}
    
    customerTable_add( &customers,customer1,&retVal );
    customerTable_add( &customers,customer2,&retVal );
    customerTable_add( &customers,customer3,&retVal );
    customerTable_add( &customers,customer4,&retVal );

	printf("\nTest 6.5: Max satisfaction index of an non-empty table (one customer per range)");
	(*totalTest)++;
    customerTable_getMaxSatisfactionPerAgeInterval(customers,&upto29,&between30and44,&between45and59,&from60);  
	if (upto29==90.0 && between30and44==80.0 && between45and59==70.0 && from60==85.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected results)\n");
	}

    customerTable_add( &customers,customer5,&retVal );

	printf("\nTest 6.6: Max satisfaction index of an non-empty table (several customers per range)");
	(*totalTest)++;
    customerTable_getMaxSatisfactionPerAgeInterval(customers,&upto29,&between30and44,&between45and59,&from60);  
	if (upto29==90.0 && between30and44==90.0 && between45and59==70.0 && from60==85.0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected results)\n");
	}
}

void test_table_operation(int *totalTest, int *passedTest) 
{
    tCustomer customer1, customer2, customer3, customer4, customer5;
    tCustomerTable customers;
	tError retVal;

    customerTable_init(&customers);    
	getCustomerObject(CUSTOMER1, &customer1);
	getCustomerObject(CUSTOMER2, &customer2);
    getCustomerObject(CUSTOMER3, &customer3);
    getCustomerObject(CUSTOMER4, &customer4);
    getCustomerObject(CUSTOMER5, &customer5);

	printf("=================================================\n");
	printf(" TABLE OPERATIONS (Exercise 7)\n");
	printf("=================================================\n");
                            
	printf("\nTest 7.1: Deletion in empty table");
	(*totalTest)++;
    customerTable_del( &customers,customer1 );
	if (customers.nCustomers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected behaviour in deletion\n");
	}
    
    customerTable_add( &customers,customer1,&retVal );
    
	printf("\nTest 7.2: Deletion of non-existing customer in non-empty table");
	(*totalTest)++;
    customerTable_del( &customers,customer2 );
	if (customers.nCustomers==1) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected behaviour in deletion\n");
	}
    
	printf("\nTest 7.3: Deletion of existing customer in non-empty table (no gap)");
	(*totalTest)++;
    customerTable_del( &customers,customer1 );
	if (customers.nCustomers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected behaviour in deletion\n");
	}

    customerTable_add( &customers,customer1,&retVal );
    customerTable_add( &customers,customer2,&retVal );
    customerTable_add( &customers,customer3,&retVal );

	printf("\nTest 7.4: Deletion requires customers displacement to fill the gap");
	(*totalTest)++;
    customerTable_del( &customers,customer1 );
	if (customers.nCustomers==2 && 
        customers.table[0].id == 20 &&
        customers.table[1].id == 30) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected behaviour in deletion\n");
	}
}
