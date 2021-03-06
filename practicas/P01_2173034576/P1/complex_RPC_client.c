/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "complex_RPC.h"


void
complex_operaciones_1(char *host)
{
	CLIENT *clnt;
	complex  *z;
	complex x,y;
	double N;

#ifndef	DEBUG
	clnt = clnt_create (host, COMPLEX_OPERACIONES, COMPLEX_OPER_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	x.fReal = 10;  x.fImg = 20;
   y.fReal = 30;  y.fImg = 40;
   N = 0.1;   
   printf ("N = %f\nx = (%f) + (%f)i\ny = (%f) + (%f)i\n\n", N, x.fReal, x.fImg, y.fReal, y.fImg);
   z = scsuma_1 (x, y,clnt);
	if (z == (complex *) NULL) {
		clnt_perror (clnt, "call failed");
	}else printf ("z = x + y = (%f) + (%f)i\n", z->fReal, z->fImg);

	z = scproductoconescalar_1(x, N,clnt);
	if (z == (complex *) NULL) {
		clnt_perror (clnt, "call failed");
	}else printf ("z = x * N = (%f) + (%f)i\n", z->fReal, z->fImg);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	complex_operaciones_1 (host);
exit (0);
}
