#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "floatmatlib.h"

float *solve2x2 (float *);
float *solve3x3 (float *);
int determinante (float *);


/*Funcion que resuelve sistemas de ecuaciones de 2x2 por metodo de Cramer*/
/*RECIBE: un puntero al arreglo que contiene los coeficientes*/
/*DEVUELVE: un puntero a un vector resultado*/

float *solve2x2 (float *coeficientes)
{

	float *resultado = NULL;
	float *auxmatrix = NULL;

	int detdenominador=0;
	int detnumerador=0;

	auxmatrix = mk_matrix (2, 2, 0);	/*Creo arreglos auxiliares*/
	resultado = mk_matrix (1, 2, 0);

	*auxmatrix = *(coeficientes);
	*(auxmatrix+1) = *(coeficientes+1);
	*(auxmatrix+2) = *(coeficientes+3);	/*Copio coeficientes*/
	*(auxmatrix+3) = *(coeficientes+4);

	detdenominador = determinante (auxmatrix);	/*Calculo el determinante "denominador" de cramer*/

	*auxmatrix = *(coeficientes+2);
	*(auxmatrix+2) = *(coeficientes+5);	

	
	detnumerador = determinante (auxmatrix);	/*Calculo el determinante "numerador" de la formula para obtener el valor de X*/

	*resultado = (detnumerador/(detdenominador*1.0));	/*Guardo el valor de x en el vector*/

	*auxmatrix = *(coeficientes);
	*(auxmatrix+1) = *(coeficientes+2);
	*(auxmatrix+2) = *(coeficientes+3);		/*Actualizo matriz auxiliar para calcular Y*/
	*(auxmatrix+3) = *(coeficientes+5);

	detnumerador = determinante (auxmatrix);	

	*(resultado+1) = (detnumerador/(detdenominador*1.0));	/*Guardo el valor de y en el vector*/

	return resultado;

	
}

/*Funcion que resuelve sistemas de ecuaciones de 3x3 por metodo de Cramer*/
/*RECIBE: un puntero al arreglo que contiene los coeficientes*/
/*DEVUELVE: un puntero a un vector resultado*/

float *solve3x3 (float *coeficientes)
{

	int i = 0;
	int j = 0;

	float *matrixaux1= NULL;	/*Creo matrices auxiliares para armar los determinantes que necesito calcular*/
	float *matrixaux2= NULL;
	float *resultado= NULL;

	int detdenom=0;
	int detnum=0;

	matrixaux1 = mk_matrix (3,3,0);
	matrixaux2 = mk_matrix (3,3,0);		/*MATRIXAUX1 ALOJARA EL DETERMINANTE DEL DENOM*/
	resultado = mk_matrix (1,3,0);
	
	for (i=0 ; i<3 ; i++)
	{
		for (j=0; j<3 ; j++)

			*(matrixaux1+(3*i)+j) = *(coeficientes+(4*i)+j);

	}

	detdenom = determinante (matrixaux1);

	for (i=0 ; i<9 ; i++)
	{

			*(matrixaux2+i) = *(matrixaux1+i);	/*COPIO MATRIZ DEL DENOM Y EN BASE A ELLA ARMO LA DEL NUM*/

	}
	
	for (i=0 ; i<3 ; i++)
	{

			*(matrixaux2+(3*i)) = *(coeficientes+(4*i)+3);	/*agrego columna j,k,l*/

	}
	

	detnum = determinante (matrixaux2);

	*(resultado) = (detnum/(detdenom*1.0));

	for (i=0 ; i<9 ; i++)
	{

			*(matrixaux2+i) = *(matrixaux1+i);	/*COPIO MATRIZ DEL DENOM Y EN BASE A ELLA ARMO LA DEL NUM*/

	}

	for (i=0 ; i<3 ; i++)
	{

			*(matrixaux2+(3*i)+1) = *(coeficientes+(4*i)+3);	/*agrego columna j,k,l*/

	}

	detnum = determinante (matrixaux2);

	*(resultado+1) = (detnum/(detdenom*1.0));

	for (i=0 ; i<9 ; i++)
	{

			*(matrixaux2+i) = *(matrixaux1+i);	/*COPIO MATRIZ DEL DENOM Y EN BASE A ELLA ARMO LA DEL NUM*/

	}

	for (i=0 ; i<3 ; i++)
	{

			*(matrixaux2+(3*i)+2) = *(coeficientes+(4*i)+3);	/*agrego columna j,k,l*/

	}

	detnum = determinante (matrixaux2);

	*(resultado+2) = (detnum/(detdenom*1.0));

	return resultado;

}
	




/*Funcion que calcula el determinante de una matriz de 2x2 o 3x3 por metodo de sarrus*/
/*RECIBE un puntero al inicio de la matriz*/
/*DEVUELVE: error si la matriz no es cuadrada. Si es cuadrada, devuelve su determinante*/

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
