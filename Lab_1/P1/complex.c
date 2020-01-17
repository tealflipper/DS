/*Dado que un n�mero complejo tiene la forma de x =a + ib, para realizar operaciones sobre ellos,
  debemos crear un nuevo tipo que lo soporte, ya que los que existen (int, long, char, float, 
  double, etc.) no lo permiten. Por lo anterior, emplearemos una estructura.*/

#include <stdio.h>
#include <stdlib.h>

 typedef struct COMPLEX complex;  /*Tipo complex*/
 struct COMPLEX
 {
   double fReal;  /*Parte real*/
   double fImg;   /*Parte imaginaria*/
 };
 
 complex scSuma (complex a, complex b);
 complex scProductoConEscalar (complex a, double c);
 
 int main ()
 {
   complex x, y, z; /*Unos n�meros complejos*/
   double N;
   x.fReal = 10;  x.fImg = 20;
   y.fReal = 30;  y.fImg = 40;
   N = 0.1;   
   printf ("N = %f\nx = (%f) + (%f)i\ny = (%f) + (%f)i\n\n", N, x.fReal, x.fImg, y.fReal, y.fImg);
   z = scSuma (x, y);
   printf ("z = x + y = (%f) + (%f)i\n", z.fReal, z.fImg);
   z = scProductoConEscalar (x, N);
   printf ("z = x * N = (%f) + (%f)i\n", z.fReal, z.fImg);
   return (0);
 }
 
 complex scSuma (complex a, complex b)
 { /*La suma se realiza componente a componente, 
     es decir, real con real e imaginario con imaginario*/
   complex scR;
   scR.fReal = a.fReal + b.fReal;
   scR.fImg = a.fImg + b.fImg;
   return (scR);
 }
 
 complex scProductoConEscalar (complex a, double c)
 { /*Todo el n�mero complejo se multiplica por c*/
   complex scR;
   scR.fReal = a.fReal * c;
   scR.fImg = a.fImg * c;
   return (scR); 
 }
