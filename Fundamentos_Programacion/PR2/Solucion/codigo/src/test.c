#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "movement.h"
#include "customer.h"
#include "hotel.h"
#include "list.h"
#include "queue.h"
#include "api.h"

#define CUSTOMER1 "10 LUISA MARTINEZ 38908321Y 1990 7 15 BARCELONA 0 3 25 100 90.00"    
#define CUSTOMER2 "20 JOHN DOE 44451217G 1976 3 14 LONDON 1 6 25 100 80.00"
#define CUSTOMER3 "30 PETER WILLIAMS 41072140T 1965 2 28 DUBLIN 3 0 10 50 70.00"
#define CUSTOMER4 "40 JUSTINE LECLERC 23169220R 1959 8 20 PARIS 2 1 30 20 85.00"
#define CUSTOMER5 "50 JUSTINE LEBLANC 23169221R 1988 4 22 CANNES 0 5 9 9 90.00"

#define HOTEL1 "1 IBIS RAVAL BARCELONA 2 0 40 50.00 7.00 0 0 1 95.00"
#define HOTEL2 "2 HILTON DIAGONAL BARCELONA 5 4 40 400.0 1.0 1 1 1 75.00"
#define HOTEL3 "3 PRESTIGE RECOLETOS MADRID 5 4 40 300.0 2.0 1 0 1 90.00"

#define MOVEMENT1 "1 10 11 2019"
#define BOOKINGS1 "3 10 4 10 11 2019 20 11 2019 1 0.00 0 0 0 0 0 20 3 10 11 2019 24 11 2019 2 0.00 0 0 0 0 0 30 2 10 11 2019 15 11 2019 3 0.00 0 0 0 0 0"
#define BOOKINGS2 "1 40 3 25 10 2019 10 11 2019 0 0.00 1 301 0 0 0"
#define BOOKINGS3 "1 50 3 25 10 2019 9 11 2019 0 70.00 1 302 0 0 0"
#define QUEUE1 "3 10 20 30"
#define QUEUE2 "1 40"

void runTests() {	
	int passedTestPR1= 0, passedTestPR2=0;
	int totalTestPR1= 0, totalTestPR2=0;
    float ratioPR1= 0.0, ratioPR2= 0.0, ratioPR= 0.0;
	
	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 1 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR1(&totalTestPR1, &passedTestPR1);
    if (totalTestPR1 > 0) {
        ratioPR1= (float)passedTestPR1/totalTestPR1*100.0;
	}
	
	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 2 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR2(&totalTestPR2, &passedTestPR2);
    if (totalTestPR2 > 0) {
        ratioPR2= (float)passedTestPR2/totalTestPR2*100.0;
	}
	
    if (totalTestPR1 + totalTestPR2 > 0) {
        ratioPR= (float)(passedTestPR1+passedTestPR2)/(totalTestPR1+totalTestPR2)*100.0;
	}
	
	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");
	printf("\tPR1: Passed %d of %d [%0.2f%%]\n", passedTestPR1, totalTestPR1, ratioPR1);
	printf("\tPR2: Passed %d of %d [%0.2f%%]\n", passedTestPR2, totalTestPR2, ratioPR2);
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR1+passedTestPR2, totalTestPR1+totalTestPR2, ratioPR);
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

void runTestsPR2(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
    
    test_movements_checkin(totalTest, passedTest);
    test_movements_checkout(totalTest, passedTest);
}

void test_movements_checkin(int *totalTest, int *passedTest) 
{ 
    int hotelIndex, prevOccupiedRooms, postOccupiedRooms, nAssignedRooms;
    int bookingIndex10, bookingIndex20, bookingIndex30, bookingIndex40;
    int prevPendingBookings, postPendingBookings;
    int prevCurrentBookings, postCurrentBookings;
    tAppData appData;
    tMovement movement;
    tCustomer customer;
    boolean equals;
    tHotel hotel;
    tError retVal;
    tDate date;
    
    appData_init(&appData);
    
    /* add hotels */
    getHotelObject(HOTEL1, &hotel);
    hotelTable_add(&appData.hotels, hotel, &retVal);		
    getHotelObject(HOTEL2, &hotel);
    hotelTable_add(&appData.hotels, hotel, &retVal);		
    getHotelObject(HOTEL3, &hotel);
    hotelTable_add(&appData.hotels, hotel, &retVal);		

    /* add customers */
    getCustomerObject(CUSTOMER1, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		
    getCustomerObject(CUSTOMER2, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		
    getCustomerObject(CUSTOMER3, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		
    getCustomerObject(CUSTOMER4, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		
    getCustomerObject(CUSTOMER5, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		

    /* add a movement */
    getMovementObject(MOVEMENT1, &movement);
    getBookingObject(BOOKINGS1,&movement.pendingBookings);
    getBookingObject(BOOKINGS2,&movement.currentBookings);
    getBookingObject(BOOKINGS3,&movement.completedBookings);
    movementTable_add(&appData.movements, movement, &retVal);

    /* update hotel occupation */
    hotelIndex= hotelTable_find(appData.hotels,movement.id);
    updateHotelOccupation( &appData.hotels.table[hotelIndex], movement.currentBookings );
    
	printf("==================================\n");
	printf(" CHECK-IN PROCESS\n");
	printf("==================================\n");

	printf("\nTest 1.1: Find customer booking (existing customers)");
	(*totalTest)++;
    bookingIndex10= findCustomerBooking(movement.pendingBookings, 10);
    bookingIndex20= findCustomerBooking(movement.pendingBookings, 20);
    bookingIndex30= findCustomerBooking(movement.pendingBookings, 30);
    if (bookingIndex10 == 1 && 
        bookingIndex20 == 2 && 
        bookingIndex30 == 3) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Incorrect index for existing customers)\n");
	}

	printf("\nTest 1.2: Find customer booking (non-existing customers)");
	(*totalTest)++;
    bookingIndex40= findCustomerBooking(movement.pendingBookings, 40);
    if (bookingIndex40 == NO_BOOKING) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Incorrect index for existing customers)\n");
	}

	printf("\nTest 1.3: Empty checkin queue");
	(*totalTest)++;
    date.day= 9; date.month= 11; date.year= 2019; 
    processCheckins( &appData.hotels.table[hotelIndex], appData.customers, date, 
                     &appData.movements.table[0].checkinQueue,
                     &appData.movements.table[0].pendingBookings, 
                     &appData.movements.table[0].currentBookings );
    equals= (movement_cmp( movement, appData.movements.table[0] ) == 0);
    if (equals){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (no changes expected caused by an empty checkin queue)\n");
	}

	printf("\nTest 1.4: Checkin queue non-empty. Customers with incorrect checkin date");
	(*totalTest)++;
    prevOccupiedRooms= appData.hotels.table[hotelIndex].occupiedRooms;
    prevPendingBookings= bookingList_length(appData.movements.table[0].pendingBookings);
    prevCurrentBookings= bookingList_length(appData.movements.table[0].currentBookings);
    getCustomerQueueObject(QUEUE1,&appData.movements.table[0].checkinQueue);
    processCheckins( &appData.hotels.table[hotelIndex], appData.customers, date, 
                     &appData.movements.table[0].checkinQueue,
                     &appData.movements.table[0].pendingBookings, 
                     &appData.movements.table[0].currentBookings);
    postOccupiedRooms= appData.hotels.table[hotelIndex].occupiedRooms;
    postPendingBookings= bookingList_length(appData.movements.table[0].pendingBookings);
    postCurrentBookings= bookingList_length(appData.movements.table[0].currentBookings);
    if (prevOccupiedRooms == postOccupiedRooms && 
        customerQueue_empty(appData.movements.table[0].checkinQueue) && 
        prevPendingBookings == postPendingBookings && 
        prevCurrentBookings == postCurrentBookings) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (no checkin should be effective since date does not match)\n");
	}

	printf("\nTest 1.5: Checkin queue non-empty. Customers with correct checkin date");
	(*totalTest)++;
    date.day= 10; date.month= 11; date.year= 2019; 
    prevOccupiedRooms= appData.hotels.table[hotelIndex].occupiedRooms;
    prevPendingBookings= bookingList_length(appData.movements.table[0].pendingBookings);
    prevCurrentBookings= bookingList_length(appData.movements.table[0].currentBookings);
    getCustomerQueueObject(QUEUE1,&appData.movements.table[0].checkinQueue);
    processCheckins( &appData.hotels.table[hotelIndex], appData.customers, date, 
                     &appData.movements.table[0].checkinQueue,
                     &appData.movements.table[0].pendingBookings, 
                     &appData.movements.table[0].currentBookings);
    postOccupiedRooms= appData.hotels.table[hotelIndex].occupiedRooms;
    postPendingBookings= bookingList_length(appData.movements.table[0].pendingBookings);
    postCurrentBookings= bookingList_length(appData.movements.table[0].currentBookings);
    if (prevOccupiedRooms < postOccupiedRooms && 
        customerQueue_empty(appData.movements.table[0].checkinQueue)) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (No checkins processed)\n");
	}
    
	printf("\nTest 1.6: Checkin queue non-empty. Correct date. Bookings list management");
	(*totalTest)++;
    if (prevPendingBookings == postPendingBookings+3 && 
        prevCurrentBookings == postCurrentBookings-3) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (3 checkins should have been processed on the current date)\n");
	}    
    
	printf("\nTest 1.7: Current bookings properly processed");    
	(*totalTest)++;
    bookingIndex10= findCustomerBooking(appData.movements.table[0].currentBookings, 10);
    if (bookingIndex10 != NO_CUSTOMER)
        nAssignedRooms= appData.movements.table[0].currentBookings.table[bookingIndex10-1].nAssignedRooms;
    else
        nAssignedRooms= 0;
    if (nAssignedRooms == 1 && 
        appData.movements.table[0].currentBookings.table[bookingIndex10-1].assignedRooms[nAssignedRooms-1] == 401) 
    {
        printf("\n\t-> OK\n");
        (*passedTest)++;                
    }
    else {
		printf("\n\t-> FAIL (No rooms assigned to current booking)\n");
    }
}

void test_movements_checkout(int *totalTest, int *passedTest) 
{ 
    int hotelIndex, bookingIndex40, nAssignedRooms; 
    int prevOccupiedRooms, postOccupiedRooms;
    int prevCompletedBookings, postCompletedBookings;
    int prevCurrentBookings, postCurrentBookings;
    tAppData appData;
    tMovement movement;
    tCustomer customer;
    tBooking booking;
    boolean equals;
    tHotel hotel;
    tError retVal;
    tDate date;
    float price;
    
    appData_init(&appData);
    
    /* add hotels */
    getHotelObject(HOTEL1, &hotel);
    hotelTable_add(&appData.hotels, hotel, &retVal);		
    getHotelObject(HOTEL2, &hotel);
    hotelTable_add(&appData.hotels, hotel, &retVal);		
    getHotelObject(HOTEL3, &hotel);
    hotelTable_add(&appData.hotels, hotel, &retVal);		

    /* add customers */
    getCustomerObject(CUSTOMER1, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		
    getCustomerObject(CUSTOMER2, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		
    getCustomerObject(CUSTOMER3, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		
    getCustomerObject(CUSTOMER4, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		
    getCustomerObject(CUSTOMER5, &customer);
    customerTable_add(&appData.customers, customer, &retVal);		

    /* add a movement */
    getMovementObject(MOVEMENT1, &movement);
    getBookingObject(BOOKINGS1,&movement.pendingBookings);
    getBookingObject(BOOKINGS2,&movement.currentBookings);
    getBookingObject(BOOKINGS3,&movement.completedBookings);
    movementTable_add(&appData.movements, movement, &retVal);

    /* update hotel occupation */
    hotelIndex= hotelTable_find(appData.hotels,movement.id);
    updateHotelOccupation( &appData.hotels.table[hotelIndex], movement.currentBookings );
    date.day= 10; date.month= 11; date.year= 2019; 
    
	printf("==================================\n");
	printf(" CHECK-OUT PROCESS\n");
	printf("==================================\n");

	printf("\nTest 2.1: Calculate price for TRIPLE room, 3 customers in ROOM_ONLY regime. Checkout on date.");
	(*totalTest)++;
    booking_cpy(&booking, movement.currentBookings.table[0]);
    booking.regime= ROOM_ONLY;
    booking.nGuests= 3;
    date_cpy( &booking.checkOutDate, date );
    price= calculatePrice(appData.hotels.table[hotelIndex], booking, date);
    if (price == 1200.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
        printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",1200.0, price);
	}

	printf("\nTest 2.2: Calculate price for TRIPLE room, 3 customers in ROOM_AND_BREAKFAST regime. Checkout on date.");
	(*totalTest)++;
    booking.regime= ROOM_AND_BREAKFAST;
    price= calculatePrice(appData.hotels.table[hotelIndex], booking, date);
    if (price == 1680.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
        printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",1680.0, price);
	}

	printf("\nTest 2.3: Calculate price for QUAD room, 3 customers in HALF_BOARD regime. Checkout on date.");
	(*totalTest)++;
    booking.assignedRooms[0]= 401;
    booking.regime= HALF_BOARD;
    price= calculatePrice(appData.hotels.table[hotelIndex], booking, date);
    if (price == 2600.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
        printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",2600.0, price);
	}

	printf("\nTest 2.4: Calculate price for QUAD room, 3 customers in FULL_BOARD regime. Late Checkout.");
	(*totalTest)++;
    booking.regime= FULL_BOARD;
    date.day= 11;
    price= calculatePrice(appData.hotels.table[hotelIndex], booking, date);
    if (price == 4233.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",4233.0, price);
	}

	printf("\nTest 2.5: Calculate price for two DOUBLE rooms, 4 customers in FULL_BOARD regime. Late Checkout.");
	(*totalTest)++;
    booking.nGuests= 4;
    booking.assignedRooms[0]= 201;
    booking.assignedRooms[1]= 202;
    booking.nAssignedRooms= 2;
    booking.regime= FULL_BOARD;
    price= calculatePrice(appData.hotels.table[hotelIndex], booking, date);
    if (price == 5304.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",5304.0, price);
	}

	printf("\nTest 2.6: Calculate price for one SINGLE and one DOUBLE room, 3 customers in FULL_BOARD regime. Checkout on date.");
	(*totalTest)++;
    date.day= 10;
    booking.checkOutDate.day= 10;
    booking.nGuests= 3;
    booking.assignedRooms[0]= 101;
    booking.assignedRooms[1]= 201;
    booking.nAssignedRooms= 2;
    booking.regime= FULL_BOARD;
    price= calculatePrice(appData.hotels.table[hotelIndex], booking, date);
    if (price == 3320.0) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
        printf("\n\t-> FAIL (Incorrect price calculation. Expected: %.2f Returned: %.2f)\n",3320.0, price);
	}

	printf("\nTest 2.7: Empty checkout queue");
	(*totalTest)++;
    date.day= 9; date.month= 11; date.year= 2019; 
    processCheckouts( &appData.hotels.table[hotelIndex], appData.customers, date, 
                      &appData.movements.table[0].checkoutQueue,
                      &appData.movements.table[0].currentBookings, 
                      &appData.movements.table[0].completedBookings );
    equals= (movement_cmp( movement, appData.movements.table[0] ) == 0);
    if (equals){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (no changes expected caused by an empty checkin queue)\n");
	}

	printf("\nTest 2.8: Checkout queue non-empty. Customers with incorrect checkout date");
	(*totalTest)++;
    prevOccupiedRooms= appData.hotels.table[hotelIndex].occupiedRooms;
    prevCurrentBookings= bookingList_length(appData.movements.table[0].currentBookings);
    prevCompletedBookings= bookingList_length(appData.movements.table[0].completedBookings);
    getCustomerQueueObject(QUEUE2,&appData.movements.table[0].checkoutQueue);
    processCheckouts( &appData.hotels.table[hotelIndex], appData.customers, date, 
                      &appData.movements.table[0].checkoutQueue,
                      &appData.movements.table[0].currentBookings, 
                      &appData.movements.table[0].completedBookings );
    postOccupiedRooms= appData.hotels.table[hotelIndex].occupiedRooms;
    postCurrentBookings= bookingList_length(appData.movements.table[0].currentBookings);
    postCompletedBookings= bookingList_length(appData.movements.table[0].completedBookings);
    if (prevOccupiedRooms == postOccupiedRooms && 
        customerQueue_empty(appData.movements.table[0].checkoutQueue) && 
        prevCurrentBookings == postCurrentBookings && 
        prevCompletedBookings == postCompletedBookings) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (no checkout should be effective since date does not match)\n");
	}

	printf("\nTest 2.9: Checkout queue non-empty. Customers with correct checkout date");
	(*totalTest)++;
    date.day= 10; date.month= 11; date.year= 2019; 
    prevOccupiedRooms= appData.hotels.table[hotelIndex].occupiedRooms;
    prevCurrentBookings= bookingList_length(appData.movements.table[0].currentBookings);
    prevCompletedBookings= bookingList_length(appData.movements.table[0].completedBookings);
    getCustomerQueueObject(QUEUE2,&appData.movements.table[0].checkoutQueue);
    processCheckouts( &appData.hotels.table[hotelIndex], appData.customers, date, 
                      &appData.movements.table[0].checkoutQueue,
                      &appData.movements.table[0].currentBookings, 
                      &appData.movements.table[0].completedBookings);
    postOccupiedRooms= appData.hotels.table[hotelIndex].occupiedRooms;
    postCurrentBookings= bookingList_length(appData.movements.table[0].currentBookings);
    postCompletedBookings= bookingList_length(appData.movements.table[0].completedBookings);
    if (prevOccupiedRooms > postOccupiedRooms && 
        customerQueue_empty(appData.movements.table[0].checkoutQueue)) {
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (No checkouts processed)\n");
	}
    
	printf("\nTest 2.10: Checkout queue non-empty. Correct date. Bookings list management");
	(*totalTest)++;
    if (prevCurrentBookings == postCurrentBookings+1 && 
        prevCompletedBookings == postCompletedBookings-1) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (1 checkout should have been processed on the current date)\n");
	}    
    
	printf("\nTest 2.11: Current bookings properly processed (price calculated)");    
	(*totalTest)++;
    bookingIndex40= findCustomerBooking(appData.movements.table[0].completedBookings, 40);
    if (bookingIndex40 != NO_CUSTOMER)
        nAssignedRooms= appData.movements.table[0].completedBookings.table[bookingIndex40-1].nAssignedRooms;
    else
        nAssignedRooms= 0;
    if (nAssignedRooms == 1 && 
        appData.movements.table[0].completedBookings.table[bookingIndex40-1].price == 1200.0) 
    {
        printf("\n\t-> OK\n");
        (*passedTest)++;                
    }
    else {
		printf("\n\t-> FAIL (No room price calculated for a completed booking)\n");
    }
    
	printf("\nTest 2.12: Current bookings properly processed (room free)");    
	(*totalTest)++;
    if (appData.hotels.table[0].layout[2][0] == FALSE) 
    {
        printf("\n\t-> OK\n");
        (*passedTest)++;                
    }
    else {
		printf("\n\t-> FAIL (Room 301 should be free after checkout)\n");
    }
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
