#!/bin/bash

# print_param a b c d
print_param() {
    echo \$*: $* # ""a b c d""
    echo \$@: $@ # "a b c d"
}

print_param2() {
	echo '"$*" >'
    for arg in "$*"; do
        echo "$arg"
    done
}

print_param3() {
    echo '"$@" >'
    for arg in "$@"; do
        echo "$arg"
    done
}

print_param2 "hi~" "hello, world" "bye" 
print_param3 "hi~" "hello, world" "bye" 
