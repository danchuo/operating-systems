

// S = 0
// for: {
// (parent)
//  write()
//  A(S,2)
//  Z(S)
//  read()
//  (child)
//  D(S,1)
//  read()
//  write()
//  D(S,1)}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main()
{
  int fd[2], result;
  size_t size;
  char  message[16];

  char pathname[] = "3.c";
  key_t key;
  struct sembuf mybuf;
  int semid;

  int N; // N >= 2
  scanf("%d", &N);

  if (pipe(fd) < 0) {
    printf("Can\'t open pipe\n");
    exit(-1);
  }

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get semaphore set\n");
    exit(-1);
  }

  result = fork();
  if (result < 0) {
    printf("Can\'t fork child\n");
    exit(-1);
  }  

  for (int i = 0; i < N; ++i) {
    if (result > 0) {
      /* parent */
      // write
      size = write(fd[1], "Hi from parent!", 16);
      if (size != 16) {
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      // A(S,2)
      mybuf.sem_num = 0;
      mybuf.sem_op = 2;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }

      // Z(S)
      mybuf.sem_num = 0;
      mybuf.sem_op = 0;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }

      // read
      size = read(fd[0], message, 16);
      if (size != 16) {
        printf("Can\'t read string from pipe\n");
        exit(-1);
      }

      printf("Read from pipe: %d %s\n", i, message);
    } else {
      /* child */

      // D(S,1)
      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }

      // read
      size = read(fd[0], message, 16);
      if (size != 16) {
        printf("Can\'t read string from pipe\n");
        exit(-1);
      }

      printf("Read from pipe: %d %s\n", i, message);

      // write
      size = write(fd[1], "Hi from chiild!", 16);
      if (size != 16) {
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      // D(S,1)
      mybuf.sem_num = 0;
      mybuf.sem_op = -1;
      mybuf.sem_flg = 0;
      if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
      }
    }
  }

  if (close(fd[0]) < 0) {
    printf("Can\'t close reading side of pipe\n"); 
    exit(-1);
  }

  if (close(fd[1]) < 0) {
    printf("Can\'t close writing side of pipe\n"); 
    exit(-1);
  }

  return 0;
}