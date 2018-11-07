#!/bin/bash

read -p "input number: "

# if (reply == 0) printf("number is zero\n");
if [ $REPLY -gt 0 ]
then
	echo "number is positive"
elif [ $REPLY -lt 0 ]; then
	echo "number is negative"
else
	echo "number is zero"
fi

