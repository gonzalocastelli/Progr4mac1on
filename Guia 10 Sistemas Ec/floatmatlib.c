
/*Libreria para manejo de matrices*/

/*Authors: Grupo 1: Castelli, Diaz, Viotti Bozzini*/
/*Date: 3 de junio de 2014*/

/*Libreria para manejo de matrices. Inlcuye funciones para:

	Crear matriz e ingresar componentes por teclado
	Inicializar matriz
	Inicializar matriz en random

	Obtener cantidad de filas y/o columnas de una matriz
	Imprimir matriz en pantalla

	Sumar matrices
	Restar matrices
	Multiplicar o restar por filas
	
	

*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "floatmatlib.h"

#define NEGATIVO 1
#define ERROR 0

#ifndef MATLIB_H

	#define MATLIB_H


/*Funcion que crea una matriz de N filas, M columnas, con sus celdas inicializadas en el valor initval*/
/*Deja dos espacios libres para info de cant de fil y col*/
/*Devuelve un puntero al inicio de la matriz*/


float *mk_matrix (char M, char N, int initialval)
{

	float *matrix = NULL;

	if( (matrix = (float *) malloc (M*N*sizeof(float)+2*sizeof(float))) == NULL) /*Save space for info*/
	{
		printf ("Not enough memory to allocate matrix\n");	/*Exit program if not enough mem*/
		exit (1);
	}

	int i=0;

	*(char *)(matrix+0)= M;		/*Save rows and columns data*/
	*(char *)(matrix+1)= N;

	for (i=2 ; i<((M*N)+2) ; i++)

	  *(matrix+i) = (float)initialval;			/*Initializes matrix with selected number*/

	return (matrix+2);	/*Return pointer + 2*/

}

/*Funcion que crea una matriz aleatoria de N filas, M columnas*/
/*Deja dos espacios libres para info de fil y col*/
/*Devuelve un puntero al inicio de la matriz*/


float *mk_crazy_matrix (char M, char N, int minval, int maxval)
{

	float *matrix = NULL;

	if ((matrix = (float *) malloc ((M*N)+2*sizeof(float))) == NULL)
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

	return (matrix+2);	/*Return pointer + 2 because of rows and columns header*/

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
		state = QERROR;				/*If they differ, function returns error*/

	return state;
}

/*Funcion que multiplica una fila por una constante M*/
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


/*Funcion que resta dos filas entre si*/
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

/*Funcion que crea una matriz y permite ingresar sus componentes por teclado*/
/*Devuelve un puntero a donde comienza la matriz*/
float *type_matrix (char M, char N)
{

	int estado=FINE;
	int *pstate;
	float *matrix = NULL;
	char marcador1=1;
	
	int i=0;
	
	
	pstate = &estado;

	if( (matrix = (float *) malloc (M*N*sizeof(float)+2*sizeof(float))) == NULL) /*Save space for info*/
	{
		printf ("Not enough memory to allocate matrix\n");	/*Exit program if not enough mem*/
		exit (1);
	}

	

	*(char *)(matrix+0)= M;		/*Save rows and columns data*/
	*(char *)(matrix+1)= N;

	printf ("\nPor favor, introduzca los coeficientes\n\n");


	for (i=2 ; i<((M*N)+2) ; i++)
	{
		
		printf ("N [%d]: ", marcador1++);		/*Print visual al llenar la matriz*/
	  	*(matrix+i) = getmynumber (pstate);

		if (estado == ERROR)
			{
			printf ("Error al ingresar el numero\n");		/*Initializes matrix with typed number*/
			exit (1);
			}
									
	}
	
	return (matrix+2);	/*Return pointer + 2*/

}

/*Funcion que me permite ingresar datos por teclado*/
/*Devuelve un float con el numero tecleado*/
float getmynumber (int * pstate)		//recibe donde quiere que guarde el valor terminado, y la variable estado
{


float numero=0;	//variables locales de la funcion
float final=0;
unsigned int entero=0;
unsigned int contador=0;
unsigned int ingresoadecimal=0;	//esta define si se introdujo un punto decimal o no
unsigned int c;
unsigned int signo=0;	//define el signo

while ((c=getchar())!=('\n'))	//queda en el while hasta que se aprete enter

	{
	if ((c>=0x30)&&(c<=0x39))	//si se tecleo un numero, viene aca
	{
		numero=(numero*10+(c-0x30));  //hace los calculos y corrimientos necesarios
			if (ingresoadecimal)
				contador=contador++;  //si llegue aca es porque se introdujo el punto decimal. Este contador me permitira luego reducir lo ingresado a la forma "0.(lo ingresado)"
	}	

	if (c=='-')	//se tecleo el signo menos
		if (numero==0)
			signo=NEGATIVO;	//lo introdujeron antes de poner un numero, es correcto!
		else
			*pstate=ERROR;	//el signo menos vino despues de algun numero. Es incorrecto. Se pasa a un estado de error.


		if (c=='.')	//el numero es con decimales!
		{
			if (ingresoadecimal==0)
			{
				entero=numero;	//debo liberar...
				numero=0;	//...y resetear la variable numero para que los calculos sean correctos
				ingresoadecimal=1;	//marco que estamos en "modo decimal". Si alguien ingresa un punto nuevamente, el resultado sera incorrecto
			}
			else
				*pstate=ERROR;
		}		

		if ((c!='.')&&(c!='-')&&(c!=0x30)&&(c!=0x31)&&(c!=0x32)&&(c!=0x33)&&(c!=0x34)&&(c!=0x35)&&(c!=0x36)&&(c!=0x37)&&(c!=0x38)&&(c!=0x39))	//Si lo tecleado no es un numero, ni un punto, ni un menos... error!

			*pstate=ERROR;


	}

while (contador>0)	//ya se tecleo el numero y disponemos de su parte entera y decimal. Ajustamos la parte decimal y sumamos.
	{
		numero=(numero/10);	//ajusto a 0.(parte decimal)
		contador--;
	}


final=(entero+numero);	//sumo la parte decimal y la entera, ya tengo el numero que se tecleo


if (signo)
	final=-final;	//ultimo detalle: me fijo si se introdujo el - antes del numero

return final;

}


#endif


