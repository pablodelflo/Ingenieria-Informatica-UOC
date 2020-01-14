#include "data.h"

void bookingList_create(tBookingList *list);
boolean bookingList_empty(tBookingList list);
boolean bookingList_full(tBookingList list);
tError bookingList_insert(tBookingList *list, tBooking newElement, int index);
tError bookingList_delete(tBookingList *list, int index);
tError bookingList_get(tBookingList list, int index, tBooking *booking);
boolean bookingList_end(tBookingList list, int index);
tError bookingList_replace(tBookingList *list, int index, tBooking elem);
unsigned int bookingList_length(tBookingList list);
int bookingList_cmp( tBookingList b1, tBookingList b2 );
void bookingList_cpy( tBookingList *dst, tBookingList src );
void booking_cpy( tBooking *dst, tBooking src );
int booking_cmp( tBooking b1, tBooking b2 );
