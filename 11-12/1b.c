#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main() {
    int msqid;
    char pathname[] = "1a.c";
    key_t key;
    int len, maxlen;

    struct mymsgbuf {
        long mtype;
        struct {
            int int_info;
            float float_info;
        } info;
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can't get msqid\n");
        exit(-1);
    }

    while (1) {
        maxlen = sizeof(mybuf.info);

        if (len = msgrcv(msqid, &mybuf, maxlen, 0, 0) < 0) {
            printf("Can't receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, NULL);
            exit(0);
        }

        printf("Message type = %ld, int_info = %i, float_info = %f\n", mybuf.mtype, mybuf.info.int_info, mybuf.info.float_info);
    }

    return 0;
}