
/*Libreria para manejo de matrices*/

/*Authors: Grupo 1: Castelli, Diaz, Viotti Bozzini*/

/*Libreria para manejo de matrices. Inlcuye funciones para:

	Crear matriz
	Inicializar matriz
	Inicializar matriz en random

	Obtener cantidad de filas y/o columnas de una matriz
	Valor maximo
	Valor Minimo

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

char *mk_matrix (char, char, char);
char *mk_crazy_matrix (char, char, char, char);

char randomize (char, char);

char rowinfo (char*);
char columninfo (char*);

void sumarmatrices (char *, char * , char *);
char checkdimentions (char *, char *);


/*Funcion que crea una matriz de N filas, M columnas, con sus celdas inicializadas en el valor initval*/
/*Deja dos espacios libres para info de cant de fil y col*/
/*Devuelve un puntero al inicio de la matriz*/
/*El tipo de elementos de la matriz es char*/

char *mk_matrix (char N, char M, char initialval)
{

	char *matrix = NULL;

	if( (matrix = (char *) malloc ((N*M)+2)) == NULL) /*Save space for info*/
	{
		printf ("Not enough memory to allocate matrix\n");	/*Exit program if not enough mem*/
		exit (1);
	}

	int i=0;

	*(matrix+0)= N;		/*Save rows and columns data*/
	*(matrix+1)= M;

	for (i=2 ; i<((M*N)+2) ; i++)

	  *(matrix+i) = initialval;			/*Initializes matrix with selected number*/

	return (matrix+2);	/*Return pointer + 2*/

}

/*Funcion que crea una matriz aleatoria de N filas, M columnas*/
/*Deja dos espacios libres para info de fil y col*/
/*Devuelve un puntero al inicio de la matriz*/
/*El tipo de elementos de la matriz es char*/

char *mk_crazy_matrix (char M, char N, char minval, char maxval)
{

	char *matrix = NULL;

	if ((matrix = (char *) malloc ((M*N)+2)) == NULL)
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
	int randomnumber = 0;

	*(matrix+0) = M;
	*(matrix+1) = N;

	for (i=2 ; i<((M*N)+2) ; i++, randomnumber = randomize(minval, maxval))
	  *(matrix+i) = randomnumber;

	return (matrix+2);	/*Return pointer + 2 because of rows and columns info*/

}


/*Funcion anexa que crea numeros aleatorios*/
/*RECIBE: valor minimo y maximo*/
/*DEVUELVE: Numero aleatorio comprenido entre el minimo y maximo*/

char randomize (char minval, char maxval)
{

	int randomnumber=0;

	srand (time(NULL));	/*Seed*/

	randomnumber = ( (rand() % (maxval-minval)) + minval);	/*Randomize according to minval and maxval*/

	return randomnumber;

}


/*Funcion que recibe un puntero a una matriz y devuelve su cantidad de filas,
 siempre y cuando dicha matriz haya sido creada por mkmatrix*/

char rowinfo (char *matrix)
{

	int rows=0;

	rows = *(matrix-2);

	return rows;

}

/*Funcion que recibe un puntero a una matriz y devuelve su cantidad de columnas,
siempre y cuando la misma haya sido creada por mk_matrix*/

char columninfo (char *matrix)
{

	int columns=0;

	columns = *(matrix - 1);

	return columns;

}

/*CORE CALCULTAION*/


/*Funcion que suma dos matrices*/
/*RECIBE los punteros donde comienzan las matrices y un puntero donde se escribira la matriz resultado*/
/*DEVUELVE: NADA*/

void sumarmatrices (char *matrix1 , char *matrix2 , char *allocation)
{

	char suma;

	char M=0;
	char N=0;

	char i=0;

	char state=0;

	if ((state = checkdimentions (matrix1, matrix2)) == FINE )
	{

		M=rowinfo(matrix1);
		N=columninfo(matrix1);		/*Take row and column sample (they are the same, we take it from the first)*/

		for (i=0 ; i<(M*N) ; i++)
		{
			suma = ( *(matrix1 + i) + *(matrix2 + i) );
			*(allocation+i) = suma;
		}

	}

	else
	{

		printf ("Matrix' dimentions are different\n");
		exit (1);

	}
}


/*Funcion que resta dos matrices*/
/*RECIBE: Punteros al inicio de las matrices y puntero a partir del cual se creara la matriz resultado*/
/*Devuelve: NADA*/

void restarmatrices (char *matrix1 , char *matrix2 , char *allocation)
{

	char resta;

	char M=0;
	char N=0;

	char i=0;

	char state=0;

	if ((state = checkdimentions (matrix1, matrix2)) == FINE )
	{

		M=rowinfo(matrix1);
		N=columninfo(matrix1);		/*Take row and column sample (they are the same, we take it from the first)*/

		for (i=0 ; i<(M*N) ; i++)
		{
			resta = ( *(matrix1 + i) + *(matrix2 + i) );
			*(allocation+i) = suma;
		}

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

char checkdimentions (char *matrix1 , char *matrix2)
{

	char state = FINE;

	char row1 = *(matrix1 - 2);
	char column1 = *(matrix1 - 1);

	char row2 = *(matrix2 - 2);
	char column2 = *(matrix2 - 1);	/*Extract info from each matrix*/

	if ((row1 != row2) && (column1 != column2))
		state = ERROR;				/*If they differ, function returns error*/

}

#endif
