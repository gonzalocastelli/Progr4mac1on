#ifndef matrix__h
#define matrix__h


//La devolucion de punteros a NULL implica un error interno de la funcion, explicado con un print

float * makematrix (int rows, int column);  //creara una matriz con los elementos pedidos y en los primeros dos n° dara la cant de rows y columns 
void randomatrix (float * matrix,int minnum,int maxnum);        //se llamara si se quiere inicializar con numeros random y si no, flaco llenala vos
float * sumatrix (float * matrix1, float * matrix2);     //suma dos matrices, devuelve puntero a null si no se pueden sumar porque no son del mismo tamaño o no hay memoria suficiente para dar respuesta
float * restamatrix (float * matrix1, float * matrix2); //lo mismo que la de suma, pero con resta
int getvalmax (float * matrix);
int getminval (float * matrix);
int getfilas (float * matrix);
int getcolumnas (float * matrix);               //estas 4 funciones devuelven lo pedido sobre matrices que estan en el mismo formato de esta libreria
float * productomatrix(float * matA, float * matB);     //el programa hara: A.B=matC matC es el resultado
void printmatrix (float * matrix);	//imprime una matriz en el stdout



#define ERROR 1


#endif
