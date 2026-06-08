// Readers-Writers Problem with Writer Priority
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt, mutex, readTry, wmutex;
int readcount = 0, writecount = 0;

void* reader(void* arg) {
    sem_wait(&readTry);
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);
    sem_post(&readTry);

    printf("Reader is reading\n");

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&mutex);

    return NULL;
}

void* writer(void* arg) {
    sem_wait(&wmutex);
    writecount++;
    if (writecount == 1)
        sem_wait(&readTry);
    sem_post(&wmutex);

    sem_wait(&wrt);
    printf("Writer is writing\n");
    sem_post(&wrt);

    sem_wait(&wmutex);
    writecount--;
    if (writecount == 0)
        sem_post(&readTry);
    sem_post(&wmutex);

    return NULL;
}

int main() {
    pthread_t r[3], w[2];

    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);
    sem_init(&readTry, 0, 1);
    sem_init(&wmutex, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, NULL);

    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, NULL);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);

    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    return 0;
}