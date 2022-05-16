#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main() {
    int msqid;
    char pathname[] = "3-server.c";
    key_t key;
    int len, maxlen;

    struct mymsgbuf1 {
        long my_type;
        struct {
            pid_t client_pid; 
	    double client_request;
        } request;
    } request_buf;

    struct mymsgbuf2 {
        long my_type; 
        struct {
	    double server_response; 
        } response;
    } response_buf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can't get msqid\n");
        exit(-1);
    }
 
    while (1) {
        maxlen = sizeof(request_buf.request);
        if (len = msgrcv(msqid, (struct msgbuf *) &request_buf, maxlen, 1, 0) < 0) {
            printf("Can't receive message from queue\n");
            exit(-1);
        }

        response_buf.my_type = request_buf.request.client_pid;
        response_buf.response.server_response = request_buf.request.client_request * request_buf.request.client_request;
        len = sizeof(response_buf.response);
 
        if (msgsnd(msqid, (struct msgbuf *) &response_buf, len, 0) < 0) {
            printf("Can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    return 0;
}