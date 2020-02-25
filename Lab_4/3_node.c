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

int getSum(int* arr, int n){
  int sum=0;
  for (int i=0;i<n;i++) if (arr[i]==1) sum++;
  return sum;
}
int * getNeighbors(int iRank){
  int localRank=iRank%STAR;
  int n=(localRank==0)?5:1;
  int* neighbors=(int*)calloc(n,sizeof(int));
  for(int i=0;i<n;i++){
    if(localRank==0){//6 indices
      int prev=(iRank==0)? 20:iRank-4;
      int next=(iRank==20)? 0: iRank+4;
      neighbors[0]=prev;
      neighbors[1]=next;
      for (int i=2;i<6;i++){
        neighbors[i]=iRank+i;
      }

    }
    else neighbors[i]=iRank-localRank;
  }
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
int world_rank, world_size,iEnvio=0,visited=-1,father=-1;
int elements;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
MPI_Comm_size(MPI_COMM_WORLD, &world_size);

// Get the group of processes in MPI_COMM_WORLD
MPI_Group world_group;
MPI_Comm_group(MPI_COMM_WORLD, &world_group);

int n = N;
int outside=1,inside=5;
int*inGroup;
int* ranks=getNeighbors(world_rank);

printf("[%d]: ",world_rank);
for(int i=0;i<elements;i++) printf("%d ",getNeighbors(world_rank));
MPI_Barrier (MPI_COMM_WORLD); //Esperamos a los nodos
  //printf("ahora el nodo %d creara su grupo\n",world_rank); //Esperamos a los nodos
// construye N grupos
MPI_Group my_group[n];
for(int i=0;i<n;i++) {
  int tmp=(i%STAR==0)?7:3;
  MPI_Group_incl(world_group, tmp, inGroup, &my_group[i]);
}

// crea N comunicadores
MPI_Comm prime_comm[n];
for(int i=0;i<n;i++) {
  int tmp=(i%STAR==0)?7:3;
  MPI_Comm_create_group(MPI_COMM_WORLD, my_group[i], i, &prime_comm[i]);
  if ((prime_comm[i]==MPI_COMM_NULL)&&(iIsInGroup(inGroup[i],elements, world_rank)))
  { //Si esta en el grupo y no se pudo crear
    printf ("Error en comunicadores Grupo %d, nodo %d.\n",i, world_rank);
    MPI_Finalize ();
    return (0);
  }
}

int prime_rank[n], prime_size[n];
for(int i=0;i<n;i++) {
  prime_rank[i]=-1;
  prime_size[i]=-1;
}
//assigna rank con comunicador y talla si el comunicador no es nulo
for(int i=0;i<n;i++) 
{
  if (MPI_COMM_NULL != prime_comm[i]) {
    MPI_Comm_rank(prime_comm[i], &prime_rank[i]);
    MPI_Comm_size(prime_comm[i], &prime_size[i]);
  }
}
//grupos creados
//broadcast here
if(world_rank==0){
  visited=1;
  //envio id a vecinos
  MPI_Bcast(&world_rank,1,MPI_INT,0,prime_comm[0]);
  //no hay padre
  father=-1;
  //enviar padre a maestro
  MPI_Send(&father,1,MPI_INT,world_size-1,2,MPI_COMM_WORLD);

  //espero padres
  int Fathers[world_size-1];
  MPI_Recv(&Fathers[0],world_size-1,MPI_INT,world_size-1,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  for (int i = 0; i < world_size - 1; i++)
    printf("Proceso %d, mi padre es %d\n", i, Fathers[i]);
    
}else if(world_rank<world_rank-1){
  //recive from father
  
}



//for(int i=0;i<n;i++) printf("el nodo %d en el grupo %d %d\n",world_rank,i,prime_rank[i]);
for(int i=0;i<n;i++){
   MPI_Group_free(&my_group[i]);
}
MPI_Group_free(&world_group);

 MPI_Finalize ();
 return (0);
 } 