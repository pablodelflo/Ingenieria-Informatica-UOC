#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movement.h"
#include "list.h"
#include "queue.h"
#include "customer.h"

/* The content of the fields of the booking structure is written into the string str */
void getBookingStr(tBookingList bookings, int maxSize, char *str) {

    int length, i;
    char tempStr[MAX_LINE];  
    tBooking booking;  

    /* write the size of the list */
    length= snprintf(str, maxSize-1, "%d", bookingList_length(bookings));

 	if (length>0) 
		str[length]='\0';
    
	/* loop the elements of the list of booking writting its elements */
	for(i=1; !bookingList_end(bookings,i); i++) 
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the current booking */
		bookingList_get(bookings, i, &booking);
        
        /* write it as a string */
        length= snprintf(str, maxSize-1, "%s %d %d %d %d %d %d %d %d %d %.2f %d %d %d %d %d", tempStr, 
                booking.id, booking.nGuests, 
                booking.checkInDate.day, booking.checkInDate.month, booking.checkInDate.year, 
                booking.checkOutDate.day, booking.checkOutDate.month, booking.checkOutDate.year, 
                booking.regime, booking.price, booking.nAssignedRooms, booking.assignedRooms[0], 
                booking.assignedRooms[1], booking.assignedRooms[2], booking.assignedRooms[3] );

        if (length>0) 
            str[length]='\0';
    }

	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the booking structure */
void getBookingObject(const char *str, tBookingList *bookings) 
{
	int i, size, aux_customer_id, aux_regime;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tBooking newBooking;

    /* read list size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 

    /* Initialize the bookings table */
    bookingList_create(bookings);

    for (i= 1; i<= size; i++)
    {
        /* read the loaded booking as a string*/
        sscanf(tempStr, "%d %d %d %d %d %d %d %d %d %f %d %d %d %d %d %[^\n]s", 
            &aux_customer_id, &newBooking.nGuests, 
            &newBooking.checkInDate.day, &newBooking.checkInDate.month, &newBooking.checkInDate.year,
            &newBooking.checkOutDate.day, &newBooking.checkOutDate.month, &newBooking.checkOutDate.year,
            &aux_regime, &newBooking.price, &newBooking.nAssignedRooms, &newBooking.assignedRooms[0],
            &newBooking.assignedRooms[1], &newBooking.assignedRooms[2], &newBooking.assignedRooms[3],
            nextStr); 

        newBooking.id= (tCustomerId)(aux_customer_id);
        newBooking.regime= (tRegime)(aux_regime);

        /* add the booking to the table */
        bookingList_insert(bookings,newBooking,i);

        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

/* The content of the fields of the movement structure is written into the string str */
void getMovementStr(tMovement movement, int maxSize, char *str) {

    int length;
	
    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d %d %d %d", 
             (int)movement.id, movement.date.day, movement.date.month, movement.date.year);
             
	if (length>0) 
		str[length]='\0';
}

/* The content of the string str is parsed into the fields of the movement structure */
void getMovementObject(const char *str, tMovement *movement) {

	int aux_id;
 			 
    /* read movement data */
    sscanf(str, "%d %d %d %d", 
        &aux_id, &movement->date.day, &movement->date.month, &movement->date.year);

    movement->id = (tHotelId)aux_id;
    bookingList_create( &movement->pendingBookings );
    bookingList_create( &movement->currentBookings );
    bookingList_create( &movement->completedBookings );
    customerQueue_create(&movement->checkinQueue);
    customerQueue_create(&movement->checkoutQueue);
}

void movement_cpy(tMovement *dst, tMovement src) 
{
    dst->id= src.id;
    date_cpy(&dst->date, src.date);
    bookingList_cpy( &dst->pendingBookings, src.pendingBookings );
    bookingList_cpy( &dst->currentBookings, src.currentBookings );
    bookingList_cpy( &dst->completedBookings, src.completedBookings );
    customerQueue_cpy( &dst->checkinQueue, src.checkinQueue );
    customerQueue_cpy( &dst->checkoutQueue, src.checkoutQueue );
}

int movement_cmp(tMovement d1, tMovement d2)
{
    int result = 0;

    if (d1.id > d2.id)
        result= 1;
    else if (d1.id < d2.id)
        result= -1;
    else {
        result= date_cmp(d1.date, d2.date);
        if (result==0) {
            result= bookingList_cmp(d1.pendingBookings,d2.pendingBookings);
            if (result==0) {
                result= bookingList_cmp(d1.currentBookings,d2.currentBookings);
                if (result==0) {
                    result= bookingList_cmp(d1.completedBookings,d2.completedBookings);
                    if (result==0) {
                        result= customerQueue_cmp(d1.checkinQueue,d2.checkinQueue);
                        if (result==0) {
                            result= customerQueue_cmp(d1.checkoutQueue,d2.checkoutQueue);
                        }                                        
                    }                                        
                }                                        
            }
        }
    }

    return result;
}

void movementTable_init(tMovementTable *movementsTable) {
	
	movementsTable->nMovements= 0;
}

void movementTable_add(tMovementTable *tabMovements, tMovement movement, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new movement */
	if(tabMovements->nMovements>=MAX_MOVEMENTS)
		*retVal = ERR_MEMORY;

	if (*retVal == OK) {
		/* Add the new movement to the end of the table */
		movement_cpy(&tabMovements->table[tabMovements->nMovements],movement);
		tabMovements->nMovements++;
	}
}

void movementTable_save(tMovementTable tabMovements, const char* filename, tError *retVal) {

    *retVal = OK;

	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} 
    else 
    {
        /* Save general movement data to the file */
        for(i=0;i<tabMovements.nMovements;i++) 
        {
            getMovementStr(tabMovements.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            
            /* Save the bookings lists */
            getBookingStr(tabMovements.table[i].pendingBookings, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            getBookingStr(tabMovements.table[i].currentBookings, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            getBookingStr(tabMovements.table[i].completedBookings, MAX_LINE, str);
            fprintf(fout, "%s\n", str);

            /* Save the queues */
            getCustomerQueueStr(tabMovements.table[i].checkinQueue, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
            getCustomerQueueStr(tabMovements.table[i].checkoutQueue, MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
                    
        /* Close the file */
        fclose(fout);
	}
}

void movementTable_load(tMovementTable *tabMovements, const char* filename, tError *retVal) 
{	
	char line[MAX_LINE];
	tMovement newMovement;
    int movementLines;
	FILE *fin=0;
	*retVal = OK;
	
	/* Initialize the output table */
	movementTable_init(tabMovements);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the movements */
		while(!feof(fin) && tabMovements->nMovements<MAX_MOVEMENTS) 
        {
			/* Read the movement object */
            movementLines= 0;
			line[0] = '\0';
			fgets(line, MAX_LINE-1, fin);
			line[MAX_LINE-1]='\0';
			if (strlen(line)>0) {
               getMovementObject(line, &newMovement);
               movementLines++;
            }

			/* Read the pending bookings object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getBookingObject(line,&newMovement.pendingBookings);
                    movementLines++;
                }
            }
                
			/* Read the current bookings object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getBookingObject(line,&newMovement.currentBookings);
                    movementLines++;
                }
            }
            
			/* Read the completed bookings object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getBookingObject(line,&newMovement.completedBookings);
                    movementLines++;
                }
            }
            
			/* Read the check-in queue object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getCustomerQueueObject(line,&newMovement.checkinQueue);                    
                    movementLines++;
                }
            }
            
			/* Read the check-out queue object */
            if (!feof(fin)) {
                line[0] = '\0';
                fgets(line, MAX_LINE-1, fin);
                line[MAX_LINE-1]='\0';
                if (strlen(line)>0) {
                    getCustomerQueueObject(line,&newMovement.checkoutQueue);
                    movementLines++;
                }
            }
            
            /* Add the new movement to the output table */
            if (movementLines == 6) 
                movementTable_add(tabMovements, newMovement, retVal);		
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}
