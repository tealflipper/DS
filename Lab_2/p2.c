#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
enum Node {A,B,C,D,E};
typedef enum Node node;

#define iteration 3
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
  int iFlag;
  unsigned char bSalir;
  MPI_Request mpirReq[N][N];
  char nodes[5]="ABCDE";
  int myAdyencyMatrix[N][N];
  int incomingAdyencyMatrix1[N][N]; 
  int incomingAdyencyMatrix2[N][N];
  MPI_Status mpisEstado;
  MPI_Init (&iArgc, &pscArgv);
  MPI_Comm_size (MPI_COMM_WORLD, &iSize);
  MPI_Comm_rank (MPI_COMM_WORLD, &iRank);
  for(int i=A;i<E;i++) if(iRank==i) makeAdyencyMatrix(myAdyencyMatrix,i);
  for(int i=0;i<iteration;i++){
    //send
    for (int j=0;j<N;j++){
      if(iRank==j){
        int prev=getPrev(j);
        int next=getNext(j);
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, prev, j, MPI_COMM_WORLD, &mpirReq[j][prev]);
        MPI_Isend (myAdyencyMatrix, N*N, MPI_INT, next, j, MPI_COMM_WORLD, &mpirReq[j][next]);
       
      }
      //receive
      for (int j=0;j<N;j++){
        if(iRank==j){
          int prev=getPrev(j);
          int next=getNext(j);
          for (int i=0;i<100000;i++);
          MPI_Irecv (incomingAdyencyMatrix1, N*N, MPI_INT, prev, prev, MPI_COMM_WORLD, &mpirReq[j][prev]);
          MPI_Irecv (incomingAdyencyMatrix2, N*N, MPI_INT, next, next, MPI_COMM_WORLD, &mpirReq[j][next]);
          //MPI_Wait(&mpirReq[j][prev], &mpisEstado);
          MPI_Test (&mpirReq[j][prev], &iFlag, &mpisEstado);
          //printf ("TAG: %d, Origen: %d flag %d\n", mpisEstado.MPI_TAG, mpisEstado.MPI_SOURCE, iFlag);
          MPI_Test (&mpirReq[j][next], &iFlag, &mpisEstado);
          //printf ("TAG: %d, Origen: %d flag %d\n", mpisEstado.MPI_TAG, mpisEstado.MPI_SOURCE, iFlag);
          //MPI_Test (&mpirReq[j][1], &iFlag, &mpisEstado);
          //printf ("TAG1: %d, Origen: %d\n", iFlag, mpisEstado.MPI_SOURCE);
          mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix1);
          //MPI_Wait(&mpirReq[j], &mpisEstado);
          mixMatrices(myAdyencyMatrix,incomingAdyencyMatrix2);
        }
      }
    }
  }
    if(iRank==0) printMatrix(myAdyencyMatrix,N,N);
  MPI_Finalize();
}