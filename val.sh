#!/bin/bash
valgrind --leak-check=full\
    --show-leak-kinds=possible\
    --track-origins=yes\
    --log-file=vout.log\
    ./respawn test-bins/print_args out.log err.log foo bar
