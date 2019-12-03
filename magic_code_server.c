/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "magic_code.h"
#include <signal.h>

int noOfDigits = 0;
int noOfLines = 0;

void sigintHandler(int sig_num)
{
	printf("Total number of lines = %d", noOfLines);
	printf("\nTotal number of digits = %d", noOfDigits);
	printf("\n");
	exit(0);
}

void *
magic_code_1_svc(char **argp, struct svc_req *rqstp)
{
	static char *result;

	/*
	 * insert server code here
	 */
	printf("Remote procedure called now =====\n");
	printf("Remote procedure called %s\n", *argp);
	signal(SIGINT, sigintHandler);
	char *s;
	for (s = *argp; *s != NULL; s++)
	{
		if (isdigit(*s))
			noOfDigits++;
	}

	noOfLines++;

	return (void *)&result;
}
