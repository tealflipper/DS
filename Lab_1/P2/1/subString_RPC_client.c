/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "subString_RPC.h"


void
substring_1(str s1,str s2,char *host)
{
	CLIENT *clnt;
	int  *res;
	printf("%s\n%s\n",s1.arr,s2.arr);

#ifndef	DEBUG
	clnt = clnt_create (host, SUBSTRING, SUBSTRING_1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	res = issubstring_1(s1, s2, clnt);
	if (res == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}else if (*res == -1) printf ("Not present\n");
	else printf("Present at index %d\n", *res);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

int copyString(char* to, char* from){
   int i=0;
   while(from[i]!=0){
     to[i]=from[i];
     i++;
   }
   return i;
 }


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 3) {
		printf ("usage: %s server_host string1 string2 \n", argv[0]);
		exit (1);
	}
	host = argv[1];
	str s1;
	s1.ln=copyString(s1.arr,argv[2]);
	str s2;
	s2.ln=copyString(s2.arr,argv[3]);
	substring_1 (s1,s2,host);
exit (0);
}
