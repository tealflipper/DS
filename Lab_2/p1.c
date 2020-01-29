#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 5
#define M 2

enum node {A,B,C,D,E}
int myAdyencyMatrix[N*N];
// my matrix, of n x n op is the node 0<op<=5
void makeAdyencyMatrix(int* Matrix,int n,int op){
  switch (op)
  {
  case A:
    myAdyencyMatrix[2]=1;
    myAdyencyMatrix[3]=1;
    myAdyencyMatrix[10]=1;
    myAdyencyMatrix[15]=1;
    break;
  
  case B:
    myAdyencyMatrix[8]=1;
    myAdyencyMatrix[9]=1;
    myAdyencyMatrix[16]=1;
    myAdyencyMatrix[21]=1;
    break;
  
  case C:
    myAdyencyMatrix[10]=1;
    myAdyencyMatrix[14]=1;
    myAdyencyMatrix[2]=1;
    myAdyencyMatrix[22]=1;
    break;
  case D:
    myAdyencyMatrix[15]=1;
    myAdyencyMatrix[16]=1;
    myAdyencyMatrix[3]=1;
    myAdyencyMatrix[8]=1;
    break;
  case E:
    myAdyencyMatrix[21]=1;
    myAdyencyMatrix[22]=1;
    myAdyencyMatrix[9]=1;
    myAdyencyMatrix[14]=1;
    break;
  default:
    break;
  }
}

