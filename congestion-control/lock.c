#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int lock = 0; // Global lock variable

void *critical_section(void *arg)
{
    int id = *(int *)arg;

    // Entry Section
    while (lock != 0)
        ; // Busy-waiting
    lock = 1;

    // Critical Section
    printf("Process %d is in the critical section\n", id);
    sleep(1); // Simulate some work in the critical section

    // Exit Section
    lock = 0;
    printf("Process %d is leaving the critical section\n", id);

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // Creating two threads
    pthread_create(&t1, NULL, critical_section, &id1);
    pthread_create(&t2, NULL, critical_section, &id2);

    // Joining threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
