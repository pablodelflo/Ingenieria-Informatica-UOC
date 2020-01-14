#include "data.h"

void customerQueue_create( tCustomerQueue *queue );
tCustomerId customerQueue_head(tCustomerQueue queue);
boolean customerQueue_empty(tCustomerQueue queue);
boolean customerQueue_full(tCustomerQueue queue);
int  customerQueue_length(tCustomerQueue queue);
void customerQueue_enqueue(tCustomerQueue *queue, tCustomerId newElement);
void customerQueue_dequeue(tCustomerQueue *queue);
void customerQueue_cpy(tCustomerQueue *dst, tCustomerQueue src);
int  customerQueue_cmp(tCustomerQueue q1, tCustomerQueue q2);
void customerQueue_save(tCustomerQueue tabCustomers, const char* filename, tError *retVal);
void customerQueue_load(tCustomerQueue *tabCustomers, const char* filename, tError *retVal);
void getCustomerQueueStr( tCustomerQueue queue, int maxSize, char *str);
void getCustomerQueueObject(const char *str, tCustomerQueue *queue) ;
 
