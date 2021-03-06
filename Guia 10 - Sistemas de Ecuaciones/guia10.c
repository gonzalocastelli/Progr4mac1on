#include <stdio.h>
#include <stdlib.h>
#include "floatmatlib.c"

#define MAXINCOG 100
#define ERROR 0
#define FINE 1
#define NEGATIVO 1


/*Programa que calcula sistemas de ecuaciones*/

int main (void)

{

	/*Definicion de variables y punteros*/

	int i=0;
	int j=0;
	int k=0;
        int r=0;
	float valor, valor2;	
	char filas, columnas; 
	float cant_incog =0;
     	float *ptr;
	float *solutions = NULL;
	int estado = FINE;
	int *pstate;

	pstate = &estado;

        /*-----------------------------*/

        
	if ((solutions = (float *) malloc ( MAXINCOG * sizeof(float))) == NULL)		/*Guardo espacio para el vector solucion*/
		{
			
			printf ("Not enough memory\n");
			exit (1);	

		}


	printf ("\n\n Programa que resuelve sistemas de ecuaciones. No acepta dos o mas ecuaciones que sean multiplos entre si. Si algun resultado es inf significa que no hay solucion al sistema ingresado.\n\n");


	printf ("\n\nPor favor, introduzca el numero de ecuaciones con las que desea hacer el sistema:");

		
	cant_incog = getmynumber (pstate);

	if ((estado==ERROR) || (cant_incog<0.01))
		{
		printf ("Error al introducir el numero de ecuaciones. Recuerde que debe ser un numero entero positivo\n");
		exit (1);
		}
	

	ptr = type_matrix (cant_incog,cant_incog + 1);
	

	printf ("\n\nUsted ha ingresado la matriz: \n");

	printm (ptr);
	printf ("\n");
	
	columnas = columninfo (ptr);
	filas = rowinfo (ptr);			/*Obtiene info de cols y fils para poder triangular*/



        for (j=0 ; j<columnas ; j++)
	{
	for (i=1 ; i<filas-j ; i++)
	{
	valor = *(ptr+j*columnas+j);
	valor2 = *(ptr+(i+j)*columnas+j);		/*Triangula la matriz*/

	multfil (j, valor2, ptr);
	multfil (i+j, valor , ptr);
	restfil (i+j, j, ptr);
	multfil (j, 1.0/valor2 , ptr);
	}
        }


	for (i=filas-1, k=0 ; i>=0 ; i--, k++)
	{

		valor = 0;

		for (j=i , r=k-1 ; j<(columnas-2) ; j++, r--)
		{

		valor += (*(ptr+i*columnas+(j+1)) * (*(solutions+r)));					/*Core Solution*/	/*Despeja a partir de la matriz triangulada*/

		}
	
		*(solutions+k) = ((*(ptr+i*columnas+(columnas-1)) - valor) / *(ptr+i*columnas+i) );

	}
	
	r=1;
	k=cant_incog;

	while (k>0)							/*Muestro resultado*/
	printf ("Solucion %d = %g\n", r++, *(solutions+(--k)));

	printf ("\n");
	
        return 0;
}


