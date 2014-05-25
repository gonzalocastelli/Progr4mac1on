#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINIMO 45
#define	MINIMOSTR "MINIMO"
#define MAXIMO 101
#define	MAXIMOSTR "MAXIMO"
int main (void)
{

	int i;

	srand(time(NULL));	/*Semilla*/

	printf ("Ten random numbers from MINIMOSTR to MAXIMOSTR\n");

	for (i=0 ; i<10 ; i++)
		printf ("%d\n", ((rand() % (MAXIMO-MINIMO+1))+MINIMO));

	return 0;


}



