#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
enum Node {A,B,C,D,E};
typedef enum Node node;

#define iteration 2
#define N 5
#define M 2
#define PRINCIPAL A /*El nodo cero será el principal*/ 

//prints n x m matrix
void printMatrix(int Matrix[N][N],int n,int m){
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      printf("%d ",Matrix[i][j]);
    }
    printf("\n");
  }
}
// my matrix, of n x n op is the node 0<op<=5
void makeAdyencyMatrix(int Matrix[N][N],node op){
  for(int i=0;i<N;i++){ for (int j=0;j<N;j++) Matrix[i][j]=0;}

  switch (op)
  {
  case A:
    Matrix[A][C]=1;
    Matrix[A][D]=1;
    Matrix[C][A]=1;
    Matrix[D][A]=1;
    break;
  
  case B:
    Matrix[B][D]=1;
    Matrix[B][E]=1;
    Matrix[D][B]=1;
    Matrix[E][B]=1;
    break;
  
  case C:
    Matrix[C][A]=1;
    Matrix[C][E]=1;
    Matrix[A][C]=1;
    Matrix[E][C]=1;
    break;
  case D:
    Matrix[D][A]=1;
    Matrix[D][B]=1;
    Matrix[A][D]=1;
    Matrix[B][D]=1;
    break;
  case E:
    Matrix[E][B]=1;
    Matrix[E][C]=1;
    Matrix[B][E]=1;
    Matrix[C][E]=1;
    break;
  default:
    break;
  }
  
}

void mixMatrices(int Ma[N][N], int Mb[N][N]){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++) {
      if(Mb[i][j]==1) Ma[i][j]=Mb[i][j];
    } 
  }
  
}

int main(int iArgc, char *pscArgv[]){
  int iRank; /*Este es el idenficador de nodo*/
  int iSize; /*Número total de nodos*/
  int iFlag;
  MPI_Request mpirReq;
  char nodes[5]="ABCDE";
  int myAdyencyMatrix[N][N];
  int incomingAdyencyMatrix[N][N]; 
  MPI_Status mpisEstado;
  MPI_Init (&iArgc, &pscArgv);
  MPI_Comm_size (MPI_COMM_WORLD, &iSize);
  MPI_Comm_rank (MPI_COMM_WORLD, &iRank);
  for(int i=A;i<E;i++) if(iRank==i) makeAdyencyMatrix(myAdyencyMatrix,i);
  for(int i=0;i<iteration;i++){
    for (int j=0;j<N;j++){
      if(iRank==j){
        int prev=(j==0)?N-1:j-1;
        int next=(j==N-1)?0:j+1;
        MPI_Send (myAdyencyMatrix, N*N, MPI_INT, next, j, MPI_COMM_WORLD);
        MPI_Send (myAdyencyMatrix, N*N, MPI_INT, prev, j, MPI_COMM_WORLD);
        MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, next, next, MPI_COMM_WORLD, &mpisEstado);
        mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
        MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, prev, prev, MPI_COMM_WORLD, &mpisEstado);
        mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);

      }
    }
    /*
    switch (iRank)
    {
    case A:
      
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, C, A, MPI_COMM_WORLD);
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, D, A, MPI_COMM_WORLD);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, C, C, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, D, D, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);

      printMatrix(myAdyencyMatrix,N,N);
      break;
    
    case B:
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, D, B, MPI_COMM_WORLD);
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, E, B, MPI_COMM_WORLD);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, D, D, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, E, E, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      break;

    case C:
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, A, C, MPI_COMM_WORLD);
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, E, C, MPI_COMM_WORLD);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, A, A, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, E, E, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      break;

    case D:
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, A, D, MPI_COMM_WORLD);
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, B, D, MPI_COMM_WORLD);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, A, A, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, B, B, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      break;
    
    case E:
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, B, E, MPI_COMM_WORLD);
      MPI_Send (myAdyencyMatrix, N*N, MPI_INT, C, E, MPI_COMM_WORLD);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, B, B, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      MPI_Recv(incomingAdyencyMatrix, N*N, MPI_INT, C, C, MPI_COMM_WORLD, &mpisEstado);
      mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix);
      break;
    default:
      break;
    }
    */
  }
  if(iRank==0) printMatrix(myAdyencyMatrix,N,N);
  MPI_Finalize();
}