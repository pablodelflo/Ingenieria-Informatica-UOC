#include <stdio.h>
#include "data.h"
#include "ticket.h"


void getTicketStr(tTicket ticket, int maxSize, char *str) 
{
	int length;
	length = 0;
	length = snprintf(str,maxSize-1,"%d %u %d %d  %.2f", 
        ticket.roomNum, ticket.source, ticket.date, ticket.hour, ticket.amount);
    if (length>0) 
		str[length]='\0';
}

void getTicketObject(const char *str, tTicket *ticket) 
{	

	sscanf(str, "%d %u %d %d %f", &ticket->roomNum, &ticket->source, &ticket->date, 
        &ticket->hour, &ticket->amount);
}
void ticketCpy(tTicket src, tTicket *dest){
	dest->roomNum = src.roomNum;
	dest->source  = src.source;
	dest->date =  src.date;
	dest->hour = src.hour;
	dest->amount = src.amount;
	
}

int ticketCmpDate(tTicket t1, tTicket t2){

	int result;
	result=0;
	if (t1.date <t2.date) 
		result=-1;
	else
		if (t1.date > t2.date) 
			result=1;
		else
			if (t1.hour<t2.hour) 
				result=-1;
			else 
				if (t1.hour >t2.hour)
					result=1;
	

  return(result);
}

boolean ticketEquals(tTicket t1, tTicket t2){
	
	
	return(t1.roomNum == t2.roomNum && t1.source == t2.source && t1.date == t2.date && t1.hour == t2.hour && t1.amount == t2.amount);
}
