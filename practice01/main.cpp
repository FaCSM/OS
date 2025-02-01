#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <csignal>


using namespace std;
pthread_t id1;
pthread_t id2;
pthread_t id3;
bool thread1_finished = false;
bool thread2_finished = false;
bool thread3_finished = false;
void *thread1(void *param) {
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);
    siginfo_t info;
    while (!thread2_finished) {
        cout << "поток 1 работает\n";
        sigwaitinfo(&sigset, &info);
        if (info.si_signo == SIGUSR1) {
            printf("Поток 1 получил сигнал SIGUSR1, значение %d\n", info.si_value.sival_int);
        }
        sleep(3);
    }
    return NULL;
}


void *thread2(void *param) {
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);
    siginfo_t info;
    while (!thread2_finished) {
        cout << "поток 2 работает\n";
        sigwaitinfo(&sigset, &info);
        if (info.si_signo == SIGUSR1) {
            printf("Поток 2 получил сигнал SIGUSR1, значение %d\n", info.si_value.sival_int);
        }
        sleep(3);
    }
    return NULL;
}
void *thread3(void *param){
    union sigval l{};

    while (!thread3_finished) {
        cout << "поток 3 работает\n";
        l.sival_int = 123;
        pthread_sigqueue(id1, SIGUSR1, l);
        l.sival_int = 12;
        pthread_sigqueue(id2, SIGUSR1, l);
        sleep(5);
    }
    return NULL;
}

int main() {

    int c;
    
    pthread_create(&id1, NULL, thread1, NULL);
    pthread_create(&id2, NULL, thread2, NULL);
    sleep(1);
    pthread_create(&id3, NULL, thread3, NULL);

    cout << "Нажмите Enter для завершения...\n" << endl;
    getchar();
    thread1_finished = true;
    thread2_finished = true;
    thread3_finished = true;
    pthread_join(id3, NULL);
    cout << "поток 3 завершен\n";
    pthread_join(id1, NULL);
    cout << "поток 1 завершен\n";
    pthread_join(id2, NULL);
    cout << "поток 2 завершен\n";

    sleep(3);
    return 0;
    
    

}