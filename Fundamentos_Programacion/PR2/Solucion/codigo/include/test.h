/* Run all the test set */
#include "data.h"
#include "api.h"

/* Runs the applications tests */
void runTests();

/* Runs the applications tests corresponding to PR1 */
void runTestsPR1(int* totalTest, int* passedTest);

/* Runs the applications tests corresponding to PR2 */
void runTestsPR2(int* totalTest, int* passedTest);

/* Test the copy and comparison of customers */
void test_cpycmp(int* totalTest, int* passedTest);

/* Test the customer search */
void test_search(int* totalTest, int* passedTest);

/* Test the customer statistics */
void test_count(int* totalTest, int* passedTest);

/* Test the customer sorting */
void test_sort(int* totalTest, int* passedTest);

/* Test the api calls */
void test_api(int* totalTest, int* passedTest);

/* Test the selection calls */
void test_selection(int* totalTest, int* passedTest);

/* Test the filter combination calls */
void test_filter_combination(int* totalTest, int* passedTest);

/* Test the statistics calls */
void test_statistics(int* totalTest, int* passedTest);

/* Test the table operations calls */
void test_table_operation(int* totalTest, int* passedTest);

/* Test the table movements calls: checkins */
void test_movements_checkin(int *totalTest, int *passedTest);

/* Test the table movements calls: checkouts */
void test_movements_checkout(int *totalTest, int *passedTest);
