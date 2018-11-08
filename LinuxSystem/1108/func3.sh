#!/bin/bash

display() {
	while [ -n "$1" ]; do
		echo "$1 "
		shift
	done
}

name1="Tom"
name2="Bob"
name3="Ann"

arr=("Tom" "Bob" "Ann")

#display ${arr[*]}
display ${arr[0]} ${arr[1]} ${arr[2]} 

#display $name1 $name2 $name3
#display "Tom" "Bob" "Ann"

