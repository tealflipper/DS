#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
enum Node {A,B,C,D,E,BOSS};
typedef enum Node node;
#define FALSE 0
#define TRUE 1
#define iteration 1
#define N 5
#define M 2
//#labred063, 64,65,66
//prints n x m matrix
void printMatrix(int Matrix[N][N],int n,int m){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
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
  int iRank; /*Este es el idenficador de nodo*/
  int iSize; /*Número total de nodos*/
  int iFlag[4];
  int bVal=0;

  unsigned char bSalir;
  MPI_Request mpirReq[10];
  char nodes[N]="ABCDE";
  int myAdyencyMatrix[N][N];
  int incomingAdyencyMatrix[N][N][N]; 
  MPI_Status mpisEstado[10];
  MPI_Init (&iArgc, &pscArgv);
  MPI_Comm_size (MPI_COMM_WORLD, &iSize);
  MPI_Comm_rank (MPI_COMM_WORLD, &iRank);
  int i;
  for(i=A;i<=E;i++) if(iRank==i) makeAdyencyMatrix(myAdyencyMatrix,i);
  for(i=0;i<iteration;i++){
    // Normal nodes
    //send
    for (int j=0;j<N;j++){
      if(iRank==j){
        int prev=getPrev(j);
        int next=getNext(j);
        iFlag[3]=0,iFlag[2]=0;
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, prev, 1, MPI_COMM_WORLD, &mpirReq[0]);
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, next, 1, MPI_COMM_WORLD, &mpirReq[1]);
        for(int k=0;k<=1;k++){
          bSalir = FALSE;
          while (!bSalir)
          {
            MPI_Test (&mpirReq[k], &iFlag[0], &mpisEstado[k]);
            if (iFlag[0]) bSalir = TRUE;
          }
        }
      }
    }
    //receive
    for (int j=0;j<N;j++){
      if(iRank==j){
        int prev=getPrev(j);
        int next=getNext(j);
        iFlag[0]=0,iFlag[1]=0;
        MPI_Irecv (incomingAdyencyMatrix[0], N*N, MPI_INT, prev, 1, MPI_COMM_WORLD, &mpirReq[2]);
        MPI_Irecv (incomingAdyencyMatrix[1], N*N, MPI_INT, next, 1, MPI_COMM_WORLD, &mpirReq[3]);
        for(int k=2;k<=3;k++){
          bSalir = FALSE;
          while (!bSalir)
          {
            MPI_Test (&mpirReq[k], &iFlag[0], &mpisEstado[k]);
            if (iFlag[0]) bSalir = TRUE;
          }
        }
        mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix[0]);
        mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix[1]);
        /*
        */
      }
    }    

    
  
  }
  int fin=i;
  for(i=0;i<N;i++){
    if(iRank==i) {
      printf("%c: ",nodes[i]);
      printMatrix(myAdyencyMatrix,N,N);
      printf("\n");
    }
  }
  MPI_Finalize();
}
