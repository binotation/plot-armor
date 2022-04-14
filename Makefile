CC=gcc
CFLAGS=-Wall -pedantic -std=gnu99

.DEFAULT_GOAL:=respawn

respawn: respawn.c
	$(CC) $(CFLAGS) respawn.c -o respawn

print_args: test-bins/print_args.c
	$(CC) $(CFLAGS) test-bins/print_args.c -o test-bins/print_args
