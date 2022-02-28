#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
	printf("Аргументы командной строки:\n");
	
	for(int i = 0; i < argc; ++i) {
		printf("%d.) %s\n",i , argv[i]);
	}
	
	printf("\nПараметры окружающей среды процесса:\n");
	
	int j = 0;
	while(envp[j] != 0) {
		printf("%d.) %s\n",j , envp[j]);
		++j;
	}
	return 0;
}