/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */


#define MAX_TICKETS 100

typedef enum {FALSE, TRUE} boolean;
typedef enum {BAR, RESTAURANT, BEAUTY_SALOON, SHOP} tSource;

typedef struct {
    int roomNum;
	tSource source;
	int date;
	int hour;
	float amount;
} tTicket;



#endif /*__DATA_H*/