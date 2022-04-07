#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static char *filepath;
static char *stdout_redirect;
static char *stderr_redirect;
static char **bin_args;

void child_exit_handler(int sig) {
    if (!fork()) {
        freopen(stdout_redirect, "w+", stdout);
        freopen(stderr_redirect, "w+", stderr);
        execvp(filepath, bin_args);
    }
}

int main(int argc, char **argv) {
    if (argc < 4) {
        fputs("Usage: respawn filepath stdout_redirect stderr_redirect bin_args...\n", stderr);
        return 1;
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = child_exit_handler;
    sigaction(SIGCHLD, &sa, NULL);

    filepath = argv[1];
    stdout_redirect = argv[2];
    stderr_redirect = argv[3];
    bin_args = &argv[3];

    child_exit_handler(0);
    while (1) {}
    return 0;
}
