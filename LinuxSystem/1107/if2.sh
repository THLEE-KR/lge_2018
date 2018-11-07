#!/bin/bash

read -p "input number: "

# if (reply == 0) printf("number is zero\n");
if test $REPLY -eq 0
then
	echo "number is zero"
fi

# ; 을 이용하면 한줄에 작성 가능합니다.
# if test $REPLY -ne 0; then
#	echo "number is non zero"
# fi

# !!!!!!!!
if [ $REPLY -ne 0 ]; then
	echo "number is non zero"
fi




