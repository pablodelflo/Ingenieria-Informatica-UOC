/*
*ESTE FICHERO CONTIENE:
* 	Constantes del programa
* 	Tipo enumerado tTypeHotel y boolean
* 	La declaracion del struct tHotel 	
* 	Headers de las funciones creadas
*/

//CONSTANTES
#define MAX_BRAND 15+1
#define MAX_NAME 15+1
#define MAX_CITY 15+1

//TIPOS ENUMERADOS
typedef enum {BUDGET,INN,RESORT,CONDO,LUXURY,COUNTRY} tTypeHotel;
typedef enum {FALSE,TRUE} tBoolean;

//STRUCT THOTEL
typedef struct {
  int id;
  char brand[MAX_BRAND];
  char name[MAX_NAME];
  tTypeHotel type;
  char city[MAX_CITY];
  int category;
  float priceDouble; /* reference price: double room */
  float distanceFromCityCenter;
  tBoolean hasPool;
  tBoolean hasGym;
  tBoolean closeToSubway;
  float percentOccupation;
} tHotel;


//HEADERS
void hotelRead(tHotel *h);
void hotelWrite(tHotel h);
void hotelCmpPoints(tHotel hotel1,tHotel hotel2,tHotel *bestHotel);
int hotelComputePoints(tHotel hotel,float price, float distance);
void hotelCopy(tHotel src,tHotel *dst);