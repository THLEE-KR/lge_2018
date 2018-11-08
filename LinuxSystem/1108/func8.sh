#!/bin/bash

foo() {
	echo $name
	name="Bob"
	if (($1 == 0)); then
		name="Tom"
	fi
}

foo 1
foo 1
