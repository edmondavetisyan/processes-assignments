#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    setbuf(stdout, NULL);
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        printf("[child]  PID=%d, PPID=%d\n", getpid(), getppid());
        _exit(0);
    } else {
        printf("[parent] PID=%d (child PID=%d)\n", getpid(), pid);
    }
    return 0;
}

