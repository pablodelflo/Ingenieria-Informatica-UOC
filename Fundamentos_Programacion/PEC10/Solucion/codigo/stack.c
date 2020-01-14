#include <stdio.h>
#include "data.h"
#include "stack.h"
#include "ticket.h"



void createStack(tStack *s) {
    s->nelem=0;
}

void push(tStack *s, tTicket t) {

    if (s->nelem == MAX_TICKETS) {
        printf("\n Full stack \n");
    } else {
        ticketCpy(t, &s->A[s->nelem]); /* first position in C is 0 */
        s->nelem++;
    }
}

void pop(tStack *s) {

    if (s->nelem == 0) {
        printf("\n Empty stack\n");
    } else {
        s->nelem--;
    }
}

tTicket top(tStack s) {

    tTicket t;
    if (s.nelem == 0) {
        printf("\n Empty stack \n");
    } else {
        ticketCpy(s.A[s.nelem-1], &t);
    }
    return t;
}

boolean emptyStack(tStack s) {

    return (s.nelem == 0);
}

boolean fullStack(tStack s) {

    return (s.nelem == MAX_TICKETS);
}

int heightStack(tStack s) {

    return (s.nelem);
}
boolean equalStacks(tStack s1, tStack s2) {
	boolean result;
	
	result= TRUE;
	if (!(heightStack(s1) == heightStack(s2)))
		result= FALSE;
	else {
		while(!emptyStack(s1) && result) {
			if (ticketEquals(top(s1), top(s2) )) {
				pop(&s1);
				pop(&s2);
			}
			else result = FALSE;
			
		}
	}
	return(result);
}

// PAC10 Implementation of mergeStack
void addTickets(tStack src,float *totalAmount,int roomNumber){
	
	float ttAmount=0;
	tTicket t;
	
	while(!emptyStack(src)){
		//top(src);
		ticketCpy(top(src),&t);
		if(t.roomNum==roomNumber){
			ttAmount=ttAmount+t.amount;
		}
		pop(&src);
	}
	*totalAmount=ttAmount;
}
void mergeStack(tStack src1,tStack src2,tStack *dest){
	
	tStack interStack;
	tTicket t1;
	tTicket t2;

	createStack(&interStack);
	createStack(dest);
    
    while(!emptyStack(src1)&&!emptyStack(src2)){
        ticketCpy(top(src1),&t1);
        ticketCpy(top(src2),&t2);
        if(ticketCmpDate(t1,t2)>0){
            push(&interStack,top(src1));
            pop(&src1);
        } else {
                push(&interStack,top(src2));
                pop(&src2);
        }
    }
    
    if(emptyStack(src1)){
        while(!emptyStack(src2)){
            push(&interStack,top(src2));
            pop(&src2);
        }
    } else {
            while(!emptyStack(src1)){
                push(&interStack,top(src1));
                pop(&src1);
            }
    }
    
    while(!emptyStack(interStack)){
        push(dest,top(interStack));
        pop(&interStack);
    }
}



	

