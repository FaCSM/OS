#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT 10
using namespace std;
pthread_mutex_t mutex;
bool thread1_finished = false;
bool thread2_finished = false;
void *thread1(void *arg) {
  int i;
  while(!thread1_finished){
  pthread_mutex_lock(&mutex);
  for (i = 0; i < COUNT; i++) {
    
    printf("1");
    fflush(stdout);
    sleep(1);
    
  }
  pthread_mutex_unlock(&mutex);
  sleep(1);}
  return NULL;
}

void *thread2(void *arg) {
  int i;
  while(!thread1_finished){
  pthread_mutex_lock(&mutex);
  for (i = 0; i < COUNT; i++) {
    
    printf("2");
    fflush(stdout);
    sleep(1);
    
  }
  pthread_mutex_unlock(&mutex);
  sleep(1);}
  return NULL;
}

int main() {
  pthread_t t1, t2;
  printf("prog2\n");
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
