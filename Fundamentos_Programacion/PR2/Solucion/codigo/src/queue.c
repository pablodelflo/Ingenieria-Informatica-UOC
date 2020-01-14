#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void customerQueue_create( tCustomerQueue *queue ) {
	queue->nElem=0;
}

tCustomerId customerQueue_head(tCustomerQueue queue) {
	tCustomerId head;
    head= queue.table[0];
	return head;
}

boolean customerQueue_empty(tCustomerQueue queue) {	
	boolean empty = TRUE;
	empty = (queue.nElem==0);
	return empty;
}

boolean customerQueue_full(tCustomerQueue queue) {	
	boolean full = FALSE;
	full = (queue.nElem==MAX_CUSTOMERS);
	return full;
}

int customerQueue_length(tCustomerQueue queue)
{
    return queue.nElem;
}

void customerQueue_enqueue(tCustomerQueue *queue, tCustomerId newElement) 
{
    queue->table[queue->nElem]= newElement;
	queue->nElem++;

}

void customerQueue_dequeue (tCustomerQueue *queue) {
	
	unsigned int i=0;
	
	for (i=0; i<queue->nElem-1; i++) {
		queue->table[i]= queue->table[i+1];
	}
	queue->nElem--;
}

void customerQueue_cpy(tCustomerQueue *dst, tCustomerQueue src)
{    
    customerQueue_create(dst);
    while (!customerQueue_empty(src)) {
            customerQueue_enqueue(dst, customerQueue_head(src));
            customerQueue_dequeue(&src);
    }
}

int customerQueue_cmp(tCustomerQueue q1, tCustomerQueue q2)
{
    int result;
    
    result= 0;
    
    if (customerQueue_length(q1) < customerQueue_length(q2))
        result= -1;
    else if (customerQueue_length(q1) > customerQueue_length(q2))
        result= 1;
    else {
        while (!customerQueue_empty(q1) && result==0) {
                result= (customerQueue_head(q1) == customerQueue_head(q2));
                customerQueue_dequeue(&q1);
                customerQueue_dequeue(&q2);
        }            
    }
    
    return result;
}

void getCustomerIdStr( tCustomerId customer, int maxSize, char *str )
{
    int length;

    length= snprintf(str, maxSize-1, "%d", customer);
            
    if (length>0) 
        str[length]='\0';
} 

void getCustomerIdObject(const char *str, tCustomerId *customer) 
{
	int aux_customer_id;
    
    sscanf(str, "%d", &aux_customer_id); 
    *customer= aux_customer_id;
}

/* The content of the fields of the queue structure is written into the string str */
void getCustomerQueueStr( tCustomerQueue queue, int maxSize, char *str) 
{
    int length;
	tCustomerId customerId;
    char tempStr[MAX_LINE];    

    /* write the size of the stack */
    length= snprintf(str, maxSize-1, "%d", customerQueue_length(queue));
 	if (length>0) 
		str[length]='\0';

    while(!customerQueue_empty(queue))
    {
        /* copy str into an auxiliar copy of it */
        strcpy(tempStr,str);

        /* get the top of the stack */
        customerId = customerQueue_head(queue);

        /* write it as a string */
        length= snprintf(str, maxSize-1, "%s %d", tempStr, customerId);
        if (length>0) 
            str[length]='\0';

        /* dequeue the head element to allow writting of next element */
        customerQueue_dequeue(&queue);
    }

 	if (length>0) 
		str[length]='\0';
}


/* The content of the string str is parsed into the fields of the queue structure */
void getCustomerQueueObject(const char *str, tCustomerQueue *queue) 
{
	int i, size, aux_customer_id;
    char tempStr[MAX_LINE];   
    char nextStr[MAX_LINE];   
	tCustomerId newCustomerId;

    /* read queue size */
    sscanf(str, "%d %[^\n]s", &size, tempStr); 

    /* Initialize the quaue */
    customerQueue_create(queue);

    for (i= 0; i< size; i++)
    {
        /* read the loaded data as a string*/
        sscanf(tempStr, "%d %[^\n]s", &aux_customer_id, nextStr); 
        newCustomerId= (tCustomerId)(aux_customer_id);

        /* enqueue it on the queue */
        customerQueue_enqueue( queue, newCustomerId );

        /* prepare next iteration */
        strcpy(tempStr,nextStr);   
    }
}

void customerQueue_save(tCustomerQueue queue, const char* filename, tError *retVal) {

	*retVal = OK;
	FILE *fout=0;
	char str[MAX_LINE];
	tCustomerId req;
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {

		/* Save all customers to the file */
		while(!customerQueue_empty(queue)){
			req = customerQueue_head(queue);
			getCustomerIdStr(req, MAX_LINE, str);
			fprintf(fout, "%s\n", str);
			customerQueue_dequeue(&queue);
		}
           
        /* Close the file */
		fclose(fout);
	} 
}

void customerQueue_load(tCustomerQueue *queue, const char* filename, tError *retVal) {
	
	*retVal = OK;
	
	FILE *fin=0;
	char line[MAX_LINE];
	tCustomerId newCustomer;
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

	/* Initialize the queue */
		customerQueue_create(queue);

		/* Read all the lines (customers) */
		while(!feof(fin) && !customerQueue_full(*queue)) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getCustomerIdObject(line, &newCustomer);
				/* Add the new customer to the queue */
				customerQueue_enqueue(queue, newCustomer);		
			}
		}

		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}
