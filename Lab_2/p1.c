#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
enum Node {A,B,C,D,E};
typedef enum Node node;

#define N 5
#define M 2
#define PRINCIPAL A /*El nodo cero será el principal*/ 

//prints n x m matrix
void printMatrix(int* Matrix,int n,int m){
  for(int i=0;i<n*m;i+=m){
    for(int j=i;j<i+m;j++){
      printf("%d ",Matrix[j]);
    }
    printf("\n");
  }
}
// my matrix, of n x n op is the node 0<op<=5
void makeAdyencyMatrix(int* Matrix,node op){
  for(int i=0;i<N*N;i++){ Matrix[i]=0;}
  switch (op)
  {
  case A:
    Matrix[2]=1;
    Matrix[3]=1;
    Matrix[10]=1;
    Matrix[15]=1;
    break;
  
  case B:
    Matrix[8]=1;
    Matrix[9]=1;
    Matrix[16]=1;
    Matrix[21]=1;
    break;
  
  case C:
    Matrix[10]=1;
    Matrix[14]=1;
    Matrix[2]=1;
    Matrix[22]=1;
    break;
  case D:
    Matrix[15]=1;
    Matrix[16]=1;
    Matrix[3]=1;
    Matrix[8]=1;
    break;
  case E:
    Matrix[21]=1;
    Matrix[22]=1;
    Matrix[9]=1;
    Matrix[14]=1;
    break;
  default:
    break;
  }
}

void mixMatrices(int *Ma, int* Mb){
  for(int i=0;i<N*N;i++){
    Ma[i]=Ma[i]|Mb[i];
  }
}

int main(int iArgc, char *pscArgv[]){
  int iRank; /*Este es el idenficador de nodo*/
  int iSize; /*Número total de nodos*/
  int iFlag;
  MPI_Request mpirReq;
  char nodes[5]="ABCDE";
  int myAdyencyMatrix[N*N];
  int incomingAdyencyMatrix[N*N]; 
  MPI_Status mpisEstado;
  MPI_Init (&iArgc, &pscArgv);
  MPI_Comm_size (MPI_COMM_WORLD, &iSize);
  MPI_Comm_rank (MPI_COMM_WORLD, &iRank);
  makeAdyencyMatrix(myAdyencyMatrix,A);
  switch (iRank)
  {
  case A:
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, C, A, MPI_COMM_WORLD);
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, D, A, MPI_COMM_WORLD);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, C, C, MPI_COMM_WORLD, &mpisEstado);
    mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, D, D, MPI_COMM_WORLD, &mpisEstado);
    mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);

    printMatrix(incomingAdyencyMatrix,N,N);
    break;
  
  case B:
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, D, B, MPI_COMM_WORLD);
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, E, B, MPI_COMM_WORLD);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, D, D, MPI_COMM_WORLD, &mpisEstado);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, E, E, MPI_COMM_WORLD, &mpisEstado);
    break;

  case C:
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, A, C, MPI_COMM_WORLD);
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, E, C, MPI_COMM_WORLD);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, A, A, MPI_COMM_WORLD, &mpisEstado);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, E, E, MPI_COMM_WORLD, &mpisEstado);
    break;

  case D:
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, A, D, MPI_COMM_WORLD);
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, B, D, MPI_COMM_WORLD);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, A, A, MPI_COMM_WORLD, &mpisEstado);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, B, B, MPI_COMM_WORLD, &mpisEstado);
    break;
  
  case E:
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, B, E, MPI_COMM_WORLD);
    MPI_Send (myAdyencyMatrix, N*N, MPI_INT, C, E, MPI_COMM_WORLD);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, B, B, MPI_COMM_WORLD, &mpisEstado);
    MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, C, C, MPI_COMM_WORLD, &mpisEstado);
    break;
  default:
    break;
  }
  
  MPI_Finalize();
}