#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ 27

main()
{
    int shmid;
    key_t key;
    char *shm, *s, *copy, *copy1;
    FILE *fPtr;
    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 75678;
    fPtr = fopen("secrets.out", "w");
    if (fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(1);
    }
    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0777)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    while (1)
    {
        /*
        * Now read what the server put in the memory.
        */
        if (*shm != '*')
        {
            for (s = shm; *s != NULL; s++)
                fputs(*s, fPtr);
            fputs(' ', fPtr);
            fputs(2, fPtr);
            fputs('\n');
            /*
        * Finally, change the first character of the 
        * segment to '*', indicating we have read 
        * the segment.
        */
            *shm = '*';
        }
    }

    exit(0);
}
