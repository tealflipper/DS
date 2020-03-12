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
  for(int i=0;i<N;i++) mis_padres[i]=-2;
  MPI_Barrier(MPI_COMM_WORLD);
  // Código para proceso 2
  // Inicia inundación
  if (world_rank == 0){       
    //nodo visitado por fuerza externa
      visitado = TRUE;
      // No tengo padre
      mi_nodo.padre = -1;
      mi_nodo.rango=world_rank;
      mis_padres[mi_nodo.rango]=mi_nodo.padre;
      //mandar información del nodo actual a vecinos
      //manda su nodo
      for (int i = 0; i < n; i++){
        MPI_Send(&mi_nodo, 2, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD);
        //printf("Nodo %d mando mensaje a %d\n", world_rank, neighbors[i]);

      }
      mis_padres[mi_nodo.rango]=mi_nodo.padre;
    
    
    // Espero Recibir dato de padres de mis vecinos
    for (int i = 0; i < n; i++){
      //printf("%d recibe de %d con padre \n",world_rank,neighbors[i]);
      MPI_Recv(&mensaje, 2, MPI_INT, neighbors[i], 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      mis_padres[mensaje.rango]=mensaje.padre;
    }
    
    // Ya tengo los padres, ahora los imprimo
                
  }
  // Código para procesos normales
  else if (world_rank < N){
    // Recibo de mi padre
    // No tengo padre
    mi_nodo.rango=world_rank;
    //recibe padre
    MPI_Recv(&mensaje, 2, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //printf("Nodo %d recibe mensaje de %d con padre %d\n", world_rank, mensaje.rango,mensaje.padre);
    mis_padres[mensaje.rango]=mensaje.padre;
    // Nodo no visitado
    if(visitado){
      // Envio retroalimentación a mi padre 
      
      for(int i=0;i<n;i++){
        //printf("%d recibe retro de %d\n",world_rank,neighbors[i]);
        MPI_Recv(&mensaje, 2, MPI_INT, neighbors[i], 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
    }else {//nodo visitado
      visitado = 1;
      mi_nodo.padre=mensaje.rango;
      mis_padres[mi_nodo.rango]=mi_nodo.padre;
      for (int i = 0; i < n; i++){
        MPI_Send(&mi_nodo, 2, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD);
        //printf("%d manda mensaje a %i\n", world_rank,neighbors[i]);
      }
      //printf("%d manda retro a %i\n", world_rank,mi_nodo.padre);
      MPI_Send(&mi_nodo, 2, MPI_INT, mi_nodo.padre, 2, MPI_COMM_WORLD);
      
    }
    // Recibo retroalimentación para terminar
    
  } 
  
  MPI_Barrier(MPI_COMM_WORLD);
  printf("proceso %d:   ",world_rank);
    for (int i = 0; i < N - 1; i++)
      if(mis_padres[i]!=-2)  printf("[%d] %d ",i, mis_padres[i]);
  printf("\n\n");
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}