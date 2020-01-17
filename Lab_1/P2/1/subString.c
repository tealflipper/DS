/*Para poder mandar una cadena, se crea una estructura con un arreglo de characteres
  suficientemente grande para que no exista preocupación de llenar el arreglo y un termino n 
  que indica el tamaño de la cadena.
  */

#include <stdio.h>
#include <stdlib.h>
 typedef struct STR str;  /*Tipo str*/
 struct STR
 {
   char arr[100];  /*arreglo de characteres*/
   int ln;   /*tamaño de la cadena*/
 };
 
 int isSubstring (str a, str b);

 int copyString(char* to, char* from){
   int i=0;
   while(from[i]!=0){
     to[i]=from[i];
     i++;
   }
   return i;
 }
 int main (int argc, char *argv[])
 {
   if (argc < 3) {
		printf ("usage: %s string1 string2 \n", argv[0]);
		exit (1);
	}

  str s1;
  s1.ln=copyString(s1.arr,argv[1]);
	str s2;
  s2.ln=copyString(s2.arr,argv[2]);
    int res = isSubstring(s1, s2); 
    if (res == -1) 
        printf ("Not present\n"); 
    else
        printf("Present at index %d\n", res); 
    return 0;
 }
 
int isSubstring(str s1, str s2) 
{ 
    int M = s1.ln; 
    int N = s2.ln; 
  
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) { 
        int j; 
  
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++) 
            if (s2.arr[i + j] != s1.arr[j]) 
                break; 
  
        if (j == M) 
            return i; 
    } 
  
    return -1; 
} 
