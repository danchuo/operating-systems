#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
   int pid = fork();

   if (pid == -1) {  
    printf("Ошибка.\n");
	exit(-1);
   } else if (pid == 0) {
    printf("Ребёнок:\nPID = %d\nPPID = %d\n", getpid(), getppid()); 
	(void) execle("/bin/cat", "/bin/cat", "3.c", 0, envp);
    printf("Error on program start\n");
    exit(-1);
   } else {
    printf("Родитель:\nPID = %d\nPPID = %d\nPID ребёнка = %d\n", getpid(), getppid(), pid);
   }
   
   return 0;
}