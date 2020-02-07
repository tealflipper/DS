#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
enum Node {A,B,C,D,E,BOSS};
typedef enum Node node;
#define FALSE 0
#define TRUE 1
#define iteration 100
#define N 5
#define M 2

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

int compMatrices(int Ma[N][N], int Mb[N][N]){
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++) {
      if(Mb[i][j]!=Ma[i][j]) return 0;
    } 
  } 
  return 1;
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
  int bVal=10;

  unsigned char bSalir;
  MPI_Request mpirReq[4*N];
  char nodes[N]="ABCDE";
  int myAdyencyMatrix[N][N];
  int incomingAdyencyMatrix[N][N][N]; 
  MPI_Status mpisEstado[5];
  MPI_Init (&iArgc, &pscArgv);
  MPI_Comm_size (MPI_COMM_WORLD, &iSize);
  MPI_Comm_rank (MPI_COMM_WORLD, &iRank);
  for(int i=A;i<=BOSS;i++) if(iRank==i) makeAdyencyMatrix(myAdyencyMatrix,i);
  for(int i=0;i<iteration;i++){
    // Normal nodes
    //send
    for (int j=0;j<N;j++){
      if(iRank==j){
        int prev=getPrev(j);
        int next=getNext(j);
        iFlag[3]=0,iFlag[2]=0;
        //printf("prev: %d, next: %d\n",prev,next);
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, prev, 1, MPI_COMM_WORLD, &mpirReq[0]);
        //MPI_Wait(&mpirReq[j], &mpisEstado[j]);
        MPI_Test (&mpirReq[0], &iFlag[2], &mpisEstado[0]);
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, next, 1, MPI_COMM_WORLD, &mpirReq[1]);
        //MPI_Wait(&mpirReq[j+N], &mpisEstado[j+N]);
        MPI_Test (&mpirReq[1], &iFlag[3], &mpisEstado[1]);
      }
    }
    //receive
    for (int j=0;j<N;j++){
      if(iRank==j){
        int prev=getPrev(j);
        int next=getNext(j);
        iFlag[0]=0,iFlag[1]=0;
        for (int i=0;i<100000;i++);
        MPI_Irecv (incomingAdyencyMatrix[0], N*N, MPI_INT, prev, 1, MPI_COMM_WORLD, &mpirReq[2]);
        //printf ("TAG: %d, Origen: %d F: %d\n", mpisEstado[j+N*2].MPI_TAG, mpisEstado[j+N*2].MPI_SOURCE,iFlag[0]);
        MPI_Irecv (incomingAdyencyMatrix[1], N*N, MPI_INT, next, 1, MPI_COMM_WORLD, &mpirReq[3]);
        //MPI_Wait(&mpirReq[j+N*2], &mpisEstado[j+N*2]);
        MPI_Test (&mpirReq[2], &iFlag[0], &mpisEstado[2]);
        //printf ("TAG: %d, Origen: %d F: %d\n", mpisEstado[2].MPI_TAG, mpisEstado[2].MPI_SOURCE,iFlag[2]);
        //printf ("TAG: %d, Origen: %d\n", mpisEstado[2].MPI_TAG, mpisEstado[3].MPI_SOURCE);
        //MPI_Test (&mpirReq[j][1], &iFlag, &mpisEstado);
        MPI_Test (&mpirReq[3], &iFlag[1], &mpisEstado[3]);
        //printf ("TAG: %d, Origen: %d F:%d\n", mpisEstado[3].MPI_TAG, mpisEstado[3].MPI_SOURCE,iFlag[1]);
        //printf ("TAG1: %d, Origen: %d\n", iFlag, mpisEstado.MPI_SOURCE);
        //MPI_Wait(&mpirReq[3], &mpisEstado[3]);
        mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix[0]);
        mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix[1]);
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, BOSS, 1, MPI_COMM_WORLD, &mpirReq[0]);
        int temp=0;
        MPI_Irecv (&temp, 1, MPI_INT, BOSS , 0, MPI_COMM_WORLD, &mpirReq[5]);

      }
    }    
    //Boss comunicates
    
    if(iRank==BOSS){
      MPI_Irecv (incomingAdyencyMatrix[0], N*N, MPI_INT, A , 1, MPI_COMM_WORLD, &mpirReq[0]);
      MPI_Irecv (incomingAdyencyMatrix[1], N*N, MPI_INT, B, 1, MPI_COMM_WORLD, &mpirReq[1]);
      MPI_Irecv (incomingAdyencyMatrix[2], N*N, MPI_INT, D, 1, MPI_COMM_WORLD, &mpirReq[2]);
      MPI_Irecv (incomingAdyencyMatrix[3], N*N, MPI_INT, E, 1, MPI_COMM_WORLD, &mpirReq[3]);
      int k;
      for (k=0;k<N-1;k++){
        if(!compMatrices(incomingAdyencyMatrix[k],incomingAdyencyMatrix[k+1]))  break;
        else if(k==N-2) {
          printf("interaciones: %d\n",i);
          i=iteration;
          for(int l=0;l<N;l++) MPI_Isend (&i, 1, MPI_INT, l, 0, MPI_COMM_WORLD, &mpirReq[4]);
        }
      
      }

      
    }
  
  }
  for(int i=0;i<N;i++){
    if(iRank==i) {
      printf("%c: ",nodes[i]);
      printMatrix(myAdyencyMatrix,N,N);
      printf("\n");
    }
  }
  MPI_Finalize();
}
