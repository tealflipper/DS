
typedef struct STR data;
struct STR{
    int arr[1000];  /*arreglo de characteres*/
    int ln;   /*tamaño de la cadena*/
    int key;
 };

program SUBSTRING
{
	version SUBSTRING_1
	{
    int search(data myData) = 1;
    data sort(data myData)=2;
    void printArray(data myData) = 3;

	} = 1;
} = 0x20000001;


