#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ 27

main()
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    char line[1024];

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 75678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0777)) < 0)
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

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
    int i = 0;
    while (i < 5)
    {
        s = shm;
        printf("Enter message =");
        gets(line);
        if(strstr(line, "C00l")){
            char *ptr = &line[0];
            while(*ptr!='\0'){  
                *s++ = *ptr;
                ptr++;
            }
            *s = NULL;
            

            /*
         * Finally, we wait until the other process 
         * changes the first character of our memory
         * to '*', indicating that it has read what 
         * we put there.
         */
            while (*shm != '*')
                sleep(1);
            }
        i++;
    }

    exit(0);
}
