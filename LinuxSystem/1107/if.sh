#!/bin/bash

read -p "input number: "

# if (reply == 0) printf("number is zero\n");
if test $REPLY -eq 0
then
	echo "number is zero"
fi

if test $REPLY -ne 0
then
	echo "number is non zero"
fi
