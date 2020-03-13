#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <mpi.h>
#define TRUE 1
#define FALSE 0
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



int main(int argc, char **argv)
{
    // Iniciando programa de MPI
    MPI_Init(&argc, &argv);
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); //Para obtener el ID/
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); //sPara obtener el número de procesos/
    int n=(world_rank%4==0)?5:1;
    // Inicializo mis variables
    int visitado = 0;
    // Obtengo vecinos
    int *neighbors = getNeighbors(world_rank);
    while(!visitado){
        // Código para proceso 2
        // Inicia inundación
        if (world_rank == 2)
        {
            // Envio mi id a mis vecinos
            MPI_Request mpirReq;
            int iFlag=0;
            MPI_Status mpisEstado;
            int bSalir;
            for (int i = 0; i < n; i++){
                MPI_Isend (&world_rank, 1, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD, &mpirReq);
                bSalir = FALSE;
                while (!bSalir)
                {
                    MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                    if (iFlag) bSalir = TRUE;
                }
            }
            // No tengo padre
            int padre = -1;
            // Envio mi padre al maestro
            MPI_Isend (&padre, 1, MPI_INT, world_size - 1, 2, MPI_COMM_WORLD, &mpirReq);
            bSalir = FALSE;
            while (!bSalir)
            {
                MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                if (iFlag) bSalir = TRUE;
            }

            // Espero Recibir array de padres
            int padres[world_size - 1];
            MPI_Irecv (&padres[0], world_size - 1, MPI_INT, world_size - 1, 2, MPI_COMM_WORLD, &mpirReq);
            bSalir = FALSE;
            while (!bSalir)
            {
                MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                if (iFlag) bSalir = TRUE;
            }
            visitado = 1;
            for (int i = 0; i < world_size - 1; i++)
            printf("Proceso %d, mi padre es %d\n", i, padres[i]);
        
        }
        // Código para procesos normales
        else if (world_rank < world_size - 1)
        {
            visitado = 1;
            MPI_Request mpirReq;
            int iFlag=0;
            MPI_Status mpisEstado;
            int bSalir;
            // Recibo de mi padre
            int padre;
            MPI_Irecv (&padre, 1, MPI_INT, MPI_ANY_SOURCE, 2 , MPI_COMM_WORLD, &mpirReq);
            //espera que se reciba padre
            bSalir = FALSE;
            while (!bSalir)
            {
                MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                if (iFlag) bSalir = TRUE;
            }
            // Envio mi id a mis vecinos excepto a mi padre
            for (int i = 0; i < n; i++)
                if (neighbors[i] != padre)
                    MPI_Isend (&world_rank, 1, MPI_INT, neighbors[i], 1, MPI_COMM_WORLD, &mpirReq);
                    bSalir = FALSE;
                    while (!bSalir)
                    {
                        MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                        if (iFlag) bSalir = TRUE;
                    }   
                    visitado = TRUE;
                    // Envio mi padre al maestro
                    MPI_Isend (&padre, 1, MPI_INT, world_size - 1, 2, MPI_COMM_WORLD, &mpirReq);
                    bSalir = FALSE;
                    while (!bSalir)
                    {
                        MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                        if (iFlag) bSalir = TRUE;
                    }
                    // Recibo array de padres para terminar
                    int padres[world_size - 1];
                    MPI_Irecv (&padres[0], world_size - 1, MPI_INT, world_size - 1, 2, MPI_COMM_WORLD, &mpirReq);
                    bSalir = FALSE;
                    while (!bSalir)
                    {
                        MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                        if (iFlag) bSalir = TRUE;
                    }}
        else
        {
            MPI_Request mpirReq;
            int iFlag=0;
            MPI_Status mpisEstado;
            int bSalir;
            // Recibiendo padres
            int padres[world_size - 1];
            for (int i = 0; i < world_size - 1; i++)
                MPI_Irecv (&padres[i], 1, MPI_INT, i, 2, MPI_COMM_WORLD, &mpirReq);
            for (int i = 0; i < world_size - 1; i++){
                bSalir = FALSE;
                while (!bSalir)
                {
                    MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                    if (iFlag) bSalir = TRUE;
                }
            }
            // Enviando a procesos los padres
            for (int i = 0; i < world_size - 1; i++)
                MPI_Isend (&padres[0], world_size - 1, MPI_INT, i, 2, MPI_COMM_WORLD, &mpirReq);
            for (int i = 0; i < world_size - 1; i++){
                bSalir = FALSE;
                while (!bSalir)
                {
                    MPI_Test (&mpirReq, &iFlag, &mpisEstado);
                    if (iFlag) bSalir = TRUE;
                }
            }
        }
    }   
    MPI_Finalize();
    return 0;
}