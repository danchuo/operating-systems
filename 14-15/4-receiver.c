#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sendpid;
int number = 0b11111111111111111111111111111111;
int step = 0;

void get_zero() {
  number = number ^ (1 << step);
  step++;
  if (step == 32) {
    printf("Get number: %d\n", number);
    exit(0);
  } else {
    printf("Get %d bit: %d\n", step, 0);
    kill(sendpid, SIGUSR1);
  }
}

void get_one() {
  step++;
  if (step == 32) {
    printf("Get number %d\n", number);
    exit(0);
  } else {
    printf("Get %d bit: %d\n", step, 1);
    kill(sendpid, SIGUSR1);
  }
}

int main(void) {
  (void)signal(SIGUSR1, get_zero);
  (void)signal(SIGUSR2, get_one);

  printf("My PID: %d\n", getpid());
 
  printf("Enter sender\'s PID: ");
  scanf("%d", &sendpid);

  while(1) {};
}