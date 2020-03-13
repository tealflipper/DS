
 typedef struct COMPLEX complex;  /*Tipo complex*/
 struct COMPLEX
 {
   double fReal;  /*Parte real*/
   double fImg;   /*Parte imaginaria*/
 };

program COMPLEX_OPERACIONES
{
	version COMPLEX_OPER_1
	{
    complex scSuma (complex a, complex b) = 1;
    complex scProductoConEscalar (complex a, double c) = 2;
	} = 1;
} = 0x20000001;

