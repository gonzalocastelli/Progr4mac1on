#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "matrix.h"

//Libreria MATRICES, diferentes funciones para trabajar con estas matrices





float * productomatrix (float * matA, float * matB)
{
	float  filasA;
	float  filasB;
	float  colsB;
	float  colsA;

	filasA=*(matA-2);
	colsA=*(matA-1);

	filasB=*(matB-2);
	colsB=*(matB-1);		//siguiendo el formato de la libreria obtengo los valores de las cantidades de columnas y filas

	if(((int)colsA)!=((int)filasB))
	{
		printf("Las dimensiones no permiten la multiplicacion de estas matrices\n");
		return NULL;	//devuelvo un puntero a null mosrando que hubo un error
	}

	float * matC;	//reservo lugar para el resultado

	matC=(float *)malloc((((int)filasA*colsB)*(sizeof(float)))+(2*(sizeof(float))));

	if(matC==NULL)
	{
		printf("No hay memoria para devolver el resultado\n");
		return NULL;
	}

	*matC=filasA;
	*(matC+1)=colsB;

	matC+=2;			//cumplo con el formato, y ahora comienzo con la cuenta

	int i,j;		//primero manejo filas y columnas de mat c, en el anidado mas interno del for de matC, trabajo con la mult de matA.matB

	for(i=0;i<(int)filasA;++i)
	{
		for(j=0;j<(int)colsB;++j)
		{

			int k;	//aqui trabajo con la mult
			float result=0;		//aqui esta el resultado parcial de cada mult
			for(k=0;	k<(int)colsB	;++k)
			{

				result+=(*(matA+i*((int)colsA)+k))*(*(matB+k*((int)colsB)+j));
			}
			*(matC+i*((int)colsB)+j)=result;
		}
	}

return matC;

}



















float * restamatrix (float * matrix1, float * matrix2)
{
	//como primera instancia chequeo que las filas y columnas de las matrices 1 y dos sean iguales

	float rowsmat1, colsmat1;
	float rowsmat2, colsmat2;	//Creo 2 variables que sirven para ver cuales son los  tamaños de las matrices que recibo (deben ser iguales)

	rowsmat1=*(matrix1-2);

	colsmat1=*(matrix1-1);


	rowsmat2=*(matrix2-2);			//Recordando que el formato de matrices vienen dos lugares antes donde indican su tamaño

	colsmat2=*(matrix2-1);

	int estadotemp=0;


	if((int)colsmat2!=(int)colsmat1)
	{
		estadotemp=ERROR;
		printf("Las matrices no tienen el mismo numero de columnas\n");
	}

	if((int)rowsmat1!=(int)rowsmat2)
	{						//Modifico la variable estado temporal SI son de distinto tamaño
		estadotemp=ERROR;
		printf("Las MAtrices no tienen el mismo numero de filas\n");
	}


	if(estadotemp==ERROR)
	{
		return NULL;
	}

	if(estadotemp==0)
	{
	 	float * matresult;	//creo puntero a donde devolvere el resultado
		matresult=(float *)malloc((((int)(rowsmat1*colsmat1))*(sizeof(float)))+(2*(sizeof(float))));
		if(matresult==NULL)
		{

			printf("No hay memoria para el resultado\n");
			return NULL;					//Devuelve no si no hay memoria para el resultado

		}

		*matresult=rowsmat1;
		*(matresult+1)=colsmat1;	//aplico el formato

		matresult=matresult+2;		//avanzo al inicio de la matriz en si

		int i,j;

		for(i=0;i<(int)rowsmat1;++i)
		{

			for(j=0;j<(int)colsmat1;++j)
			{

				*(matresult+(i*((int)colsmat1))+j)=(*(matrix1+(i*((int)colsmat1))+j))-(*(matrix2+(i*((int)colsmat1))+j));	//en vez de sumar, resto

			}

		}

		return matresult;

	}

	return NULL; //por si las dudas agrego este ultimo
}

float * sumatrix (float * matrix1, float * matrix2)	//suma dos matrices, devuelve puntero a null si no se pueden sumar porque no son del mismo tamaño o no hay memoria suficiente para dar respuesta
{
	//como primera instancia chequeo que las filas y columnas de las matrices 1 y dos sean iguales

	float rowsmat1, colsmat1;
	float rowsmat2, colsmat2;	//Creo 2 variables que sirven para ver cuales son los  tamaños de las matrices que recibo (deben ser iguales)

	rowsmat1=*(matrix1-2);

	colsmat1=*(matrix1-1);


	rowsmat2=*(matrix2-2);			//Recordando que el formato de matrices vienen dos lugares antes donde indican su tamaño

	colsmat2=*(matrix2-1);



	int estadotemp=0;

	if((int)colsmat2!=(int)colsmat1)
	{
		estadotemp=ERROR;
		printf("Las matrices no tienen el mismo numero de columnas\n");
	}

	if((int)rowsmat1!=(int)rowsmat2)
	{						//Modifico la variable estado temporal SI son de distinto tamaño
		estadotemp=ERROR;
		printf("Las MAtrices no tienen el mismo numero de filas\n");
	}

	if(estadotemp==ERROR)
	{
		return NULL;
	}

	// hasta aca DEBUG
	if(estadotemp==0)
	{
	 	float * matresult;	//creo puntero a donde devolvere el resultado

		matresult=(float *)malloc((((int)(rowsmat1*colsmat1))*(sizeof(float)))+(2*(sizeof(float))));
		if(matresult==NULL)
		{

			printf("No hay memoria para el resultado\n");
			return NULL;					//Devuelve no si no hay memoria para el resultado

		}

		*matresult=rowsmat1;
		*(matresult+1)=colsmat1;	//aplico el formato

		matresult=matresult+2;		//avanzo al inicio de la matriz en si

		int i,j;

		for(i=0;i<(int)rowsmat1;++i)
		{

			for(j=0;j<((int)colsmat1);++j)
			{

				*(matresult+(i*((int)colsmat1))+j)=(*(matrix1+(i*((int)colsmat1))+j))+(*(matrix2+(i*((int)colsmat1))+j));

			}

		}

		return matresult;

	}

	return NULL; //por si las dudas agrego este ultimo
}

// no BUGS from here on
int getfilas (float * matrix)
{
	return ((int)(*(matrix-2)));
}

int getcolumnas (float * matrix)
{
	return ((int)(*(matrix-1)));
}





int getvalmax (float * matrix)
{

	int cantfilas,cantcolumnas;

	cantfilas=(int)*(matrix-2);
	cantcolumnas=(int)*(matrix-1);

	int i,j;
	int k=0;
	for(i=0;i<cantfilas;++i)
	{
		for(j=0;j<cantcolumnas;++j)
		{
			if(k<((int)*(matrix+(i*cantcolumnas)+j)))
			{
				k=(int)*(matrix+(i*cantcolumnas)+j);
			}
		}
	}

return k;
}


int getminval (float * matrix)
{

        int cantfilas,cantcolumnas;

        cantfilas=(int)*(matrix-2);
        cantcolumnas=(int)*(matrix-1);

        int i,j;
        int k=(int)*(matrix);

        for(i=0;i<cantfilas;++i)
        {
                for(j=0;j<cantcolumnas;++j)
                {

                        if(k>((int)*(matrix+(i*cantcolumnas)+j)))
                        {
                                k=(int)*(matrix+((i*cantcolumnas)+j));
                        }

                }
        }

return k;
}




float * makematrix (int rows,int columns)
{

	float * matrix;

	matrix=(float *) malloc(((rows*columns)*(sizeof(float)))+(2*(sizeof(float))));
	if(matrix==NULL)
	{

	printf("Falta de memoria\n");

	return NULL;	//devolvera puntero a null si no hay suficiente memoria
	}


	*matrix=(float) rows;	//el primer numero es rows y el segundo las coumns

	*(matrix+1)=(float) columns;


return (matrix+2);
}

void randomatrix(float * matrix ,int minnum, int maxnum)
{

	srand(time(NULL));	//Para randomizar dependiendo tambien del numero maximo
	int i,j;

	int rows=(int)*(matrix-2);

	int columns=(int)*(matrix-1);


	for(i=0;i<rows;++i)
	{
		for(j=0;j<columns;++j)
		{
			*(matrix+(i*columns)+j)=minnum+(rand()%(maxnum-minnum+1));
		}
	}



}



void printmatrix (float * matrix)
{

	int columnas;
	int filas;

	filas=(int)(*(matrix-2));
	columnas=(int)(*(matrix-1));

	int i,j;	//contadores

	for(i=0; i<filas ; ++i)
	{
		for(j=0;j<columnas;	++j)
		{

			printf("%g    ",*(matrix+i*columnas+j));
		}
		printf("\n");
	}
}


