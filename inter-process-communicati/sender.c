/*
 Program: IPC using Message Queue (Sender)
 Task   : Send a string to receiver process
*/

#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg {
    long type;
    char text[100];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg message;

    printf("Enter string: ");
    scanf("%s", message.text);

    message.type = 1;   // message type 1
    msgsnd(msgid, &message, sizeof(message.text), 0);

    printf("String sent to receiver\n");
    return 0;
}

