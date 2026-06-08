#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Page Replacement Algorithms: FIFO, LRU, Optimal
#define MAX 100

int ref[MAX];

// Generate random reference string
void generate(int n)
{
    for(int i = 0; i < n; i++)
        ref[i] = rand() % 10;
}

// FIFO
int fifo(int n, int f)
{
    int frames[10], front = 0, faults = 0;

    for(int i = 0; i < f; i++)
        frames[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
            if(frames[j] == ref[i])
                found = 1;

        if(!found)
        {
            frames[front] = ref[i];
            front = (front + 1) % f;
            faults++;
        }
    }
    return faults;
}

// LRU
int lru(int n, int f)
{
    int frames[10], time[10];
    int faults = 0, t = 0;

    for(int i = 0; i < f; i++)
        frames[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
        {
            if(frames[j] == ref[i])
            {
                found = 1;
                time[j] = t++;
            }
        }

        if(!found)
        {
            int min = 0;
            for(int j = 1; j < f; j++)
                if(time[j] < time[min])
                    min = j;

            frames[min] = ref[i];
            time[min] = t++;
            faults++;
        }
    }
    return faults;
}

// Optimal
int optimal(int n, int f)
{
    int frames[10], faults = 0;

    for(int i = 0; i < f; i++)
        frames[i] = -1;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
            if(frames[j] == ref[i])
                found = 1;

        if(!found)
        {
            int pos = -1, farthest = i;

            for(int j = 0; j < f; j++)
            {
                int k;
                for(k = i + 1; k < n; k++)
                    if(frames[j] == ref[k])
                        break;

                if(k == n)
                {
                    pos = j;
                    break;
                }

                if(k > farthest)
                {
                    farthest = k;
                    pos = j;
                }
            }

            if(pos == -1)
                pos = 0;

            frames[pos] = ref[i];
            faults++;
        }
    }
    return faults;
}

// MAIN
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <length> <frames>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int f = atoi(argv[2]);

    srand(time(0));
    generate(n);

    printf("Reference string:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", ref[i]);

    printf("\n\nFIFO Faults = %d\n", fifo(n, f));
    printf("LRU Faults = %d\n", lru(n, f));
    printf("Optimal Faults = %d\n", optimal(n, f));

    return 0;
}