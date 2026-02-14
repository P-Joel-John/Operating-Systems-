//shared memory
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *data = (char *)shmat(shmid, NULL, 0);

    if (fork() == 0) {
        // Child
        char s1[100], s2[100], s3[100];
        sscanf(data, "%s %s %s", s1, s2, s3);
        sprintf(data, "%s %s %s", s1, s2, s3);
    } else {
        // Parent
        printf("Enter three strings:\n");
        scanf("%s %s %s", data, data + 30, data + 60);

        sleep(1);

        for (int i = 0; data[i] != '\0'; i++) {
            if (islower(data[i]))
                data[i] = toupper(data[i]);
            else if (isupper(data[i]))
                data[i] = tolower(data[i]);
        }

        printf("Final Output: %s\n", data);

        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}

