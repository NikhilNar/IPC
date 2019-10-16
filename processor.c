#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{

    key_t key = 3456;
    int shm_id;
    void *shm;
    char *message;
    int i = 0;
    while (1)
    {
        message = malloc(10 * sizeof(char));
        shm_id = shmget(key, 10 * sizeof(char), IPC_CREAT | 0777);
        shm = shmat(shm_id, NULL, NULL);
        if (shm == NULL)
        {
            printf("error");
        }
        sscanf(shm, "%s", message);
        printf("\n message = %s\n", message);
    }

    return 0;
}