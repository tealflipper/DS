#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
enum Node {A,B,C,D,E};
typedef enum Node node;

#define iteration 2
#define N 5
#define M 2

//prints n x m matrix
void printMatrix(int Matrix[N][N],int n,int m){
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      printf("%d",Matrix[i][j]);
    }
    printf(" ");
  }
}

int getPrev(int op){
  return (op==0)?N-1:op-1;
}

int getNext(int op){
 return (op==N-1)?0:op+1;
}

// my matrix, of n x n op is the node 0<op<=5
void makeAdyencyMatrix(int Matrix[N][N],node op){
  for(int i=0;i<N;i++){ for (int j=0;j<N;j++) Matrix[i][j]=0;}
  Matrix[op][getNext(op)]=1;
  Matrix[op][getPrev(op)]=1;
  Matrix[getNext(op)][op]=1;
  Matrix[getPrev(op)][op]=1;
  
}

void mixMatrices(int Ma[N][N], int Mb[N][N]){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++) {
      if(Mb[i][j]==1) Ma[i][j]=Mb[i][j];
    } 
  }
  
}

int main(int iArgc, char *pscArgv[]){
  int iRank; 
  int iSize; 
  int iFlag;
  MPI_Request mpirReq;
  char nodes[5]="ABCDE";
  int myAdyencyMatrix[N][N];
  int incomingAdyencyMatrix[N][N]; 
  MPI_Init (&iArgc, &pscArgv);
  MPI_Status mpisEstado;
  MPI_Comm_size (MPI_COMM_WORLD, &iSize);
  MPI_Comm_rank (MPI_COMM_WORLD, &iRank);
  for(int i=A;i<=E;i++){ 
    if(iRank==i) {
      makeAdyencyMatrix(myAdyencyMatrix,i);
      }
  }
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
  }

      printf("%c: ",nodes[iRank]);
      printMatrix(myAdyencyMatrix,N,N);
      printf("\n");
  MPI_Finalize();
}