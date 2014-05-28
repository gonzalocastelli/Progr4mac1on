#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "floatmatlib.h"
#include "sistemasdeecuaciones.h"

//def de funciones

float * getmat3x3 (void);
float * getmat2x2 (void);
float getnumber (int * pstate);
#define NEGATIVO 20
#define DOSPORDOS	4
#define TRESPORTRES	9
#ifndef ERROR
#define ERROR 1
#endif

int main (void)
{
	int estado=0;

	int * pestado;

	pestado=&estado;

	printf("¿Desea hacer un sistema de ecuaciones de:\n(a)2x2?\n(b)3x3?\n");


	do{

		*pestado=0;

		char c=0;

		c=getchar();

                                        float * matcoef;
                                        float * matresults;


		switch(c)
		{
			case 'a':
			case 'A':
					matcoef=getmat2x2();

					printf("Su matriz es la siguiente:\n");
					printm(matcoef);

					matresults = solve2x2 (matcoef);
					printm (matresults);

					

					break;	//ACA SE VA A PONER LA FUNCION QUE HACE EL 2X2


			case 'B':
			case 'b':
					matcoef=getmat3x3();
					printf("Su matriz es la siguiente:\n");
					printm(matcoef);
					
					matresults = solve3x3 (matcoef);
					printm (matresults);

					break;//aca lo que hace 3x3
			default:	printf("No existe esta opcion, recuerde que si ud. envio un espacio como primer caracter, no sera correcto. Ingrese su opcion nuevamente:\n");
					if(c!='\n')
					{	while(getchar()!='\n');	}
					*pestado=ERROR;
					break;

		}
	}
	while(*pestado==ERROR);


return 0;
}


float * getmat3x3 (void)
{
	int estadotemp=0;
	int * pestadotemp;

	pestadotemp=&estadotemp;

	char filas=3;
	char columnas=4;

	float * coeficientes;

	coeficientes=mk_matrix(filas,columnas,0);
	printf("El formato de la ecuacion es:\n(1)x+(2)y+3(z)=(4)\n(5)x+(6)y+(7)z=(8)\n(9)x+(10)y+(11)z=(12)\n");
	int i;
	float j;

	        for(i=0;i<12;++i)
        {

                do{
                        estadotemp=0;
                        printf("(%d)=?\n",i+1);
                        j=getnumber(*pestadotemp);
                        if(estadotemp==ERROR)
                        {
                        printf("Introduccion incorrecta del coeficiente.\n");
                        }
                        if(estadotemp==0)
                        {
                                *(coeficientes+i)=j;
                        }

                }
                while(estadotemp);
        }

return coeficientes;
}









float * getmat2x2(void)				//generara una matriz de 2x3 con como si estuviesen las ecuaciones
{
	int estadotemp=0;
	int * pestadotemp;

	pestadotemp=&estadotemp;

	char filas=2;
	char columnas=3;		//creo variables tipo int con la cantidad de filas y columnas, para luego pedir el espacio

	float * coeficientes;



	coeficientes=mk_matrix(filas,columnas,0);

	printf("El formato de la ecuacion es:\n (1)x+(2)y=(3)\n(4)x+(5)y=(6)\n");
	int i;
	float j;

	for(i=0;i<6;++i)
	{

		do{
			estadotemp=0;
			printf("(%d)=?\n",i+1);
			j=getnumber(*pestadotemp);
			if(estadotemp==ERROR)
			{
			printf("Introduccion incorrecta del coeficiente.\n");
			}
			if(estadotemp==0)
			{
				*(coeficientes+i)=j;
			}

		}
		while(estadotemp);
	}

return coeficientes;
}







float getnumber (int * pstate)		//recibe donde quiere que guarde el valor terminado, y la variable estado
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
