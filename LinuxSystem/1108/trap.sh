#!/bin/bash

# kill -l
# SIGKILL SIGSTOP SIGCONT
# trap "echo Ctrl + C" SIGINT 
foo() {
	echo "foo"
}

trap foo SIGINT

for ((i=1; i<=10; ++i)); do
	echo "Loop $i"
	sleep 1
done
