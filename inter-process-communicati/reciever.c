/*
 Program: IPC using Message Queue (Receiver)
 Task   : Reverse the received string and send it back
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
    char rev[100];
    int i, len;

    msgrcv(msgid, &message, sizeof(message.text), 1, 0);

    len = strlen(message.text);
    for (i = 0; i < len; i++)
        rev[i] = message.text[len - i - 1];
    rev[len] = '\0';

    message.type = 2;
    strcpy(message.text, rev);
    msgsnd(msgid, &message, sizeof(message.text), 0);

    printf("Reversed string sent back\n");

    msgctl(msgid, IPC_RMID, NULL);  // remove queue
    return 0;
}

