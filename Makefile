CC := clang
CFLAGS := -Wall -Wextra -std=gnu17

.PHONY: target
.DEFAULT_GOAL := target

target: CFLAGS += -O3
target: respawn

respawn: respawn.c
	$(CC) $(CFLAGS) respawn.c -o respawn

print_args: test-bins/print_args.c
	$(CC) $(CFLAGS) test-bins/print_args.c -o test-bins/print_args

crash: test-bins/crash.c
	$(CC) $(CFLAGS) test-bins/crash.c -o test-bins/crash

clean:
	rm respawn test-bins/crash test-bins/print_args *.log
