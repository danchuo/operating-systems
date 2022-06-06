#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int received = 1;

void waiting() {
  received = 1;
}

int main(void) {
  (void)signal(SIGUSR1, waiting);

  printf("My PID: %d\n", getpid());

  int recpid; 
  printf("Enter receiver\'s PID: ");
  scanf("%d", &recpid);

  int number;
  printf("Enter number: ");
  scanf("%d", &number);

  for (int i = 0; i < 32; ++i) {
    if ((number & (1 << i)) == 0) {
      kill(recpid, SIGUSR1);
    } else {
      kill(recpid, SIGUSR2);
    }
    received = 0;
    while (i != 31 && received == 0) {}
  }

  printf("Send number: %d\n", number);
  return 0;
}