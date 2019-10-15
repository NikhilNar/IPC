#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

main() {

key_t key=1235;
int shm_id;
void *shm;
char *message;
message = malloc(10*sizeof(char));
shm_id = shmget(key,10*sizeof(char),NULL);
shm = shmat(shm_id,NULL,NULL);
if(shm == NULL)
{
printf("error");
}
sscanf(shm,"%s",message);
printf("\n message = %s\n",message);
}