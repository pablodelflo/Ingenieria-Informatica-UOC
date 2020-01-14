#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

void getCustomerStr(tCustomer customer, int maxSize, char *str) 
{
	int length= 0;
    /* Uncomment to test*/
	length = snprintf(str,maxSize-1,"%d %s %s %s %d %d %d %s %d %d %d %d %.2f", 
        customer.id, customer.name, customer.surname, customer.docNumber, 
        customer.birthDate.year, customer.birthDate.month, customer.birthDate.day, 
        customer.birthCity, (int)customer.status, (int)customer.profile, customer.bookingsCounter,
        customer.points, customer.satisfaction);
    
	if (length>0) 
		str[length]='\0';
}

void getCustomerObject(const char *str, tCustomer *customer) 
{	
    int id= 0;
    /* Uncomment to test*/
    int status, profile;
	sscanf(str, "%d %s %s %s %d %d %d %s %d %d %d %d %f", &(id), customer->name, customer->surname, 
        customer->docNumber, &(customer->birthDate.year), &(customer->birthDate.month), &(customer->birthDate.day),
        customer->birthCity, &status, &profile, &customer->bookingsCounter, 
        &customer->points, &customer->satisfaction);
	customer->status = (tCivilState)(status);
	customer->profile = (tProfile)(profile);
    
	customer->id = (tCustomerId)(id);
}

int date_cmp( tDate d1, tDate d2 ) {
    
    int result;
    
    result= 0;

    if (d1.year > d2.year)
        result= 1;
    else if (d1.year < d2.year)
        result= -1;
    else {
        if (d1.month > d2.month)
            result= 1;
        else if (d1.month < d2.month)
            result= -1;
        else {
            if (d1.day > d2.day)
                result= 1;
            else if (d1.day < d2.day)
                result= -1;
        }
    }
    
    return result;
}

void customerTable_init(tCustomerTable *customerTable) {
	
	customerTable->nCustomers=0;
}

void convertToUpper( char *string )
{
    int i, len;
    char originalChar;
    
    len= strlen(string);
    for (i= 0; i < len; i++) {
        originalChar= string[i];
        if (originalChar >= 'a' && originalChar <= 'z') 
            string[i]= originalChar + 'A' - 'a';
    }
}

int strcmpUpper( char *s1, char *s2 )
{
    int result= 0;
    char string1[MAX_LINE];
    char string2[MAX_LINE];
    
    strncpy(string1,s1,MAX_LINE);
    strncpy(string2,s2,MAX_LINE);
    convertToUpper(string1);
    convertToUpper(string2);
    if (strcmp(string1,string2) < 0){
        result=-1;
    } else if (strcmp(string1,string2) > 0){
        result=1;
    }
    
    return result;
}

int customer_cmp(tCustomer d1, tCustomer d2) 
{	
    int result = 0;
        
    if (strcmpUpper(d1.name,d2.name) < 0){
		result = -1;
	} else {
		if (strcmpUpper(d1.name,d2.name) > 0){
			result = 1;
		} else {
			if (strcmpUpper(d1.surname,d2.surname) < 0){
				result = -1;
			} else {
				if (strcmpUpper(d1.surname,d2.surname) > 0){
					result = 1;
				} else {
					if (strcmpUpper(d1.docNumber,d2.docNumber) < 0){
						result = -1;
					} else {
						if (strcmpUpper(d1.docNumber,d2.docNumber) > 0){
							result = 1;
						} else {
							if (date_cmp(d1.birthDate,d2.birthDate) < 0){
								result = -1;
							} else {
								if (date_cmp(d1.birthDate,d2.birthDate) > 0){
									result = 1;
								} else {
									if (strcmpUpper(d1.birthCity,d2.birthCity) < 0){
										result = -1;
									} else {
										if (strcmpUpper(d1.birthCity,d2.birthCity) > 0){
											result = 1;
										} else {
											if (d1.status > d2.status){
												result = -1;
											} else {
												if (d1.status < d2.status){
													result = 1;
												} else {
													if (d1.profile > d2.profile){
														result = -1;
													} else {
														if (d1.profile < d2.profile){
																result = 1;
														} else {
															if (d1.bookingsCounter > d2.bookingsCounter){
																result = -1;
															} else {
																if (d1.bookingsCounter < d2.bookingsCounter){
																	result = 1;
																} else {
																	if (d1.points > d2.points){
																		result = -1;
																	} else {
																		if (d1.points < d2.points){
																			result = 1;
																		} else {
																			if (d1.satisfaction > d2.satisfaction){
																				result = -1;
																			} else {
																				if (d1.satisfaction < d2.satisfaction){
																					result = 1;
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
    }

    return result;
}

void customer_cpy(tCustomer *dst, tCustomer src) 
{    
    dst->id = src.id; 
    /* Uncomment to test*/
    strcpy(dst->name,src.name);
    strcpy(dst->surname,src.surname);
    strcpy(dst->docNumber,src.docNumber);
    dst->birthDate.year = src.birthDate.year;
    dst->birthDate.month = src.birthDate.month;
    dst->birthDate.day = src.birthDate.day;
    strcpy(dst->birthCity,src.birthCity);
    dst->status = src.status;
    dst->profile = src.profile;    
    dst->bookingsCounter = src.bookingsCounter;
    dst->points= src.points;
    dst->satisfaction= src.satisfaction;
    
}

void customerTable_add(tCustomerTable *tabCustomer, tCustomer customer, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new customer */
	if(tabCustomer->nCustomers>=MAX_CUSTOMERS)
		*retVal = ERR_MEMORY;

	if (*retVal == OK) {
		/* Add the new customer to the end of the table */
		customer_cpy(&tabCustomer->table[tabCustomer->nCustomers],customer);
		tabCustomer->nCustomers++;
	}

}

int customerTable_find(tCustomerTable tabCustomer, tCustomerId id) {

	int idx = NO_CUSTOMER;
	
	int i=0;
	while(i< tabCustomer.nCustomers && idx==NO_CUSTOMER) {
		/* Check if the id is the same */
		if(tabCustomer.table[i].id==id) {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void customerTable_del(tCustomerTable *tabCustomer, tCustomer customer) 
{
	
	int idToDelete = NO_CUSTOMER;
	int i;
	
	
	idToDelete=customerTable_find(*tabCustomer,customer.id);

	if (tabCustomer->nCustomers > 0 && idToDelete!=NO_CUSTOMER){
		for(i=idToDelete;i<tabCustomer->nCustomers;i++){
			tabCustomer->table[i]=tabCustomer->table[i+1];
		}
		
		tabCustomer->nCustomers--;
	}
}

void customerTable_save(tCustomerTable tabCustomer, const char* filename, tError *retVal) {

	*retVal = OK;
	
	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all customers to the file */
        for(i=0;i<tabCustomer.nCustomers;i++) {
            getCustomerStr(tabCustomer.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
}

void customerTable_load(tCustomerTable *tabCustomer, const char* filename, tError *retVal) {
	
	*retVal = OK;
	
	FILE *fin=0;
	char line[MAX_LINE];
	tCustomer newCustomer;
	
	/* Initialize the output table */
	customerTable_init(tabCustomer);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the lines */
		while(!feof(fin) && tabCustomer->nCustomers<MAX_CUSTOMERS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getCustomerObject(line, &newCustomer);
				/* Add the new customer to the output table */
				customerTable_add(tabCustomer, newCustomer, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}
}

int calculateAge( tDate birthDate )
{
	return 2019 - birthDate.year;
}

void customerTable_selectCustomers(tCustomerTable customers, char *city, tCustomerTable *result) 
{
	int i=0;
	int j=0;
	int age=0;
	char customerCity[MAX_CITY];
	char cityParameter[MAX_CITY];
	int stat=0;
	int prof=0;

	strncpy(cityParameter,city,MAX_CITY);
	
	customerTable_init(result);

	if (customers.nCustomers > 0){
		while (i<customers.nCustomers){
			age=calculateAge(customers.table[i].birthDate);
			strncpy(customerCity,customers.table[i].birthCity,MAX_CITY);
			stat=customers.table[i].status;//The value must be 0
			prof=customers.table[i].profile;//Values must be 3, 4 or 5
			
			if (strcmpUpper(cityParameter,customerCity)!=0){
				if (age>=25 && age<=35 && stat==0 && (prof==3 || prof==4 || prof==5)){
					customer_cpy(&result->table[j],customers.table[i]);
					result->nCustomers++;
					j++;
				}
			}
			
			i++;
		}
	}
}

void customerTable_selectSatisfiedCustomers(tCustomerTable customers, tCustomerTable *result) {
	
	int i=0;
	int j=0;
	float satisf=0;
	int bookings=0;
	
	customerTable_init(result);
	
	if (customers.nCustomers > 0){
		while (i<customers.nCustomers){
			satisf=customers.table[i].satisfaction;//The value must be greater than 85%
			bookings=customers.table[i].bookingsCounter;//The value must be greater than 10
			
			if (satisf>85 && bookings>=10){
				customer_cpy(&result->table[j],customers.table[i]);
				result->nCustomers++;
				j++;
			}
			
			i++;
		}
	}
}

float customerTable_getAvgPointsPerBooking(tCustomerTable tabCustomer) 
{
    float avg=0.0;
	int i=0;
	int auxPoints=0;
	int auxBookings=0;

	if (tabCustomer.nCustomers > 0){
		while (i<tabCustomer.nCustomers){
			auxPoints=auxPoints+tabCustomer.table[i].points;
			auxBookings=auxBookings+tabCustomer.table[i].bookingsCounter;
			avg=(float)auxPoints/(float)auxBookings;
			i++;
		}
	}

    return avg;
}

void customerTable_getMaxSatisfactionPerAgeInterval(tCustomerTable tabCustomer,
     float *upto29, float *between30and44, float *between45and59, float *from60) 
{
	int i=0;
	int auxAge=0;
	float auxSatis=0.0;
	//This array includes the maximum satisfaction of each age in each position: 0 for under 30, 
	//1 between 30 and 44, 2 between 45 and 59 and 3 for over 60
	float maxSatisfaction[4] = {0.0,0.0,0.0,0.0};
	
	
	if (tabCustomer.nCustomers > 0){
		while (i<tabCustomer.nCustomers){
			auxAge=calculateAge(tabCustomer.table[i].birthDate);
			if (auxAge<=29){
				auxSatis=tabCustomer.table[i].satisfaction;
				if (auxSatis>maxSatisfaction[0]){
					maxSatisfaction[0]=auxSatis;
				}
			} else {
				if (auxAge>=30 && auxAge<=44){
					auxSatis=tabCustomer.table[i].satisfaction;
					if (auxSatis>maxSatisfaction[1]){
						maxSatisfaction[1]=auxSatis;
					}
				} else {
					if (auxAge>=45 && auxAge<=59){
						auxSatis=tabCustomer.table[i].satisfaction;
						if (auxSatis>maxSatisfaction[2]){
							maxSatisfaction[2]=auxSatis;
						}
					} else {
						if (auxAge>=60){
							auxSatis=tabCustomer.table[i].satisfaction;
							if (auxSatis>maxSatisfaction[3]){
								maxSatisfaction[3]=auxSatis;
							}
						}
					}
				}
			}
			
			i++;
		}
	}
	
	*upto29=maxSatisfaction[0];
	*between30and44=maxSatisfaction[1];
	*between45and59=maxSatisfaction[2];
	*from60=maxSatisfaction[3];

}

