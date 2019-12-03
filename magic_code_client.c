/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "magic_code.h"


void
magic_code_prog_1(char *host)
{
	CLIENT *clnt;
	void  *result_1;
	char * magic_code_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, MAGIC_CODE_PROG, MAGIC_CODE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
    magic_code_1_arg = "C00lMessage";
	result_1 = magic_code_1(&magic_code_1_arg, clnt);
	if (result_1 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
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
	magic_code_prog_1 (host);
exit (0);
}
