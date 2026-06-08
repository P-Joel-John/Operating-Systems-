#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Disk Scheduling Algorithms: SSTF, LOOK, CSCAN
#define SIZE 10
#define MAX 5000

// Function to generate random requests
void generateRequests(int req[]) {
    for (int i = 0; i < SIZE; i++) {
        req[i] = rand() % MAX;
    }
}

// Sort array
void sort(int arr[]) {
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if (arr[i] > arr[j]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
}

// SSTF
int SSTF(int req[], int head) {
    int visited[SIZE] = {0};
    int total = 0;

    for (int i = 0; i < SIZE; i++) {
        int min = 999999, index = -1;

        for (int j = 0; j < SIZE; j++) {
            if (!visited[j]) {
                int dist = abs(head - req[j]);
                if (dist < min) {
                    min = dist;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += min;
        head = req[index];
    }
    return total;
}

// LOOK
int LOOK(int req[], int head) {
    int total = 0;
    sort(req);

    int i;
    for (i = 0; i < SIZE; i++) {
        if (req[i] >= head)
            break;
    }

    // Move right
    for (int j = i; j < SIZE; j++) {
        total += abs(head - req[j]);
        head = req[j];
    }

    // Move left
    for (int j = i - 1; j >= 0; j--) {
        total += abs(head - req[j]);
        head = req[j];
    }

    return total;
}

// CSCAN
int CSCAN(int req[], int head) {
    int total = 0;
    sort(req);

    int i;
    for (i = 0; i < SIZE; i++) {
        if (req[i] >= head)
            break;
    }

    // Move right
    for (int j = i; j < SIZE; j++) {
        total += abs(head - req[j]);
        head = req[j];
    }

    // Jump to start
    total += abs(head - (MAX - 1));
    head = 0;
    total += (MAX - 1);

    // Continue from beginning
    for (int j = 0; j < i; j++) {
        total += abs(head - req[j]);
        head = req[j];
    }

    return total;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <initial_head_position>\n", argv[0]);
        return 1;
    }

    int head = atoi(argv[1]);
    int req[SIZE];

    srand(time(NULL));
    generateRequests(req);

    printf("Disk Requests: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", req[i]);

    printf("\nInitial Head: %d\n", head);

    printf("\nTotal Head Movement:\n");
    printf("SSTF  = %d\n", SSTF(req, head));
    printf("LOOK  = %d\n", LOOK(req, head));
    printf("CSCAN = %d\n", CSCAN(req, head));

    return 0;
}