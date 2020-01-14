#define MAX_BRAND 15+1
#define MAX_NAME 15+1
#define MAX_CITY 15+1
#define MAX_HOTELS 100
#define MAX_LINE 514

typedef enum {FALSE, TRUE} tBoolean;
typedef enum { BUDGET, INN, RESORT, CONDO, LUXURY, COUNTRY } tTypeHotel; 

typedef struct {
    int id; 
    char brand[MAX_BRAND]; 
    char name[MAX_NAME]; 
    char city[MAX_CITY]; 
    int category;
    tTypeHotel type;
	int numRooms;
    float priceDouble; /* reference price: double room */
    float distanceFromCityCenter;
    tBoolean hasPool;
    tBoolean hasGym;
    tBoolean closeToSubway;
    float percentOccupation;
} tHotel;

typedef struct{
	tHotel hotels[MAX_HOTELS];
	int nHotels;
}tHotelTable;

void hotelRead(tHotel *h);
void hotelCopy (tHotel *dst, tHotel src);
void hotelWrite(tHotel h);
void getHotelObject(const char *str, tHotel *hotel);
void hotelsTableAddElement(tHotelTable *tabHotels, tHotel hotel);
void hotelsTableLoadDataFromFile(tHotelTable *tabHotels, const char* filename);
int hotelComputePoints(tHotel hotel,float price,float distance);

void hotelsTableInitialize(tHotelTable *selectedHotelsTable);
void hotelsTableSelect(tHotelTable hotelsTable, char city[MAX_CITY], float price, float distance, int points, tHotelTable *selectedHotelsTable);
float hotelsComputeAverageOccupation(tHotelTable hotelTable, char city[MAX_CITY]);