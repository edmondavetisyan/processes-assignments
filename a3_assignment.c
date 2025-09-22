#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void cleanup1(void) { puts("atexit: cleanup1"); }
static void cleanup2(void) { puts("atexit: cleanup2"); }

int main(int argc, char **argv) {
    setbuf(stdout, NULL);
    if (atexit(cleanup1) != 0 || atexit(cleanup2) != 0) {
        perror("atexit");
        return 1;
    }

    puts("main: running");

    if (argc > 1) {
        puts("main: early exit via exit(0)");
        exit(0);
    }

    puts("main: normal return");
    return 0;
}

