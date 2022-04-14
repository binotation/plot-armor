#include <stdio.h>
#include <unistd.h>

int main() {
    fputs("Running normally\n", stdout);
    fflush(stdout);
    int zero = 0;
    sleep(5);
    printf("%d\n", 1 / zero);
    return 0;
}
