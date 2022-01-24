#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
   printf("%s %d %s","Идентификатор пользователя:",getuid(),"\n");
   printf("%s %d %s","Идентификатор группы:",getgid(),"\n");

   return 0;
}