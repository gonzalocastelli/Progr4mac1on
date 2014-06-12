#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "floatmatlib.c"


int newdet (float *ptr);
void multfil (int fila, float M, float *matrix);
void restfil (int fila1, int fila2, float *matrix);



void main (void)
{

	int i=0;
	int j=0;
	int k=0;
        int r=0;
	float valor;
	float valor2;
	char columnas;
        char filas;
	float *ptr;
	

	float *solutions = NULL;

	if ((solutions = (float *) malloc (2 * sizeof(float))) == NULL)
		{
			
			printf ("Not enough mem\n");
			exit (1);	

		}


	
	ptr = mk_crazy_matrix (5,6,1,5);

	printm (ptr);
	printf ("\n");
	
	columnas = columninfo (ptr);
	filas = rowinfo (ptr);



        for (j=0 ; j<columnas ; j++)
	{
	for (i=1 ; i<filas-j ; i++)
	{
	valor = *(ptr+j*columnas+j);
	valor2 = *(ptr+(i+j)*columnas+j);		/*CORE TRIANGULATION*/

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

		valor += (*(ptr+i*columnas+(j+1)) * (*(solutions+r)));

		}
	
		*(solutions+k) = ((*(ptr+i*columnas+(columnas-1)) - valor) / *(ptr+i*columnas+i) );

	}
	
	i=0;

	while (i<7)	
	printf ("Soluciones de x en adelante = %g\n", *(solutions+(i++)));
	
	printm (ptr);
	printf ("\n");
}



void multfil (int fila, float M, float *matrix)
{

	int j=0;
	char columnas;
	columnas = columninfo (matrix);

	for (j=0 ; j<columnas ; j++)
	{			
		(*(matrix + fila*columnas + j)) *= M;
	
	}

}



void restfil (int fila1, int fila2, float *matrix)
{

		int j=0;
	char columnas;
	columnas = columninfo (matrix);

	for (j=0 ; j<columnas ; j++)
	{
		
		(*(matrix + fila1*columnas + j)) -= (*(matrix + fila2*columnas + j));
		

	}

}

