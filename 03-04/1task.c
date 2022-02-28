#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
   printf("%s %d %s","Идентификатор процесса:",getpid(),"\n");
   printf("%s %d %s","идентификатор родительского процесса:",getppid(),"\n");
   
   return 0;
}