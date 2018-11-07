#!/bin/bash

read -p "input number: "

# if (reply == 0) printf("number is zero\n");
if [ $REPLY -eq 0 ]
then
	echo "number is zero"
else
	echo "number is non zero"
fi

