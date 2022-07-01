CC := clang
CFLAGS := -Wall -Wextra -std=c17 -O3

TARGETDIR := target

.PHONY: $(shell mkdir -p $(TARGETDIR)) clean all print_args crash
.DEFAULT_GOAL := all

all: print_args crash

print_args:
	$(CC) $(CFLAGS) $@.c -o $(TARGETDIR)/$@

crash:
	$(CC) $(CFLAGS) $@.c -o $(TARGETDIR)/$@

clean:
	rm -f target/*
