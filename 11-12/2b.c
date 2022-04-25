#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int msqid;
    char pathname[] = "2a.c";
    key_t key;
    int len, maxlen;

    struct mymsgbuf {
        long mtype;
        struct {
            int int_info;
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

    for (int i = 1; i <= 5; ++i) {
        maxlen = sizeof(mybuf.info);

        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0) < 0) {
            printf("Can't receive message from queue\n");
            exit(-1);
        }

        printf("Message type = %ld, int_info = %i\n", mybuf.mtype, mybuf.info.int_info);
    }

    for (int i = 1; i <= 5; ++i) {
        mybuf.mtype = 2;
        mybuf.info.int_info = 2504;
        len = sizeof(mybuf.info);

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    return 0;
}