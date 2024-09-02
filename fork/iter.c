#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int p = 0;
    for (int i = 0; i < 3; i++)
    {
        fork();
        printf("%d\t", getpid());
        //printf("ID: %d\t\n", );
        printf("PAR: %d\n", getppid());
        printf("\tX");
        // printf("i: %d\t", i);
    }
    return 0;
}