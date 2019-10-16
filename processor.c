#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SHMSZ 27

main()
{
    int shmid;
    key_t key;
    char *shm, *s, *copy, *copy1;
    FILE *fPtr;
    fPtr = fopen("secrets.out", "w");
        if (fPtr == NULL)
            {
                /* File not created hence exit */
                printf("Unable to create file.\n");
                exit(1);
            }
    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 85678;
    
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
            printf("In if=========");
            char numberOfDigits[10];
            char characterArray[1];
            int noOfDigits = 0;
            char message[100];
            int i=0; 
            for (s = shm; *s != NULL; s++){
                putchar(*s);
                message[i] = *s;
                if(isdigit(*s))
                    noOfDigits++;
                //characterArray[0]=*s;
                //fputs(characterArray, fPtr);
                i++;
            }
            message[i]=' ';
            message[i+1]='\0';
            if(strcmp(message, "exit")==0)
                break;    
            printf("Message =====%s", message);  
            fputs(message, fPtr);
            
            sprintf(numberOfDigits, "%d", noOfDigits);
            printf("Total no of digits =%s", numberOfDigits);
            fputs(numberOfDigits, fPtr);
            sprintf(numberOfDigits, "%s", "");
            characterArray[0] = '\n';
            fputs(characterArray, fPtr);
            /*
        * Finally, change the first character of the 
        * segment to '*', indicating we have read 
        * the segment.
        */
            *shm = '*';
        }
        
    }
    fclose(fPtr);
    

    exit(0);
}
