
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


/*Prototipos de funciones*/

char *create_matrix (int, int, char);
char *create_crazy_matrix (int, int, char, char);

char randomize (char, char);



/*Funcion que crea una matriz de N filas, M columnas, con sus celdas inicializadas en el valor initval*/
/*Devuelve un puntero al inicio de la matriz*/
/*El tipo de elementos de la matriz es char*/

char *create_matrix (int N, int M, char initialval)
{

	char *matrix = NULL;

	if( (matrix = (char *) malloc (N*M)) == NULL)
	{
		printf ("Not enough memory to allocate matrix\n");	/*Exit program if not enough mem*/
		exit (1);
	}

	int i=0;

	for (i=0 ; i<(M*N) ; i++)

	  *(matrix+i) = initialval;			/*Initializes matrix with selected number*/

}

/*Funcion que crea una matriz aleatoria de N filas, M columnas*/
/*Devuelve un puntero al inicio de la matriz*/
/*El tipo de elementos de la matriz es char*/

char *create_crazy_matrix (int M, int N, char minval, char maxval)
{

	char *matrix = NULL;

	if ((matrix = (char *) malloc (M*N)) == NULL)
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

	for (i=0 ; i<(M*N) ; i++, randomnumber = randomize(minval, maxval))
	  *(matrix+i) = randomnumber;

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


#endif
