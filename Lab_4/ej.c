#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <mpi.h>
#define N 24
#define STAR 4 // nodes in star topology network
#define MASTER 24 /*El nodo maestro será el ultimo proceso, al igual que en los subgrupos*/
#define TRUE 1
#define FALSE 0

int iIsInGroup (int *piGroup, int iLenGroup, int iRank){
  int i;
  for (i=0; i<iLenGroup; i++) 
  if (iRank==piGroup[i]) return (TRUE);
  return (FALSE);
}

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

int n = 7;
int ranks[7] = {1, 2, 3, 5, 7, 11, 13};

// Construct a group containing all of the prime ranks in world_group
MPI_Group prime_group;
MPI_Group_incl(world_group, 7, ranks, &prime_group);

// Create a new communicator based on the group
MPI_Comm prime_comm;
MPI_Comm_create_group(MPI_COMM_WORLD, prime_group, 0, &prime_comm);

int prime_rank = -1, prime_size = -1;
// If this rank isn't in the new communicator, it will be
// MPI_COMM_NULL. Using MPI_COMM_NULL for MPI_Comm_rank or
// MPI_Comm_size is erroneous
if (MPI_COMM_NULL != prime_comm) {
	MPI_Comm_rank(prime_comm, &prime_rank);
	MPI_Comm_size(prime_comm, &prime_size);
}

printf("WORLD RANK/SIZE: %d/%d PRIME RANK/SIZE: %d/%d\n",
	world_rank, world_size, prime_rank, prime_size);

MPI_Group_free(&world_group);
MPI_Group_free(&prime_group);
//MPI_Comm_free(&prime_comm);

 MPI_Finalize ();
 return (0);
 } 