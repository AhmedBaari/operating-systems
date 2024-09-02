#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

int flag[2] = {FALSE, FALSE}; // FLAG array to indicate desire to enter the critical section
int turn = 0;                 // TURN variable to indicate whose turn it is

void *process(void *arg)
{
    int id = *(int *)arg;
    int other = 1 - id;

    for (int i = 0; i < 3; i++)
    { // Each process tries to enter critical section 3 times
        // Entry Section
        flag[id] = TRUE;
        turn = other;

        while (turn == other && flag[other] == TRUE)
            ; // Busy-wait if it's the other process's turn and it wants to enter

        // Critical Section
        printf("Process %d is in the critical section\n", id);
        sleep(1); // Simulate some work in the critical section

        // Exit Section
        flag[id] = FALSE;
        printf("Process %d is leaving the critical section\n", id);

        // Remainder Section
        sleep(1); // Simulate some work outside the critical section
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int id1 = 0, id2 = 1;

    // Creating two threads
    pthread_create(&t1, NULL, process, &id1);
    pthread_create(&t2, NULL, process, &id2);

    // Joining threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
