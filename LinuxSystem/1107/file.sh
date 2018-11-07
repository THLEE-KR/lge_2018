#!/bin/bash

if [ -f ~/.vimrc ]; then
	echo "yes"
	cp ~/.vimrc .
else
	echo "no"
fi
