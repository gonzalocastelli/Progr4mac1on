
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
#include <alloc.h>

#ifndef MATLIB_H

	#define MATLIB_H

	char *create_matrix (int, int, char);

#endif




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

