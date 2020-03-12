typedef struct STR str;
struct STR{
   char arr[100];  /*arreglo de characteres*/
   int ln;   /*tamaño de la cadena*/
 };
 typedef struct DATA data;
struct DATA{
    int arr[1000];  /*arreglo de enteros*/
    int ln;   /*tamaño de la cadena*/
    int key;
 };

program REMOTECALLS
{
	version REMOTECALLS_1
	{
    int isSubstring (str s1, str s2) = 1;
    int search(data myData) = 2;
    data sort(data myData)=3;
    void printArray(data myData) = 4;
    long fact(int n) = 5;
	} = 1;
} = 0x20000001;