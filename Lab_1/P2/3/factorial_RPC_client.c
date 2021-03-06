/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "factorial_RPC.h"


void
factorial_1(char *host)
{
	CLIENT *clnt;
	long  *result_1;
	int fact_1_n;
	printf("dame n: ");
	scanf("%d",&fact_1_n);
#ifndef	DEBUG
	clnt = clnt_create (host, FACTORIAL, FACTORIAL_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = fact_1(fact_1_n, clnt);
	if (result_1 == (long *) NULL) {
		clnt_perror (clnt, "call failed");
	}else printf("%d! = %ld\n",fact_1_n,*result_1);
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
	factorial_1 (host);
exit (0);
}
