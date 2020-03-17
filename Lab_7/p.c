#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <mpi.h>
#define TRUE 1
#define FALSE 0
#define N 10
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
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Request request;
  MPI_Status status;
  int i=0,c=0,j;
  if(world_rank!=3){

  while(c<2){
    int destino;
    int recibido = 0;
    if (world_rank == 0){
        i=world_rank;
        //send message
        
        //wait for ack
    MPI_Irecv(&j, 1, MPI_INT,  MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &request);
    destino=(world_rank+1)%world_size;
    while (!recibido){
      // Envio un mensaje con mi ID
      // En el arreglo
      // Para ser el master
      //printf("[%d] Destino: %d\n",world_rank, destino);
      MPI_Send(&i, 1, MPI_INT, destino, 1, MPI_COMM_WORLD);// Espero retroalimentación para ver si le llego
      sleep(2);
        // Esperando para ver si responde
        int flag = 0;
        // Probando si llego mensaje
        MPI_Test(&request, &flag, &status);
        if (flag){
          // El proceso recibió el menasaje
          // Ya puedo seguir
          //printf("nodo %d respondio a %d\n ",status.MPI_SOURCE, world_rank);
          recibido = 1;
        }else{
          //printf("nodo %d no respondio a %d\n ",destino, world_rank);
        }
        // Envio al siguiente nodo
        destino++;
        if (destino == world_size)
        {
          destino =1;
          // printf("Ningún proceso recibió mi mensaje, vuelvo a empezar\n");
        }
      }
        MPI_Irecv(&i, 1, MPI_INT,  MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        MPI_Send(&i, 1, MPI_INT,status.MPI_SOURCE, 2, MPI_COMM_WORLD);
        //printf("proceso %d:  %d\n ",world_rank,i);
            
    }
    // Código para procesos normales
    else if (world_rank < world_size){
        MPI_Irecv(&i, 1, MPI_INT,  MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        //printf("proceso %d:  %d\n ",world_rank,i);
        //send ack
        MPI_Send(&i, 1, MPI_INT,status.MPI_SOURCE, 2, MPI_COMM_WORLD);
        destino=(world_rank+1)%world_size;
        MPI_Irecv(&j, 1, MPI_INT,  MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &request);
    while (!recibido){
      // Envio un mensaje con mi ID
      // En el arreglo
      // Para ser el master
      //printf("[%d] Destino: %d\n",world_rank, destino);
      i=world_rank;
      MPI_Send(&i, 1, MPI_INT, destino, 1, MPI_COMM_WORLD);// Espero retroalimentación para ver si le llego
      sleep(2);
        // Esperando para ver si responde
        int flag = 0;
        // Probando si llego mensaje
        MPI_Test(&request, &flag, &status);
        if (flag){
          // El proceso recibió el menasaje
          // Ya puedo seguir
          //printf("nodo %d respondio a %d\n ",status.MPI_SOURCE, world_rank);
          recibido = 1;
        }else{
          //printf("nodo %d no respondio a %d\n ",destino, world_rank);
        }
        // Envio al siguiente nodo
        destino++;
        if (destino == world_size)
        {
          destino =0;
          // printf("Ningún proceso recibió mi mensaje, vuelvo a empezar\n");
        }
      }
        i=world_rank;
    }    
    c++;
  }
  
  printf("%d \n",world_rank);
  }
  MPI_Finalize();
  return 0;
}