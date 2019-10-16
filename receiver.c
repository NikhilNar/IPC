#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main()
{

    key_t key = 3456;
    int shm_id;
    void *shm;
    int i = 0;
    char message[1024];
    while (i < 5)
    {
        printf("Enter message =");
        gets(message);
        if (strstr(message, "C00L"))
        {
            shm_id = shmget(key, 10 * sizeof(char), IPC_CREAT | 0777);
            shm = shmat(shm_id, NULL, NULL);
            sprintf(shm, "%s", message);
        }

        i++;
    }
    return 0;
}
