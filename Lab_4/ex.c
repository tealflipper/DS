#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <mpi.h>
#define N 25
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
  int lastNode=(N-1-STAR);
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
  //Para poder agregar nodo maestro
  //neighbors[MASTER]=1;
}

int main (int iArg, char *spcArgv[])
{

  int iRank, totalProcesses, i, j, iIdGroup, iEnvio;
  int siGrupo[N][N], iNGrupo[N]; //procesos en grupos: siGrupo[Grupo][idGroupo] y numero de procesos en grupo: iNGrupo[group]
  int visitado=-1;
  int neighbors[N];
  MPI_Group smpigGrupoGbl; //grupo global
  MPI_Group smpigGrupo[N];
  MPI_Comm smpicGrupoComm[N];
  //for(i=0;i<totalProcesses;i++) iNGrupo[i]=0;


  MPI_Init (&iArg, &spcArgv);
  //Determinamos el número de procesos del grupo global
  MPI_Comm_rank (MPI_COMM_WORLD, &iRank); //Para obtener el ID
  MPI_Comm_size (MPI_COMM_WORLD, &totalProcesses); //Para obtener el número de procesos
  
  if ((totalProcesses<4)||(totalProcesses>N))
  { //Necesitamos más procesos, pero no tantos
    MPI_Finalize ();
    return (0);
  }
  //crear lista de nodos vecinos
  getNeighbors(iRank,neighbors);
  //crear grupo con vecinos del nodo
  for(i=0;i<totalProcesses;i++){
    if(neighbors[i]==1){
      siGrupo[iRank][iNGrupo[iRank]++]=i;
    }
  }/*
  //Ademas el proceso MASTER estará en ambos grupos
  siGrupo[iRank][iNGrupo[iRank]++]=MASTER;
 
  if (iRank==MASTER)
  {
    printf ("Hay %d nodos, repartidos:\n", totalProcesses);
    for(j=0;j<N;j++){
      printf ("Grupo %d(%d): ",j, iNGrupo[j]);
      for (i=0; i<iNGrupo[j]; i++) printf ("%d ", siGrupo[j][i]); 
    }
    printf ("\n");
  }
  
  MPI_Barrier (MPI_COMM_WORLD); //Esperamos a los nodos
 //Manejador del grupo global
 MPI_Comm_group (MPI_COMM_WORLD, &smpigGrupoGbl);
 for(i=0;i<N;i++){
  MPI_Group_incl (smpigGrupoGbl, iNGrupo[i], siGrupo[i], &smpigGrupo1);
  MPI_Comm_create (MPI_COMM_WORLD, smpigGrupo1, &smpicGrupoComm1);
  if ((smpicGrupoComm1==MPI_COMM_NULL)&&(iIsInGroup(siGrupo1, iNGrupo1, iRank)))
  { //Si esta en el grupo y no se pudo crear
    printf ("Error en comunicadores Grupo 1, nodo %d.\n", iRank);
    MPI_Finalize ();
    return (0);
  }
 }
 /*
 MPI_Group_incl (smpigGrupoGbl, iNGrupo2, siGrupo2, &smpigGrupo2);
 MPI_Comm_create (MPI_COMM_WORLD, smpigGrupo2, &smpicGrupoComm2);
 if ((smpicGrupoComm2==MPI_COMM_NULL)&&(iIsInGroup(siGrupo2, iNGrupo2, iRank)))
 { //Si esta en el grupo y no se pudo crear
 printf ("Error en comunicadores Grupo 2, nodo %d.\n", iRank);
 MPI_Finalize ();
 return (0);
 }
 */

 if (iRank%2) MPI_Comm_rank (smpicGrupoComm1, &iIdGroup);
 else MPI_Comm_rank (smpicGrupoComm2, &iIdGroup);
 printf ("Nodo %d, en el grupo soy %d, quedo a la espera\n", iRank, iIdGroup);
 if (iRank%2)
 { //Separamos los grupos
 if (iIdGroup==MASTER)
 { //El MASTER envia
 iEnvio = 100; 
 MPI_Bcast (&iEnvio, 1, MPI_INT, MASTER, smpicGrupoComm1);
 }
 else
 { //Los demás reciben
 MPI_Bcast (&iEnvio, 1, MPI_INT, MASTER, smpicGrupoComm1);
 printf ("Soy %d global, pero en el grupo 1 soy %d, recibi: %d\n", iRank, iIdGroup, iEnvio);
 }
 }
 else
 {
 if (iIdGroup==MASTER)
 { //El MASTER envia
 iEnvio = 200;
 MPI_Bcast (&iEnvio, 1, MPI_INT, MASTER, smpicGrupoComm2);
 }
 else
 { //Los demás reciben
 MPI_Bcast (&iEnvio, 1, MPI_INT, MASTER, smpicGrupoComm2);
 printf ("Soy %d global, pero en el grupo 2 soy %d, recibi: %d\n", iRank, iIdGroup, iEnvio);
 }
 }
 usleep ((iRank+1)*100000);
 MPI_Barrier (MPI_COMM_WORLD); //Para asegurar la creacion

 if ((iRank%2)||(iRank==MASTER))
 { //Todos liberan su respectivo grupo
 printf ("Nodo %d liberando grupo 1\n", iRank);
 MPI_Comm_free (&smpicGrupoComm1);
 MPI_Group_free (&smpigGrupo1);
 }
 if ((!(iRank%2))||(iRank==MASTER))
 { //Todos liberan su respectivo grupo
 printf ("Nodo %d liberando grupo 2\n", iRank);
 MPI_Comm_free (&smpicGrupoComm2);
 MPI_Group_free (&smpigGrupo2);
 }
 MPI_Barrier (MPI_COMM_WORLD); //Para asegurar la liberación
  /* 
  */
 MPI_Finalize ();
 return (0);
 } 