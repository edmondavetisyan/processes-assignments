#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    int do_wait = (argc > 1 && argv[1][0] == 'w'); // pass "wait" to reap

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        printf("[child] PID=%d exiting now\n", getpid());
        _exit(0);
    }

    if (!do_wait) {
        printf("[parent] PID=%d not waiting; sleep 10s (inspect zombie with ps/top/htop)\n", getpid());
        sleep(10);
        return 0;
    } else {
        int status = 0;
        if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return 1; }
        printf("[parent] reaped child PID=%d, WIFEXITED=%d, code=%d\n",
               pid, WIFEXITED(status) ? 1 : 0, WIFEXITED(status) ? WEXITSTATUS(status) : -1);
        return 0;
    }
}

