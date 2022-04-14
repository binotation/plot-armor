CC=gcc
CFLAGS=-Wall -pedantic -std=gnu99

.DEFAULT_GOAL:=respawn

.PHONY: release

release: CFLAGS+=-O3

release: respawn

respawn: respawn.c
	$(CC) $(CFLAGS) respawn.c -o respawn

print_args: test-bins/print_args.c
	$(CC) $(CFLAGS) test-bins/print_args.c -o test-bins/print_args

crash: test-bins/crash.c
	$(CC) $(CFLAGS) test-bins/crash.c -o test-bins/crash

clean:
	rm respawn test-bins/crash test-bins/print_args *.log
