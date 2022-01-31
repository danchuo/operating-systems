#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
   int pid = fork();

   if (pid == -1) {  
    printf("Ошибка.\n");
   } else if (pid == 0) {
    printf("Ребёнок:\nPID = %d\nPPID = %d\n", getpid(), getppid()); 
   } else {
    printf("Родитель:\nPID = %d\nPPID = %d\nPID ребёнка = %d\n", getpid(), getppid(), pid);
   }
   
   
   return 0;
}