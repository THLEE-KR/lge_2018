#!/bin/bash

foo() {
	echo "foo"
}

set -x
trap foo SIGINT
for ((i=1; i<=10; ++i)); do
	echo "Loop $i"
	sleep 1
	if ((i == 5)); then
		trap -- SIGINT
	fi
done
set +x

trap foo SIGINT
for ((i=1; i<=10; ++i)); do
	echo "Loop $i"
	sleep 1
	if ((i == 5)); then
		trap -- SIGINT
	fi
done

