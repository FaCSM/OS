#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
using namespace std;

pthread_mutex_t mutex;
bool thread1_finished = false;
bool thread2_finished = false;
void *thread1(void *arg) {
  int i;
  struct timespec tp;
  while(!thread1_finished){

    clock_gettime(CLOCK_REALTIME, &tp);
    tp.tv_sec += 1;
    int rv = pthread_mutex_timedlock(&mutex, &tp);
    if (rv == 0) {printf("1");pthread_mutex_unlock(&mutex);}
    
  }
  return NULL;
}

void *thread2(void *arg) {
  int i;
  struct timespec tp;
  while(!thread2_finished){

    clock_gettime(CLOCK_REALTIME, &tp);
    tp.tv_sec += 1;
    int rv = pthread_mutex_timedlock(&mutex, &tp);
    if (rv == 0) {printf("2");pthread_mutex_unlock(&mutex);}
    
  }
  return NULL;
}

int main() {
  pthread_t t1, t2;
  printf("prog3\n");
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&t1, NULL, thread1, NULL);
  pthread_create(&t2, NULL, thread2, NULL);
cout << "Нажмите Enter для завершения...\n" << endl;
    getchar();
    thread1_finished = true;
    thread2_finished = true; 
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_mutex_destroy(&mutex);
  return 0;
}
