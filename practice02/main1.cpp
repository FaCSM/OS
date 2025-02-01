#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define COUNT 10
using namespace std;
bool thread1_finished = false;
bool thread2_finished = false;
void *thread1(void *arg) {
  int i;
  while(!thread1_finished){
  for (i = 0; i < COUNT; i++) {
    printf("1");
    fflush(stdout);
    sleep(1);
  }
  sleep(1);}
  return NULL;
}

void *thread2(void *arg) {
  int i;
  while(!thread2_finished){
  for (i = 0; i < COUNT; i++) {
    printf("2");
    fflush(stdout);
    sleep(1);
  }
  sleep(1);}
  return NULL;
}

int main() {
  pthread_t t1, t2;
  printf("prog1\n");        
  pthread_create(&t1, NULL, thread1, NULL);
  pthread_create(&t2, NULL, thread2, NULL);
    cout << "Нажмите Enter для завершения...\n" << endl;
    getchar();
    thread1_finished = true;
    thread2_finished = true;    
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
