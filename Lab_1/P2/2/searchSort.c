#include <stdio.h>
#include <stdlib.h>

typedef struct STR data;
struct STR{
    int arr[1000];  /*arreglo de characteres*/
    int ln;   /*tamaño de la cadena*/
    int key;
 };
void printArray_p(int arr[], int n) ;
void insertionSort(int* arr, int n) 
{ 
  int i, key, j; 
    for (i = 1; i < n; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
      while (j >= 0 && arr[j] > key) { 
          arr[j + 1] = arr[j]; 
          j = j - 1; 
      } 
      arr[j + 1] = key; 
  } 
} 

void printArray_p(int arr[], int n) 
{ 
  int i; 
  for (i = 0; i < n; i++) 
      printf("%d ", arr[i]); 
  printf("\n"); 
} 

//array,left start, right end, x key
int binarySearch(int arr[], int l, int r, int x) 
{ 
  if (r >= l) { 
    int mid = l + (r - l) / 2; 
    if (arr[mid] == x) 
        return mid; 
    if (arr[mid] > x) 
      return binarySearch(arr, l, mid - 1, x); 
    return binarySearch(arr, mid + 1, r, x); 
  } 
 
  return -1; 
} 


int search(data myData){
    return binarySearch(myData.arr,0,myData.ln,myData.key);

}

data sort(data myData){
    data tmp;
    tmp.key=myData.key;
    tmp.ln=myData.ln;
    for(int i=0;i<myData.ln;i++){ tmp.arr[i]=myData.arr[i];}
    insertionSort(tmp.arr,myData.ln);
    return tmp;


}
void printArray(data myData){
    printArray_p(myData.arr,myData.ln);
}

int main(){
  data myData;
  int tmp[]={1,5,56,3,43,-12,34,54,2,4,65,0};
  myData.ln=12;
  myData.key=54;
  for(int i=0;i<myData.ln;i++){ myData.arr[i]=tmp[i];}

  printArray(myData);
  myData=sort(myData);
  printArray(myData);
  int res=search(myData);
  printf("clave %d encontrada en posicion; %d\n",myData.key,res);
}