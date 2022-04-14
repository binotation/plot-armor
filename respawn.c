#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Before child execs
#define CHLD_INIT_ROUTINE() {\
    freopen(outf, "a+", stdout);\
    freopen(errf, "a+", stderr);\
    execvp(bin, binargs);\
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
        fputs("Usage: respawn bin outf errf binargs...\n", stderr);
        return 1;
    }

    char *bin = argv[1];
    char *outf = argv[2];
    char *errf = argv[3];

    char **binargs = malloc(sizeof(char*) * (argc - 2));
    cpy_slice_into(binargs, &argv[3]);
    binargs[0] = bin;

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
