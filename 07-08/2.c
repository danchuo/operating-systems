#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy)
{
  pthread_t thid;
  thid = pthread_self();

  a = a + 1;

  printf("Thread %lu, Calculation result: %d\n", thid, a);
  return NULL;
}

int main()
{
  pthread_t thid, mythid, thid3; 
  int result; 

  result = pthread_create (&mythid, (pthread_attr_t *)NULL, mythread, NULL);

  if (result != 0) {
    printf ("Error on 1 thread create, return value: %d\n", result);
    exit(-1);
  }

  printf("Thread %lu created\n", mythid);

  result = pthread_create (&thid3, (pthread_attr_t *)NULL, mythread, NULL);

  if (result != 0) {
    printf ("Error on 2 thread create, return value: %d\n", result);
    exit(-1);
  }

  printf("Thread %lu created\n", thid3);

  thid = pthread_self();

  a = a + 1;

  printf("Thread %lu, Calculation result: %d\n", thid, a);

  pthread_join(mythid, (void **)NULL);
  pthread_join(thid3, (void **)NULL);

  return 0;
}