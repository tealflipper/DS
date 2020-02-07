#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
enum Node {A,B,C,D,E};
typedef enum Node node;
#define FALSE 0
#define TRUE 1
#define iteration 5
#define N 5
#define M 2
#define PRINCIPAL A /*El nodo cero será el principal*/ 

//prints n x m matrix
void printMatrix(int Matrix[N][N],int n,int m){
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      printf("%d",Matrix[i][j]);
    }
    printf(" ");
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

int getPrev(int op){
  switch (op)
  {
  case A:
    return D;
  case B:
    return E;
  case C:
    return A;
  case D:
    return B;
  case E:
    return C;
  
  default:
    break;
  }
}

int getNext(int op){
  switch (op)
  {
  case A:
    return C;
  case B:
    return D;
  case C:
    return E;
  case D:
    return A;
  case E:
    return B;
  
  default:
    break;
  }
}

int main(int iArgc, char *pscArgv[]){
  int iRank; /*Este es el idenficador de nodo*/
  int iSize; /*Número total de nodos*/
  int iFlag[2];
  unsigned char bSalir;
  MPI_Request mpirReq[4];
  char nodes[5]="ABCDE";
  int myAdyencyMatrix[N][N];
  int incomingAdyencyMatrix1[N][N]; 
  int incomingAdyencyMatrix2[N][N];
  MPI_Status mpisEstado[4];
  MPI_Init (&iArgc, &pscArgv);
  MPI_Comm_size (MPI_COMM_WORLD, &iSize);
  MPI_Comm_rank (MPI_COMM_WORLD, &iRank);
  for(int i=A;i<=E;i++) if(iRank==i) makeAdyencyMatrix(myAdyencyMatrix,i);
  for(int i=0;i<iteration;i++){
    //send
    for (int j=0;j<N;j++){
      if(iRank==j){
        int prev=getPrev(j);
        int next=getNext(j);
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, prev, j, MPI_COMM_WORLD, &mpirReq[0]);
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, next, j, MPI_COMM_WORLD, &mpirReq[1]);
       
      }
      //receive
      for (int j=0;j<N;j++){
        if(iRank==j){
          int prev=getPrev(j);
          int next=getNext(j);
          for (int i=0;i<100000;i++);
          MPI_Irecv (incomingAdyencyMatrix1, N*N, MPI_INT, prev, prev, MPI_COMM_WORLD, &mpirReq[2]);
          MPI_Irecv (incomingAdyencyMatrix2, N*N, MPI_INT, next, next, MPI_COMM_WORLD, &mpirReq[3]);
          //MPI_Wait(&mpirReq[2], &mpisEstado[2]);
          MPI_Test (&mpirReq[2], &iFlag[0], &mpisEstado[2]);
         //printf ("TAG: %d, Origen: %d\n", mpisEstado[2].MPI_TAG, mpisEstado[2].MPI_SOURCE);
          MPI_Test (&mpirReq[3], &iFlag[1], &mpisEstado[3]);
          //printf ("TAG: %d, Origen: %d\n", mpisEstado[3].MPI_TAG, mpisEstado[3].MPI_SOURCE);
          //MPI_Test (&mpirReq[j][1], &iFlag, &mpisEstado);
          //printf ("TAG1: %d, Origen: %d\n", iFlag, mpisEstado.MPI_SOURCE);
          mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix1);
          //MPI_Wait(&mpirReq[3], &mpisEstado[3]);
          mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix2);
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
