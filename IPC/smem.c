#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SHMSZ 27

int main()
{
    printf("0");
    char c;
    printf("1");
    int shmid, k;
    printf("2");
    key_t key;
    printf("3");
    char *shm, *s;
    printf("Your key is 6543");
    key = 6543;
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
    {
        printf("error in shmget");
        return 1;
    }
    if ((shm = shmat(shmid, NULL, 0)) == (char *)-1)
    {
        printf("error in shmat");
        return 1;
    }
    s = shm;
    // printf("Enter value");
    for (c = 'a'; c < 'z'; c = c + 2)
    {
        *s = c;
        s++;
    }
    *s = '\0';
    while (*shm != '*')
        sleep(1);

    exit(0);
}
