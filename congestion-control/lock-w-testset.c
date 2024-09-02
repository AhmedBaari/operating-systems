#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

atomic_int lock = 0; // Global lock variable

int test_and_set(atomic_int *target)
{
    return atomic_exchange(target, 1);
}

void *critical_section(void *arg)
{
    int id = *(int *)arg;

    // Entry Section
    while (test_and_set(&lock) == 1)
        ; // Busy-waiting with atomic operation

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
