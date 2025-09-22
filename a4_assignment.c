#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void report(const char *who, int status) {
    if (WIFEXITED(status)) {
        printf("%s exited with code %d\n", who, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("%s terminated by signal %d\n", who, WTERMSIG(status));
    } else {
        printf("%s ended (other)\n", who);
    }
}

int main(void) {
    setbuf(stdout, NULL);

    pid_t a = fork();
    if (a < 0) { perror("fork a"); return 1; }
    if (a == 0) { _exit(0); }

    pid_t b = fork();
    if (b < 0) { perror("fork b"); return 1; }
    if (b == 0) { _exit(1); }

    int st = 0;
    if (waitpid(a, &st, 0) < 0) { perror("waitpid a"); return 1; } report("child A", st);
    if (waitpid(b, &st, 0) < 0) { perror("waitpid b"); return 1; } report("child B", st);

    return 0;
}

