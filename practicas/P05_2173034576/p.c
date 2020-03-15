#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <mpi.h>
#define TRUE 1
#define FALSE 0
#define N 24
typedef struct{
  int padre;
  int rango;
  int arr[N];
}packet;

int * getNeighbors(int iRank){
  int localRank=iRank%4;
  int n=(localRank==0)?5:1;
  int* neighbors=(int*)calloc(n,sizeof(int));
  for(int i=0;i<n;i++){
    if(localRank==0){//6 indices
      int prev=(iRank==0)? 20:iRank-4;
      int next=(iRank==20)? 0: iRank+4;
      neighbors[0]=prev;
      neighbors[1]=next;
      for (int i=2;i<6;i++){
        neighbors[i]=iRank+i-1;
      }

    }
    else neighbors[i]=iRank-localRank;
  }
  return neighbors;
}

void copyArr(int* from, int* to, int n){
  for(int i=0;i<n;i++) to[i]=from[i];
}

int main(int argc, char **argv)
{
  // Iniciando programa de MPI
  MPI_Init(&argc, &argv);
  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //Para obtener el ID/
  MPI_Comm_size(MPI_COMM_WORLD, &world_size); //sPara obtener el número de procesos/
  int n=(world_rank%4==0)?5:1;
  // Inicializo mis variables
  // Obtengo vecinos
  int *neighbors = getNeighbors(world_rank);
  int mis_padres[N];
  packet mi_nodo;
  packet mensaje;
  int visitado=FALSE;
  for(int i=0;i<N;i++) mi_nodo.arr[i]=-2;
  for(int i=0;i<N;i++) mis_padres[i]=-2;
  MPI_Barrier(MPI_COMM_WORLD);
  // Código para proceso 2
  // Inicia inundación
  int isdone=0;
  int l=0;
  while(!isdone){
    if(world_rank==0){
      if(!visitado){
        visitado=1;
        mi_nodo.padre = -1;
        mi_nodo.rango=world_rank;
        mi_nodo.arr[mi_nodo.rango]=mi_nodo.padre;
        mis_padres[mi_nodo.rango]=mi_nodo.padre;
        for (int i = 0; i < n; i++){
          MPI_Send(&mi_nodo, 2+N, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD);
          //printf("Nodo %d mando mensaje a %d\n", world_rank, neighbors[i]);
        }
      }
      else{
        for (int i = 0; i < n; i++){
          MPI_Recv(&mensaje, 2+N, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          for(int k=0;k<N;k++){
            if(mensaje.arr[k]>-2 && mensaje.arr[k] <N) mis_padres[k]=mensaje.arr[k];
          }
          //printf("Nodo %d recibe mensaje a %d\n", world_rank, neighbors[i]);
        }
        for(int k=0;k<N;k++) mi_nodo.arr[k]=mis_padres[k];
        //mandar que ya se recibio el mensaje, retro
        for (int i = 0; i < n; i++){
          MPI_Send(&mi_nodo, 2+N, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD);
          printf("Nodo %d mando retro a %d\n", world_rank, neighbors[i]);
        }
        isdone=1;
      }
      
    }
    else{
      if(visitado){
        for (int i = 0; i < n; i++){
           MPI_Recv(&mensaje, 2+N, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          for(int k=0;k<N;k++){
            if(mensaje.arr[k]>-2 && mensaje.arr[k] <N) mis_padres[k]=mensaje.arr[k];
          }
        }
        isdone=1;
        //nodo recibe toda retro
        MPI_Send(&mi_nodo, 2+N, MPI_INT, mi_nodo.padre, 1, MPI_COMM_WORLD);

      }
      else {
      MPI_Recv(&mensaje, 2+N, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int k=0;k<N;k++){
          if(mensaje.arr[k]>-2 && mensaje.arr[k] <N) mis_padres[k]=mensaje.arr[k];
        }
      }
      if(!visitado){
        mi_nodo.padre=mensaje.padre;
        mi_nodo.rango=world_rank;
        mi_nodo.arr[mi_nodo.rango]=mi_nodo.padre;
        mi_nodo.padre=mensaje.rango;
        mis_padres[mi_nodo.rango]=mi_nodo.padre;
        visitado=1;
        //paso 3->2
        for(int k=0;k<N;k++) mi_nodo.arr[k]=mis_padres[k];
        for (int i = 0; i < n; i++){
          MPI_Send(&mi_nodo, 2+N, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD);
          printf("Nodo %d mando mensaje a %d\n", world_rank, neighbors[i]);
        }
      }else{
        
        for(int k=0;k<N;k++) mi_nodo.arr[k]=mis_padres[k];
        for (int i = 0; i < n; i++){
          MPI_Send(&mi_nodo, 2+N, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD);
          printf("Nodo %d mando retro a %d\n", world_rank, neighbors[i]);
        }
      }
    }
  }
  for(int i=0;i<N;i++){
    if(mis_padres[i]==world_rank) MPI_Recv(&mensaje, 2+N, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    for(int k=0;k<N;k++){
            if(mensaje.arr[k]>-2 && mensaje.arr[k] <N) mis_padres[k]=mensaje.arr[k];
          }
  }
  for(int k=0;k<N;k++) mi_nodo.arr[k]=mis_padres[k];
  
  MPI_Barrier(MPI_COMM_WORLD);
  printf("proceso %d:   ",world_rank);
    for (int i = 0; i < N - 1; i++)
      if(mis_padres[i]!=-2)  printf("[%d] %d ",i, mis_padres[i]);
  printf("\n\n");
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
