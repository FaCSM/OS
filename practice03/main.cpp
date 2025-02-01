#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
int in_critical_section = 0;

int thread_done1 = 0;
int thread_done2 = 0;

int pipefd[2];

void *thread1(void *arg) {
    char buffer[256];
    pid_t pid;

    while (!thread_done1) {
        pid = getpid();
        sprintf(buffer, "PID: %d\n", pid);

        while (in_critical_section); 
        in_critical_section = 1;

        int bytes_written = write(pipefd[1], buffer, strlen(buffer));
        if (bytes_written == -1) {
            perror("write");
            exit(1);
        }

        for (int i = 0; i < 1000000; i++);  

        in_critical_section = 0; 

        sleep(1);
    }

    return NULL;
}

void *thread2(void *arg) {
    char buffer[256];

    while (!thread_done2) {
        memset(buffer, 0, sizeof(buffer));

        int bytes_read = read(pipefd[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read");
            exit(1);
        } else if (bytes_read == 0) {
            break;
        }

        printf("%s", buffer);
    }

    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    int rv;

    rv = pipe(pipefd);
    if (rv == -1) {
        perror("pipe");
        exit(1);
    }

    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    printf("Press Enter to terminate...\n");
    getchar();

    thread_done1 = 1;
    thread_done2 = 1;

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
