
//multithreading to calculate mean, median and standard deviation of an array of integers
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Global variables (shared by all threads)
int *arr;        // Array of integers
int n;           // Number of elements
float mean, median, stddev;

/* Thread function to calculate mean */
void *calculate_mean(void *arg)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += arr[i];

    mean = sum / n;

    pthread_exit(NULL);
}

/* Thread function to calculate median */
void *calculate_median(void *arg)
{
    int temp;

    /* Sorting the array (simple bubble sort) */
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    /* Finding median */
    if (n % 2 == 0)
        median = (arr[n/2 - 1] + arr[n/2]) / 2.0;
    else
        median = arr[n/2];

    pthread_exit(NULL);
}

/* Thread function to calculate standard deviation */
void *calculate_stddev(void *arg)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += (arr[i] - mean) * (arr[i] - mean);

    stddev = sqrt(sum / n);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2, tid3;

    /* Check for minimum input */
    if (argc < 2)
    {
        printf("minimum 1 value needed");
        return 1;
    }

    n = argc - 1;

    /* Allocate memory for array */
    arr = (int *)malloc(n * sizeof(int));

    /* Read integers from command line */
    for (int i = 0; i < n; i++)
        arr[i] = atoi(argv[i + 1]);

    /* Create threads */
    pthread_create(&tid1, NULL, calculate_mean, NULL);
    pthread_create(&tid2, NULL, calculate_median, NULL);

    /* Wait for mean thread before std deviation */
    pthread_join(tid1, NULL);

    pthread_create(&tid3, NULL, calculate_stddev, NULL);

    /* Wait for remaining threads */
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    /* Display results */
    printf("Mean = %.2f\n", mean);
    printf("Median = %.2f\n", median);
    printf("Standard Deviation = %.2f\n", stddev);

    free(arr);
    return 0;
}










