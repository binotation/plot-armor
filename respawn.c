#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Before child execs
#define CHLD_INIT_ROUTINE() {\
    freopen(stdout_redirect, "a+", stdout);\
    freopen(stderr_redirect, "a+", stderr);\
    execvp(binpath, bin_args);\
}

static char *binpath;
static char *stdout_redirect;
static char *stderr_redirect;
static char **bin_args;

void cpy_slice_into(char **args, char **argv_slice) {
    int i = -1;
    while (argv_slice[++i] != 0) {
        args[i] = argv_slice[i];
    }
    args[i] = 0;
}

void child_exit_handler(int sig) {
    if (!fork()) {
        CHLD_INIT_ROUTINE()
    }
}

int main(int argc, char **argv) {
    if (argc < 4) {
        fputs("Usage: respawn binpath stdout_redirect stderr_redirect bin_args...\n", stderr);
        return 1;
    }

    // Initialize SIGCHLD handler
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = child_exit_handler;
    sigaction(SIGCHLD, &sa, NULL);

    binpath = argv[1];
    stdout_redirect = argv[2];
    stderr_redirect = argv[3];

    bin_args = (char**)malloc(sizeof(char*) * (argc - 2));
    cpy_slice_into(bin_args, &argv[3]);
    bin_args[0] = binpath;

    if (!fork()) {
        CHLD_INIT_ROUTINE()
    } else {
        while (1) { wait(0); }
    }
}
