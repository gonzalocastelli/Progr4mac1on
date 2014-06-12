
#ifndef FLOAT_MATLIB_H

	#define FLOAT_MATLIB_H

/*Libreria para manejo de matrices*/

/*Authors: Grupo 1: Castelli, Diaz, Viotti Bozzini*/

/*Libreria para manejo de matrices. Inlcuye funciones para:

	Crear e inicializar matriz
	Inicializar matriz en random

	Obtener cantidad de filas y/o columnas de una matriz
	Imprimir matriz en pantalla

	Sumar matrices
	Restar matrices
	Multiplicar matrices
	y mas...

*/


/*Constantes*/

#define FINE 1
#define QERROR 0


/*Prototipos de funciones*/

float *mk_matrix (char, char, int);
float *mk_crazy_matrix (char, char, int, int);

float randomize (float, float);

char rowinfo (float*);
char columninfo (float*);
void printm (float *);

float *sumarmatrices (float *, float * , float *);
float *restarmatrices (float *, float*, float*);

char checkdimentions (float *, float *);

void multfil (int fila, float M, float *matrix);
void restfil (int fila1, int fila2, float *matrix);

float *type_matrix (char M, char N);
float getmynumber (int *);

#endif
