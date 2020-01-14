/* This code ensures that this file is included only once */
#ifndef __TEST_H
#define __TEST_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

void runTests();
void runAllTests(int *totalTest, int *passedTest);



#endif /*__TEST_H*/