/***************************************************************
* Fichero: PEC4.c
* Autor: Pablo J. Delgado Flores
* Fecha: 20/10/2019
* Descripcion: Este fichero contiene la solucion al ejercicio
* planteado en la PEC4 de Fundamentos de Programacion
***************************************************************/
#include <stdio.h>

/*Definimos las constantes que usaremos en el programa*/
#define MAX_CHARACTERS 10
#define MIN_REPETITIONS 1
#define MAX_REPETITIONS 100
#define NUMBER1_ASCII 48
#define NUMBER9_ASCII 57
#define NUMBER_LETTER_A 97
#define ENCRYPTED_POSITION 3
#define ALPHABET 26

/*Comenzamos la definicion del programa principal*/
int main(int argc, char **argv)
{
	char password[MAX_CHARACTERS+1];
	int numRepetitions = 0;
	int i = 1;
	int j = 0;
	int numberDigits;
	int numberLetter;
	while (numRepetitions<MIN_REPETITIONS || numRepetitions>MAX_REPETITIONS){
		printf("Numero de passwords a generar: ");
		scanf("%d",&numRepetitions);
		if (numRepetitions<MIN_REPETITIONS || numRepetitions>MAX_REPETITIONS){
			printf("\n=============================================\n");
			printf("ERROR: debes generar entre 1 y 100 passwords.\n");
			printf("=============================================\n\n");
		}
	}
	for(i;i<=numRepetitions;i++){
		printf("Introduce tu password a encriptar: ");
		scanf("%s",password);
		numberDigits = 0;
		numberLetter = 0;
		for(j=0;j<MAX_CHARACTERS;j++){
			if((password[j]>=NUMBER1_ASCII) && (password[j]<=NUMBER9_ASCII)){
				password[j]=((password[j]-NUMBER1_ASCII) * 9 + 1) % 10 + '0';
				numberDigits++;
			} else {
					password[j]=(((password[j]-NUMBER_LETTER_A) + ENCRYPTED_POSITION) % ALPHABET)+ NUMBER_LETTER_A;
					numberLetter++;
			}
		}
		printf("[PASSWORD %d]La password encriptada es: %s\n",i,password);
		printf("Esta formada por %d numeros y %d letras\n\n",numberDigits,numberLetter);
	}
}