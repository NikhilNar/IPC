#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

main()
{

    key_t key = 1235;
    int shm_id;
    void *shm;
    char *message = "hello";
    shm_id = shmget(key, 10 * sizeof(char), IPC_CREAT);
    shm = shmat(shm_id, NULL, NULL);
    sprintf(shm, "%s", message);
}
