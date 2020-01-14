/* This code ensures that this file is included only once */
#ifndef __STACK_H
#define __STACK_H
/* If the constant STACK_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

typedef struct {
		tTicket A[MAX_TICKETS];
		int nelem;
} tStack;

// provided base stack functionalities
void createStack(tStack *s);
void push(tStack *s, tTicket t) ;
void pop(tStack *s);
tTicket top(tStack s);
boolean emptyStack(tStack s);
boolean fullStack(tStack s);
int heightStack(tStack s);
boolean equalStacks(tStack s1, tStack s2);

// PAC10 Header definition for the functionalities to implement

void addTickets(tStack src,float *totalAmount,int roomNumber);
void mergeStack(tStack src1,tStack src2,tStack *dest);

#endif /*__STACK_H*/