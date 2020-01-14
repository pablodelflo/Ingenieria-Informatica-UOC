#include <stdio.h>
#include "data.h"
#include "ticket.h"
#include "stack.h"
#include "test.h"


#define TICKET1 "105 1 20190705 2310 90.00"    
#define TICKET2 "205 1 20190705 2340 70.00"
#define TICKET3 "123 2 20190810 1006 25.15"
#define TICKET4 "202 0 20190921 1314 50.00"
#define TICKET5 "222 3 20191212 1110 40.00"
#define TICKET6 "205 3 20191212 1510 40.00"
#define TICKET7 "205 3 20190705 2340 40.00"


void runTests() {	
	int passedTests = 0;
	int totalTests = 0;
	
	printf("=================================================\n");
	printf("====       PAC10 TESTS        ====\n");
	printf("=================================================\n");	
	runAllTests(&totalTests, &passedTests);

	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");		
	printf("\tPR1: Passed %d of %d [%0.2f%%]\n", passedTests, totalTests, (float)passedTests/totalTests*100.0);
	printf("===================================\n");		
}

void runAllTests(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
	tStack s1, s2, s3, expectedResult;
	float amount;
	
	tTicket t1, t2, t3, t4, t5, t6, t7;
	
	getTicketObject(TICKET1, &t1);
	getTicketObject(TICKET2, &t2);
	getTicketObject(TICKET3, &t3);
	getTicketObject(TICKET4, &t4);
	getTicketObject(TICKET5, &t5);
	getTicketObject(TICKET6, &t6);
	getTicketObject(TICKET7, &t7);


printf("\nTest 1a.1:  Add tickets - empty stack ");
	(*totalTest)++;	
	createStack(&s1);

	addTickets(s1, &amount, 205);
	
	if (amount == 0){
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

printf("\nTest 1a.2:  Add tickets - several for selected room ");
	(*totalTest)++;	
	createStack(&s1);
	createStack(&s2);
	createStack(&expectedResult);
	
	push(&s1, t1);
	push(&s1, t2);
	push(&s1, t7);
	push(&s1, t3);
	push(&s1, t4);
	push(&s1, t5);
	push(&s1, t6);
	
	
	addTickets(s1, &amount, 205);
	
	if (amount ==150.00){
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
printf("\nTest 1a.3:  Add tickets - none for selected room ");
	(*totalTest)++;	
	createStack(&s1);

	
	push(&s1, t1);
	push(&s1, t3);
	push(&s1, t4);
	push(&s1, t5);
	
	addTickets(s1, &amount, 205);
	
	if (amount == 0){
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 1b.1: Merge stacks. Both empty");
	(*totalTest)++;
	createStack(&s1);
	createStack(&s2);
	mergeStack(s1, s2, &s3);
	if (emptyStack(s3))  {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	printf("\nTest 1b.2:  Merge stacks. Only one empty ");
	(*totalTest)++;	
	createStack(&s1);
	createStack(&s2);
	createStack(&expectedResult);
		
	push(&s1, t1);
	push(&s1, t2);
	push(&expectedResult, t1);
	push(&expectedResult, t2);
	
	mergeStack(s1, s2, &s3);
	if (equalStacks(s3, expectedResult) ){
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
printf("\nTest 1b.3:  Merge stacks. Both with tickets. All tickets from stack 1 < tickets from stack2 ");
	(*totalTest)++;	
	createStack(&s1);
	createStack(&s2);
	createStack(&expectedResult);
	
	push(&s1, t1);
	push(&s1, t2);
	push(&s2, t3);
	push(&s2, t4);
	push(&expectedResult, t1);
	push(&expectedResult, t2);
	push(&expectedResult, t3);
	push(&expectedResult, t4);
	mergeStack(s1, s2, &s3);
	if (equalStacks(s3, expectedResult)){
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

printf("\nTest 1b.4:  Merge stacks.  Both with tickets. dates mixed ");
	(*totalTest)++;	
	createStack(&s1);
	createStack(&s2);
	createStack(&expectedResult);
	
	push(&s1, t1);
	push(&s1, t3);
	push(&s2, t2);
	push(&s2, t4);
	push(&s2, t6);
	push(&expectedResult, t1);
	push(&expectedResult, t2);
	push(&expectedResult, t3);
	push(&expectedResult, t4);
	push(&expectedResult, t6);
	
	
	mergeStack(s1, s2, &s3);
	
	if (equalStacks(s3, expectedResult)){
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
printf("\nTest 1b.5:  Merge stacks. Tickets with same date/hour in both stacks");
	(*totalTest)++;	
	createStack(&s1);
	createStack(&s2);
	createStack(&expectedResult);
	
	push(&s1, t1);
	push(&s1, t3);
	push(&s2, t2);
	push(&s2, t7);
	push(&s2, t6);
	push(&expectedResult, t1);
	push(&expectedResult, t2);
	push(&expectedResult, t7);
	push(&expectedResult, t3);
	push(&expectedResult, t6);
	
	
	mergeStack(s1, s2, &s3);
	
	if (equalStacks(s3, expectedResult)){
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}	

	
	