
/*Libreria para manejo de matrices*/

/*Authors: Grupo 1: Castelli, Diaz, Viotti Bozzini*/

/*Libreria para manejo de matrices. Inlcuye funciones para:

	Crear matriz
	Inicializar matriz
	Inicializar matriz en random

	Obtener cantidad de filas y/o columnas de una matriz
	Imprimir matriz en pantalla

	Sumar matrices
	Restar matrices
	Multiplicar matrices
	Calcular determinante

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifndef MATLIB_H

	#define MATLIB_H

/*Constantes*/

#define FINE 1
#define ERROR 0

/*Prototipos de funciones*/

float *mk_matrix (char, char, float);
float *mk_crazy_matrix (char, char, float, float);

float randomize (float, float);

char rowinfo (float*);
char columninfo (float*);
void printm (float *);

float *sumarmatrices (float *, float * , float *);
float *restarmatrices (float *, float*, float*);

char checkdimentions (float *, float *);


/*Funcion que crea una matriz de N filas, M columnas, con sus celdas inicializadas en el valor initval*/
/*Deja dos espacios libres para info de cant de fil y col*/
/*Devuelve un puntero al inicio de la matriz*/
/*El tipo de elementos de la matriz es char*/

float *mk_matrix (char N, char M, float initialval)
{

	float *matrix = NULL;

	if( (matrix = (float *) malloc ((N*M)+2)) == NULL) /*Save space for info*/
	{
		printf ("Not enough memory to allocate matrix\n");	/*Exit program if not enough mem*/
		exit (1);
	}

	int i=0;

	*(char *)(matrix+0)= N;		/*Save rows and columns data*/
	*(char *)(matrix+1)= M;

	for (i=2 ; i<((M*N)+2) ; i++)

	  *(matrix+i) = initialval;			/*Initializes matrix with selected number*/

	return (matrix+2);	/*Return pointer + 2*/

}

/*Funcion que crea una matriz aleatoria de N filas, M columnas*/
/*Deja dos espacios libres para info de fil y col*/
/*Devuelve un puntero al inicio de la matriz*/
/*El tipo de elementos de la matriz es char*/

float *mk_crazy_matrix (char M, char N, float minval, float maxval)
{

	float *matrix = NULL;

	if ((matrix = (float *) malloc ((M*N)+(2*(sizeof(float))))) == NULL)	//also all the other places where you have +2
	{
		printf ("Not enough memory to allocate matrix\n");	/*No memory*/
		exit (1);
	}

	if (maxval <= minval)
	{

		printf ("Minimum value is higher than maximum\n");	/*Error message*/
		exit (1);
	}


	int i=0;
	float randomnumber = 0;

	*(char *)(matrix+0) = M;
	*(char *)(matrix+1) = N;


	for (i=2 ; i<((M*N)+2) ; i++)
	{
	  randomnumber = randomize(minval, maxval);
	  *(matrix+i) = randomnumber;
	}

	return (matrix+2);	/*Return pointer + 2 because of rows and columns info*/

}


/*Funcion anexa que crea numeros aleatorios*/
/*RECIBE: valor minimo y maximo*/
/*DEVUELVE: Numero aleatorio comprenido entre el minimo y maximo*/


float randomize (float minval, float maxval)
{

	int randomnumber=0;
	static int seed=0;

	if (seed == 0)
		{
		srand (time(NULL));	/*Seed*/ /*Only implants when function is called for the first time*/
		seed++;
		}	

	randomnumber = ( (rand() % ((int)maxval-(int)minval)) + (int)minval);	/*Randomize according to minval and maxval*/

	return ((float)randomnumber);

}



/*Funcion que recibe un puntero a una matriz y devuelve su cantidad de filas,
 siempre y cuando dicha matriz haya sido creada por mkmatrix*/

char rowinfo (float *matrix)
{

	char rows=0;

	rows = *(char *)(matrix-2);

	return rows;

}

/*Funcion que recibe un puntero a una matriz y devuelve su cantidad de columnas,
siempre y cuando la misma haya sido creada por mk_matrix*/

char columninfo (float *matrix)
{

	char columns=0;

	columns = *(char *)(matrix - 1);

	return columns;

}

/*Funcion que imprime matriz en pantalla*/
/*RECIBE el puntero donde comienza la matriz, que debe estar creada por mk_matrix*/

void printm (float *matrix)
{

	char rows=0;
	char columns=0;

	rows = rowinfo (matrix);
	columns = columninfo (matrix);

	printf ("FILAS: %d\n", rows);
	printf ("COLUMNAS: %d\n", columns);
	
	int i=0;
	int j=0;

	for (i=0 ; i<rows ; i++)
	{
		for (j=0 ; j<columns ; j++)
			printf ("%g\t", *(matrix++));

		printf ("\n");
	}


}


/*CORE CALCULTAION*/


/*Funcion que suma dos matrices*/
/*RECIBE los punteros donde comienzan las matrices y un puntero donde se escribira la info y la matriz resultado*/
/*DEVUELVE: Puntero donde empieza la matriz con los datos*/
/*CONSEJO: el puntero que retorna la funcion puede ser el mismo que el que recibe la funcion*/

float *sumarmatrices (float *matrix1 , float *matrix2 , float *allocation)
{

	float suma;

	char M=0;
	char N=0;

	char i=0;

	char state=0;

	if ((state = checkdimentions (matrix1, matrix2)) == FINE )
	{

		M=rowinfo(matrix1);
		N=columninfo(matrix1);		/*Take row and column sample (they are the same, we take it from the first)*/

		*(char *)allocation = M;
		*(char *)(allocation+1) = N;		/*Save row and column info*/

		allocation = allocation+2;	/*Place pointer where matrix starts*/

		for (i=0 ; i<(M*N) ; i++)
		{
			suma = ( *(matrix1 + i) + *(matrix2 + i) );
			*(allocation+i) = suma;
		}

		return (allocation);

	}

	else
	{

		printf ("Matrix' dimentions are different\n");
		exit (1);

	}
}


/*Funcion que resta dos matrices*/
/*RECIBE: Punteros al inicio de las matrices y puntero a partir del cual se creara la info de la matriz y la matriz resultado*/
/*Devuelve: puntero donde empieza la matriz con los datos*/

float *restarmatrices (float *matrix1 , float *matrix2 , float *allocation)
{

	float resta;

	char M=0;
	char N=0;

	char i=0;

	char state=0;

	if ((state = checkdimentions (matrix1, matrix2)) == FINE )
	{

		M=rowinfo(matrix1);
		N=columninfo(matrix1);		/*Take row and column sample (they are the same, we take it from the first)*/

		*(char *)allocation = M;
		*(char *)(allocation+1) = N;		/*Save row and column info*/

		allocation = allocation+2;	/*Place pointer where matrix starts*/

	
		for (i=0 ; i<(M*N) ; i++)
		{
			resta = ( *(matrix1 + i) - *(matrix2 + i) );
			*(allocation+i) = resta;
		}

		return (allocation);
	}

	else
	{

		printf ("Matrix' dimentions are different\n");
		exit (1);

	}
}

/*Funcion que compara las dimensiones de dos matrices*/
/*RECIBE los punteros al comienzo de ambas matrices*/
/*DEVUELVE 1 si tienen igual dimension, 0 si tienen distinta dimension*/

char checkdimentions (float *matrix1 , float *matrix2)
{

	char state = FINE;

	char row1, row2, column1, column2;

	row1 = rowinfo (matrix1);
	column1 = columninfo (matrix1);		/*Extract info from each matrix*/
	row2 = rowinfo (matrix2);
	column2 = columninfo (matrix2);

	if ((row1 != row2) || (column1 != column2))
		state = ERROR;				/*If they differ, function returns error*/

	return state;
}


#endif
