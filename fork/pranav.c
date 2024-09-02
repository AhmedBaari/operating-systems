#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    if (fork()&& fork() || fork())
        fork();
    printf("ID: %d\t", getpid());
    printf("PAR: %d\t", getppid());
    printf("\n");
    return 0;
}
