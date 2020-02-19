#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define MAX_PROCESOS 20
#define MASTER 0 /*El nodo maestro será el proceso 0, al igual que en los subgrupos*/
#define TRUE 1
#define FALSE 0
int iIsInGroup (int *piGroup, int iLenGroup, int iId)
{
  int i;
  for (i=0; i<iLenGroup; i++) 
  if (iId==piGroup[i]) return (TRUE);
  return (FALSE);
}
int main (int iArg, char *spcArgv[])
{

  int iId, iNProc, i, iIdGroup, iEnvio;
  int siGrupo1[MAX_PROCESOS], iNGrupo1; //Los procesos en el grupo 1 y su número
  int siGrupo2[MAX_PROCESOS], iNGrupo2; //Los procesos en el grupo 2 y su número
  //MPI_Group smpigGrupoGbl;
  //MPI_Group smpigGrupo1, smpigGrupo2;
  //MPI_Comm smpicGrupoComm1, smpicGrupoComm2;
  

  printf("7\n");
  MPI_Init (&iArg, &spcArgv);
  //Determinamos el número de procesos del grupo global
  MPI_Comm_rank (MPI_COMM_WORLD, &iId); //Para obtener el ID
  MPI_Comm_size (MPI_COMM_WORLD, &iNProc); //Para obtener el número de procesos
  /* 
  
  if ((iNProc<4)||(iNProc>MAX_PROCESOS))
  { //Necesitamos más procesos, pero no tantos
    MPI_Finalize ();
    return (0);
  }
  for (i=0, iNGrupo1=0, iNGrupo2=0; i<iNProc; i++)
  { //Note que los procesos 0 y 1 serán los procesos 0 de cada grupo
    if (i%2)
    { //1, 3, 5, 7, ...
      siGrupo1[iNGrupo1] = i; iNGrupo1++;
    }
    else
    { //0, 2, 4, 6, ...
      siGrupo2[iNGrupo2] = i; iNGrupo2++;
    }
  }
  //Ademas el proceso MASTER estará en ambos grupos
  siGrupo1[iNGrupo1] = MASTER; iNGrupo1++;
  if (iId==MASTER)
  {
    printf ("Hay %d nodos, repartidos:\n", iNProc);
    printf ("Grupo 1(%d): ", iNGrupo1);
    for (i=0; i<iNGrupo1; i++) printf ("%d ", siGrupo1[i]);
    printf ("\nGrupo 2(%d): ", iNGrupo2);
    for (i=0; i<iNGrupo2; i++) printf ("%d ", siGrupo2[i]);
    printf ("\n");
  }
  /*
  MPI_Barrier (MPI_COMM_WORLD); //Esperamos a los nodos
 //Manejador del grupo global
 MPI_Comm_group (MPI_COMM_WORLD, &smpigGrupoGbl);
 MPI_Group_incl (smpigGrupoGbl, iNGrupo1, siGrupo1, &smpigGrupo1);
 MPI_Comm_create (MPI_COMM_WORLD, smpigGrupo1, &smpicGrupoComm1);
 if ((smpicGrupoComm1==MPI_COMM_NULL)&&(iIsInGroup(siGrupo1, iNGrupo1, iId)))
 { //Si esta en el grupo y no se pudo crear
 printf ("Error en comunicadores Grupo 1, nodo %d.\n", iId);
 MPI_Finalize ();
 return (0);
 }
 MPI_Group_incl (smpigGrupoGbl, iNGrupo2, siGrupo2, &smpigGrupo2);
 MPI_Comm_create (MPI_COMM_WORLD, smpigGrupo2, &smpicGrupoComm2);
 if ((smpicGrupoComm2==MPI_COMM_NULL)&&(iIsInGroup(siGrupo2, iNGrupo2, iId)))
 { //Si esta en el grupo y no se pudo crear
 printf ("Error en comunicadores Grupo 2, nodo %d.\n", iId);
 MPI_Finalize ();
 return (0);
 }

 if (iId%2) MPI_Comm_rank (smpicGrupoComm1, &iIdGroup);
 else MPI_Comm_rank (smpicGrupoComm2, &iIdGroup);
 printf ("Nodo %d, en el grupo soy %d, quedo a la espera\n", iId, iIdGroup);
 if (iId%2)
 { //Separamos los grupos
 if (iIdGroup==MASTER)
 { //El MASTER envia
 iEnvio = 100; 
 MPI_Bcast (&iEnvio, 1, MPI_INT, MASTER, smpicGrupoComm1);
 }
 else
 { //Los demás reciben
 MPI_Bcast (&iEnvio, 1, MPI_INT, MASTER, smpicGrupoComm1);
 printf ("Soy %d global, pero en el grupo 1 soy %d, recibi: %d\n", iId, iIdGroup, iEnvio);
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
 printf ("Soy %d global, pero en el grupo 2 soy %d, recibi: %d\n", iId, iIdGroup, iEnvio);
 }
 }
 usleep ((iId+1)*100000);
 MPI_Barrier (MPI_COMM_WORLD); //Para asegurar la creacion

 if ((iId%2)||(iId==MASTER))
 { //Todos liberan su respectivo grupo
 printf ("Nodo %d liberando grupo 1\n", iId);
 MPI_Comm_free (&smpicGrupoComm1);
 MPI_Group_free (&smpigGrupo1);
 }
 if ((!(iId%2))||(iId==MASTER))
 { //Todos liberan su respectivo grupo
 printf ("Nodo %d liberando grupo 2\n", iId);
 MPI_Comm_free (&smpicGrupoComm2);
 MPI_Group_free (&smpigGrupo2);
 }
 MPI_Barrier (MPI_COMM_WORLD); //Para asegurar la liberación
  */
 MPI_Finalize ();
 return (0);
 } 