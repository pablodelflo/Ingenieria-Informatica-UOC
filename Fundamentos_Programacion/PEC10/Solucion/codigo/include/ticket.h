/* This code ensures that this file is included only once */
#ifndef TICKET_H
#define __TICKET_H
/* If the constant STACK_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */



void getTicketStr(tTicket ticket, int maxSize, char *str);
void getTicketObject(const char *str, tTicket *ticket);
void ticketCpy(tTicket src, tTicket *dest);
int ticketCmpDate(tTicket t1, tTicket t2);
boolean ticketEquals(tTicket t1, tTicket t2);

#endif /*__TICKET_H*/