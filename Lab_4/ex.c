#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <mpi.h>
#define NUM_NEIGHBORS 3

int * getNeighbors2(int iRank){
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

int main(int argc, char **argv)
{
    // Iniciando programa de MPI
    MPI_Init(&argc, &argv);
    int world_rank, world_size,visited=-1,father=-1;
    // Manejador del grupo global
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //Para obtener el ID/
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //sPara obtener el número de procesos/
    int n=(world_rank%4==0)?5:1;
    // Inicializo mis variables
    int visitado = 0;
    // Obtengo mis vecinos
    int *neighbors = getNeighbors2(world_rank);
    if (world_rank != world_size - 1)
    {
        
        printf("Soy %d y mis vecinos son ", world_rank);
        for (int i = 0; i < n; i++)
            printf("%d ", neighbors[i]);
        printf("\n");
    }

    // Código para proceso 0
    // Inicia inundación
    if (world_rank == 0)
    {
        visitado = 1;
        // Envió mi id a mis vecinos
        for (int i = 0; i < n; i++)
            MPI_Send(&world_rank, 1, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD);

        // No tengo padre
        int padre = -1;
        // Envio mi padre al maestro
        MPI_Send(&padre, 1, MPI_INT, world_size - 1, 2, MPI_COMM_WORLD);
        // Espero Recibir array de padres
        int padres[world_size - 1];
        MPI_Recv(&padres[0], world_size - 1, MPI_INT, world_size - 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Ya tengo los padres, ahora los imprimo
        for (int i = 0; i < world_size - 1; i++)
            printf("Proceso %d, mi padre es %d\n", i, padres[i]);
    }

    // Código para procesos normales
    else if (world_rank < world_size - 1)
    {
        // Recibo de mi padre
        int padre;
        MPI_Recv(&padre, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Envió mi id a mis vecinos excepto a mi padre
        for (int i = 0; i < n; i++)
            if (neighbors[i] != padre)
                MPI_Send(&world_rank, 1, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD);

        visitado = 1;
        // Envio mi padre al maestro
        MPI_Send(&padre, 1, MPI_INT, world_size - 1, 2, MPI_COMM_WORLD);
        // Recibo array de padres para terminar
        int padres[world_size - 1];
        MPI_Recv(&padres[0], world_size - 1, MPI_INT, world_size - 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else
    {
        // Recibiendo padres
        int padres[world_size - 1];
        for (int i = 0; i < world_size - 1; i++)
            MPI_Recv(&padres[i], 1, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Enviando a procesos los padres
        for (int i = 0; i < world_size - 1; i++)
            MPI_Send(&padres[0], world_size - 1, MPI_INT, i, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}