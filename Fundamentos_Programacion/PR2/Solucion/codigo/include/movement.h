#include "data.h"

/* Get a textual representation of a movement */
void getMovementStr(tMovement movement, int maxSize, char *str);

/* Get a movement object from its textual representation */
void getMovementObject(const char *str, tMovement *movement);

/* Get a textual representation of a booking list */
void getBookingStr(tBookingList bookings, int maxSize, char *str);

/* Get a booking list object from its textual representation */
void getBookingObject(const char *str, tBookingList *bookings);

/* Copy the movement data in src to dst*/
void movement_cpy(tMovement *dst, tMovement src);

/* Compares the movement data of p1 and p2*/
int movement_cmp(tMovement p1, tMovement p2);

/* Initializes the given movements table */
void movementTable_init(tMovementTable *movementsTable);

/* Add a new movement to the table of movements */
void movementTable_add(tMovementTable *tabMovements, tMovement movement, tError *retVal);

/* Load the table of movements from a file */
void movementTable_load(tMovementTable *tabMovements, const char* filename, tError *retVal);

/* Save a table of movements to a file */
void movementTable_save(tMovementTable tabMovements, const char* filename, tError *retVal);

