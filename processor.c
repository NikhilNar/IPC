#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MEMSIZE 27

main()
{
    int shmid;
    key_t key;
    char *shm, *s, *copy, *copy1;
    FILE *fPtr;

    // name of the shared memory segment
    key = 75678;

    // create secrets.out file
    fPtr = fopen("secrets.out", "w");
    if (fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(1);
    }
    /*
     * Find the segment.
     */
    if ((shmid = shmget(key, MEMSIZE, 0777)) < 0)
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
     * Continue reading the secret code from the shared memory.
     * End the program if the word exit occurs in the message.
     * The file should be closed to persist the data on the file.
     * The problem is if I close the file inside the while loop then it will override the
     * previous data. Hence the mechanism of exit keyword is added to close the program and persist 
     * the secret codes successfully in the file secrets.out
     */
    while (1)
    {

        if (*shm != '*')
        {
            char charArray[1];
            int noOfDigits = 0;
            char digitsToChar[10];
            char message[100];
            int j = 0;
            for (s = shm; *s != NULL; s++)
            {
                if (isdigit(*s))
                    noOfDigits++;
                message[j++] = *s;
            }
            message[j] = '\0';
            printf("Message entered =%s", message);

            if (strstr(message, "exit"))
            {
                break;
            }

            // write secret code and no of digits in the secrets.out file.
            fputs(message, fPtr);
            charArray[0] = ' ';
            fputs(charArray, fPtr);
            sprintf(digitsToChar, "%d", noOfDigits);
            fputs(digitsToChar, fPtr);
            sprintf(digitsToChar, "%s", "");
            charArray[0] = '\n';
            fputs(charArray, fPtr);

            // Send the acknowledgement to the receiver that the message is read
            // by setting the shared memory to "*"
            *shm = '*';
        }
    }

    fclose(fPtr);

    exit(0);
}
