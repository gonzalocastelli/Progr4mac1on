#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "floatmatlib.h"

float *solve2x2 (float *);
int determinante (float *);

int main (void)
{


	float *mimatriz = NULL;
	float *resultado = NULL;

	mimatriz = mk_matrix (2, 3, 1);

	*(mimatriz) = 2;
	*(mimatriz+1) = 3;
	*(mimatriz+2) = 7;
	*(mimatriz+3) = 6;
	*(mimatriz+4) = 16;
	*(mimatriz+5) = 2;

	printm (mimatriz);

	resultado = solve2x2 (mimatriz);
	
	printf ("\nResultado:\n");
	printm (resultado);
	

}



float *solve2x2 (float *coeficientes)
{

	float *resultado = NULL;
	float *auxmatrix = NULL;

	int detdenominador=0;
	int detnumerador=0;

	auxmatrix = mk_matrix (2, 2, 0);
	resultado = mk_matrix (1, 2, 0);

	*auxmatrix = *(coeficientes);
	*(auxmatrix+1) = *(coeficientes+1);
	*(auxmatrix+2) = *(coeficientes+3);
	*(auxmatrix+3) = *(coeficientes+4);

	detdenominador = determinante (auxmatrix);

	*auxmatrix = *(coeficientes+2);
	*(auxmatrix+2) = *(coeficientes+5);

	
	detnumerador = determinante (auxmatrix);

	*resultado = (detnumerador/(detdenominador*1.0));

	*auxmatrix = *(coeficientes);
	*(auxmatrix+1) = *(coeficientes+2);
	*(auxmatrix+2) = *(coeficientes+3);
	*(auxmatrix+3) = *(coeficientes+5);

	detnumerador = determinante (auxmatrix);

	*(resultado+1) = (detnumerador/(detdenominador*1.0));

	return resultado;

	
}







int determinante (float *matrix)
{

	char rows; 
	char columns;

	int i, j;

	int determinanteparcial1 = 1;
	int determinanteparcial2 = 1;
	int determinanteparcial3 = 1;
	
	rows = rowinfo (matrix);
	columns = columninfo (matrix);

	if (rows != columns)
	 {
		printf ("Matrix is not square. Cannot make operation.\n");
		exit (1);
	 }

	else
	
	{

		for (i=0, j=0 ; i<rows ; i++ , j++)
		{
			determinanteparcial1 *= (*(matrix+(i*columns)+j));	/*PRIMER CRUZADA*/
		}

		

		for (i=1, j=0 ; i<rows ; i++ , j++)
		{
			determinanteparcial2 *= (*(matrix+(i*columns)+j));	/*SEGUNDA CRUZADA*/
		}
		
		determinanteparcial2 *= (*(matrix+columns-1));
		determinanteparcial1 += determinanteparcial2;
		determinanteparcial2=1;

	

		for (i=2, j=0 ; i<rows ; i++ , j++)
		{
			determinanteparcial2 *= (*(matrix+(i*columns)+j));	/*TERCER CRUZADA*/
		}
		
		determinanteparcial2 *= *(matrix+columns-2);
		determinanteparcial2 *= *(matrix+(2*columns)-1);
		determinanteparcial1 += determinanteparcial2;
		determinanteparcial2=1;

		

		



		for (i=0, j=(columns-1) ; i<rows ; i++ , j--)
		{
			determinanteparcial2 *= (*(matrix+(i*columns)+j));	/*PRIMER CRUZADA INVERSA*/
		}

		determinanteparcial3 = determinanteparcial2;
		determinanteparcial2 = 1;

		

		for (i=1, j=(columns-1) ; i<rows ; i++ , j--)
		{
			determinanteparcial2 *= (*(matrix+(i*columns)+j));	/*SEGUNDA CRUZADA INVERSA*/
		}
		

		determinanteparcial2 *= (*(matrix));
		determinanteparcial3 += determinanteparcial2;
		determinanteparcial2=1;


		for (i=2, j=(columns-1) ; i<rows ; i++ , j--)
		{
			determinanteparcial2 *= (*(matrix+(i*columns)+j));	/*TERCER CRUZADA INVERSA*/
		}

		determinanteparcial2 *= *(matrix+1);
		determinanteparcial2 *= *(matrix+columns);
		determinanteparcial3 += determinanteparcial2;
		determinanteparcial2=1;		


		return (determinanteparcial1 - determinanteparcial3);
		
		
	}
		
}
