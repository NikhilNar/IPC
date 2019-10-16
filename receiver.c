#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#define MEMSIZE 27

main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    char line[1024];

    // name of the shared memory segment
    key = 75678;

    // Create the segment with read and write permission
    if ((shmid = shmget(key, MEMSIZE, IPC_CREAT | 0777)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    // Attach the segment to the data space.
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    /*
     * Continue taking input from the user and publish it into the shared memory if the input has the secret code "C00l"
     * End the program if the word exit occurs in the user.
     * The details about the importance of exiting the code can be found in processor.c
     */

    while (1)
    {
        s = shm;
        printf("Enter message =");
        gets(line);
        if (strstr(line, "C00l") || strstr(line, "exit"))
        {
            char *ptr = &line[0];
            // parse the input and store it in the shared memory pointed by s.
            while (*ptr != '\0')
            {
                *s++ = *ptr;
                ptr++;
            }
            *s = NULL;

            if (strstr(line, "exit"))
            {
                break;
            }

            /*
            * Wait for the processor to read the secret code from the shared memory.
            * The processor writes back '*' into the shared memory which indicates that the message has 
            * been read successfully.
            */
            while (*shm != '*')
                sleep(1);
        }
    }

    exit(0);
}
