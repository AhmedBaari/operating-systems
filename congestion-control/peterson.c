#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_ITERATIONS 3 // Number of times each process enters the critical section

int turn;     // Variable to indicate whose turn it is
bool flag[2]; // Array to indicate the intent of each process

void *process(void *arg)
{
    int id = *(int *)arg;
    int other = 1 - id; // ID of the other process

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        // Entry Section
        flag[id] = true;
        turn = other;

        // Wait until it's this process's turn or the other process is not interested
        while (turn == other && flag[other])
            ;

        // Critical Section
        printf("Process %d is in the critical section (Iteration %d)\n", id, i + 1);
        sleep(1); // Simulate work in the critical section

        // Exit Section
        flag[id] = false;
        printf("Process %d is leaving the critical section (Iteration %d)\n", id, i + 1);

        // Remainder Section
        sleep(1); // Simulate work outside the critical section
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int id1 = 0, id2 = 1;

    // Initialize the flag array
    flag[0] = false;
    flag[1] = false;

    // Creating two threads
    pthread_create(&t1, NULL, process, &id1);
    pthread_create(&t2, NULL, process, &id2);

    // Joining threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
