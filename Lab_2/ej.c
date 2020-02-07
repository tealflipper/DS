#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#define FALSE 0
#define TRUE 1
#define PRINCIPAL 0 /*El nodo cero será el principal*/ 
#define NODO_DESTINO 1 /*Pues si son dos nodos y uno es 0, el otro debe ser 1*/
 int main(int iArgc, char *pscArgv[])
 {
 int iRank; /*Este es el idenficador de nodo*/
 int iSize; /*Número total de nodos*/
 int iFlag;
 MPI_Request mpirReq;
 unsigned int w, x, y, z;
 unsigned char bSalir;
 char scMsg[] = "puto.\n";
 char scRec[100];
 MPI_Status mpisEstado;
 MPI_Init (&iArgc, &pscArgv);
 MPI_Comm_size (MPI_COMM_WORLD, &iSize);
 MPI_Comm_rank (MPI_COMM_WORLD, &iRank);
 w = strlen (scMsg); /*Cuanto mide el mensaje*/
 if (iRank==PRINCIPAL)
 {
 printf ("Soy el nodo principal, haré tiempo y luego enviaré un mensaje.\n");
 for (x=0; x<100000; x++)
 for (y=0; y<1000; y++) z = x + y;
 printf ("Ahora enviaré el mensaje de forma sincrona..\n");
 MPI_Isend (scMsg, w+1, MPI_CHAR, NODO_DESTINO, 2, MPI_COMM_WORLD, &mpirReq);
 MPI_Isend (scMsg, w+1, MPI_CHAR, 2, 2, MPI_COMM_WORLD, &mpirReq);
 MPI_Isend (scMsg, w+1, MPI_CHAR, 3, 3, MPI_COMM_WORLD, &mpirReq);

 MPI_Isend (scMsg, w+1, MPI_CHAR, 3, 2, MPI_COMM_WORLD, &mpirReq);
 
 printf ("El mensaje fue enviado, pero aun no sé si ya se recibio.\n");
 }
 else
 {
 scRec[0] = 0;
 printf ("Soy el otro nodo, y estoy en espera de recibir un mensaje.\n");
 MPI_Irecv (scRec, w+1, MPI_CHAR, PRINCIPAL, 2, MPI_COMM_WORLD, &mpirReq);
 bSalir = FALSE;
 while (!bSalir)
 {
 MPI_Test (&mpirReq, &iFlag, &mpisEstado);
 if (iFlag) bSalir = TRUE;
 }
 printf ("Me enviaron: %s\n", scRec);
 printf ("TAG: %d, Origen: %d\n", mpisEstado.MPI_TAG, mpisEstado.MPI_SOURCE);
 }
 MPI_Finalize();
 return (0);
 } 