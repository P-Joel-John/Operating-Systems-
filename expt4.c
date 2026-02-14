//parent and child process
#include <stdio.h>
#include <unistd.h>functions 
#include <sys/types.h>//pid_t

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
    }
    else if (pid == 0) {
        // Child process
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        sleep(30);   // keeps child alive
    }
    else {
        // Parent process,returns child's pid to pid variable  
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        sleep(30);   // keeps parent alive
    }

    return 0;
}

