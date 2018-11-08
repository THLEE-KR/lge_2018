#!/bin/bash

func() {
	local name="Tom"
}

display() {
	echo $0
	echo $1 $2 $3
	printf "argc: %d\n" $#

	# 10 이상부터는 {} 사용해야 한다.
	echo ${10}
}

#         $1       $2       $3
display "apple" "orange" "banana" 1 2 3 4 5 6 7 8 9 10



#func
#echo $name
