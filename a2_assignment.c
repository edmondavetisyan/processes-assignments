#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void print_status(const char *tag, int status) {
    if (WIFEXITED(status)) {
        printf("%s exited normally with code %d\n", tag, WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("%s killed by signal %d\n", tag, WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("%s stopped by signal %d\n", tag, WSTOPSIG(status));
    } else {
        printf("%s ended with unknown status\n", tag);
    }
}

int main(void) {
    setbuf(stdout, NULL);

    pid_t c1 = fork();
    if (c1 < 0) { perror("fork c1"); return 1; }
    if (c1 == 0) { _exit(42); }

    pid_t c2 = fork();
    if (c2 < 0) { perror("fork c2"); return 1; }
    if (c2 == 0) { _exit(7); }

    int status2 = 0; if (waitpid(c2, &status2, 0) < 0) { perror("waitpid c2"); return 1; }
    print_status("child2", status2);

    int status1 = 0; pid_t got = wait(&status1);
    if (got < 0) { perror("wait any"); return 1; }
    print_status("child1", status1);

    return 0;
}

