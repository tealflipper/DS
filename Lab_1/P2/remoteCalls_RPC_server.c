/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "remoteCalls_RPC.h"

void printArray_p(int arr[], int n) 
{ 
  int i; 
  for (i = 0; i < n; i++) 
      printf("%d ", arr[i]); 
  printf("\n"); 
} 

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

int *issubstring_1_svc(str s1, str s2,  struct svc_req *rqstp)
{
	static int  result;
	int M = s1.ln; 
  int N = s2.ln; 
    /* A loop to slide pat[] one by one */
  for (int i = 0; i <= M-N; i++) { 
    int j; 
    /* For current index i, check for pattern match */
    for (j = 0; j < N; j++) if (s1.arr[i + j] != s2.arr[j]) break;   
      if (j == N) 
				result=i;
        printf("%d\n",result);
        return &result; 
    } 
	result=-1;
	return &result;
}
data *sort_1_svc(data myData,  struct svc_req *rqstp)
{
	static data  tmp;

	tmp.key=myData.key;
  tmp.ln=myData.ln;
  for(int i=0;i<myData.ln;i++){ tmp.arr[i]=myData.arr[i];}
  insertionSort(tmp.arr,myData.ln);
  printArray_p(tmp.arr,tmp.ln);

	return &tmp;
}

int *search_1_svc(data myData,  struct svc_req *rqstp)
{
	static int  result;
  insertionSort(myData.arr,myData.ln);
	result=binarySearch(myData.arr,0,myData.ln,myData.key);

	return &result;
}


void *
printarray_1_svc(data myData,  struct svc_req *rqstp)
{
	static char * result;

	printArray_p(myData.arr,myData.ln);

	return (void *) &result;
}

long *
fact_1_svc(int n,  struct svc_req *rqstp)
{
	static long  result;

	if(n<=1) result= 1;
	else result=(long)n*(*fact_1_svc(n-1,rqstp));

	return &result;
}
