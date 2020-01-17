
typedef struct STR str;
struct STR{
   char arr[100];  /*arreglo de characteres*/
   int ln;   /*tamaño de la cadena*/
 };

program SUBSTRING
{
	version SUBSTRING_1
	{
    int isSubstring (str s1, str s2) = 1;
	} = 1;
} = 0x20000001;

