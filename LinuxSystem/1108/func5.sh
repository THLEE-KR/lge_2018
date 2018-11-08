#!/bin/bash

display() {
	for arg in "$@"; do
		echo $arg
	done
}

display "a" "b" "c"
#arr=("Tom" "Bob" "Ann")
#display ${arr[*]}
