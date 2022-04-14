#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Before child execs
#define CHLD_INIT_ROUTINE() {\
    freopen(stdout_redirect, "a+", stdout);\
    freopen(stderr_redirect, "a+", stderr);\
    execvp(binpath, bin_args);\
}

void cpy_slice_into(char **args, char **argv_slice) {
    int i = -1;
    while (argv_slice[++i] != 0) {
        args[i] = argv_slice[i];
    }
    args[i] = 0;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        fputs("Usage: respawn binpath stdout_redirect stderr_redirect bin_args...\n", stderr);
        return 1;
    }

    char *binpath = argv[1];
    char *stdout_redirect = argv[2];
    char *stderr_redirect = argv[3];

    char **bin_args = malloc(sizeof(char*) * (argc - 2));
    cpy_slice_into(bin_args, &argv[3]);
    bin_args[0] = binpath;

    if (!fork()) {
        // Spawn initial child process
        CHLD_INIT_ROUTINE()
    } else {
        while (1) {
            // Wait for child process termination
            if (wait(0) > 0) {
                if (!fork()) {
                    CHLD_INIT_ROUTINE()
                }
            };
        }
    }
}
