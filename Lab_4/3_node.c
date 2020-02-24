#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <mpi.h>
#define N 4
#define STAR 4 // nodes in star topology network
#define MASTER 4 /*El nodo maestro será el ultimo proceso, al igual que en los subgrupos*/
#define TRUE 1
#define FALSE 0

int iIsInGroup (int *piGroup, int iLenGroup, int iRank){
  int i;
  for (i=0; i<iLenGroup; i++) 
  if (iRank==piGroup[i]) return (TRUE);
  return (FALSE);
}

int getSum(int* arr, int n){
  int sum=0;
  for (int i=0;i<n;i++) if (arr[i]==1) sum++;
  return sum;
}
int * getNeighbors(int iRank){
  int localRank=iRank%STAR;
  int* neighbors=(int*)calloc(N,sizeof(int));
  if(localRank==0){
    //int prev=(iRank==0)? 20:iRank-4;
    //int next=(iRank==lastNode)? 0: iRank+4;
    //neighbors[prev]=1;
    //neighbors[next]=1;
    for (int i=1;i<=3;i++){
      neighbors[iRank+i]=1;
    }
  }
  else neighbors[iRank-localRank]=1;
  neighbors[iRank]=1;
  //Para poder agregar nodo maestro
  neighbors[MASTER]=1;
  return neighbors;
}
/*
void getNeighbors(int iRank, int neighbors[N]){
  int lastNode=(N-STAR);
  for(int i=0;i<N;i++) neighbors[i]=0;
  int localRank=iRank%STAR;
  if(localRank==0){
    int prev=(iRank==0)? 20:iRank-4;
    int next=(iRank==lastNode)? 0: iRank+4;
    neighbors[prev]=1;
    neighbors[next]=1;
    for (int i=1;i<=3;i++){
      neighbors[iRank+i]=1;
    }
  }
  else neighbors[iRank-localRank]=1;
  neighbors[iRank]=1;
  //Para poder agregar nodo maestro
  //neighbors[MASTER]=1;
}
*/
int main (int iArg, char *spcArgv[])
{

  // Get the rank and size in the original communicator

  MPI_Init (&iArg, &spcArgv);
int world_rank, world_size;

MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
MPI_Comm_size(MPI_COMM_WORLD, &world_size);

// Get the group of processes in MPI_COMM_WORLD
MPI_Group world_group;
MPI_Comm_group(MPI_COMM_WORLD, &world_group);

int n = 4;
int outside=3,inside=5;
int** inGroup=(int**)malloc(sizeof(int*)*n);
int** ranks=(int**)malloc(sizeof(int*)*n);
int tmp;
ranks[0]=getNeighbors(0);
for (int i = 1; i<n;i++){
  ranks[i]=getNeighbors(i);
}
for(int i=0;i<n;i++){ 
  printf("[%d]: ",world_rank);
  for(int j=0;j<n+1;j++) printf("%d ", ranks[i][j]);
  printf("\n");
}
for(int i=0;i<n;i++){
  int elements=getSum(ranks[i],n+1);
  inGroup[i]=(int*)calloc(elements,sizeof(int));
  int k=0; //index of elements in array
  for(int j=0;j<n+1;j++){
    if(ranks[i][j]==1){
      inGroup[i][k++]=j;
    }
  }
}

// Construct a group containing all of the prime ranks in world_group
MPI_Group my_group[n];
for(int i=0;i<n;i++) {
  int tmp=(i%STAR==0)?5:3;
  MPI_Group_incl(world_group, tmp, inGroup[i], &my_group[i]);
}

// Create a new communicator based on the group
MPI_Comm prime_comm[n];
for(int i=0;i<n;i++) {
  int tmp=(i%STAR==0)?5:3;
  MPI_Comm_create_group(MPI_COMM_WORLD, my_group[i], i, &prime_comm[i]);
}

int prime_rank[n], prime_size[n];
for(int i=0;i<n;i++) {
  prime_rank[i]=-1;
  prime_size[i]=-1;
}
// If this rank isn't in the new communicator, it will be
// MPI_COMM_NULL. Using MPI_COMM_NULL for MPI_Comm_rank or
// MPI_Comm_size is erroneous
for(int i=0;i<n;i++) 
{
  if (MPI_COMM_NULL != prime_comm[i]) {
    MPI_Comm_rank(prime_comm[i], &prime_rank[i]);
    MPI_Comm_size(prime_comm[i], &prime_size[i]);
  }
}
printf("el nodo %d en su grupo %d\n",world_rank,prime_rank[0]);
MPI_Group_free(&world_group);
for(int i=0;i<n;i++) MPI_Group_free(&my_group[i]);
//MPI_Comm_free(&prime_comm);

 MPI_Finalize ();
 return (0);
 } 