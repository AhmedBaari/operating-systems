Strict alternation is a simple locking mechanism where processes take turns entering their critical sections in a fixed order (e.g., `P0`, `P1`, `P0`, `P1`, ...). This method guarantees mutual exclusion but does not satisfy the progress condition because a process may be forced to wait for its turn even when the other process has no interest in entering its critical section.

### C Code for Strict Alternation (Turn-by-Turn)

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int turn = 0;  // Global variable to keep track of whose turn it is

void* process(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 3; i++) {  // Each process tries to enter critical section 3 times
        // Entry Section
        while (turn != id);  // Busy-wait until it's this process's turn

        // Critical Section
        printf("Process %d is in the critical section\n", id);
        sleep(1);  // Simulate some work in the critical section

        // Exit Section
        turn = 1 - id;  // Give turn to the other process
        printf("Process %d is leaving the critical section\n", id);

        // Remainder Section
        sleep(1);  // Simulate some work outside the critical section
    }

    return NULL;
}

int main() {
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
```

### Explanation

- **Mutual Exclusion**: Mutual exclusion is guaranteed because only the process whose turn it is can enter the critical section.
- **Progress**: This method does **not** satisfy the progress condition. A process might have to wait for its turn even if the other process has no intention of entering the critical section.
- **Bounded Wait**: The wait is bounded because a process will always get its turn eventually.
- **Strict Alternation**: The processes alternate in a strict order, `P0` -> `P1` -> `P0` -> `P1`, regardless of whether a process wants to enter the critical section.

### Demonstration

When you run the code, you'll observe that the processes strictly alternate in entering the critical section. Even if one process finishes its work and is ready to enter the critical section again, it has to wait for the other process to take its turn, demonstrating the lack of progress.

This method, while simple, is not efficient in scenarios where one process does not want to enter the critical section, as it forces unnecessary waiting.