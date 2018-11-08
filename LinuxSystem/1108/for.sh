#!/bin/bash

for (( i=0 ; i<10 ; ++i )); do
	echo "$i: hello"
done

for i in 1 2 3 4 5 6 7 8 9; do
    echo "$i: hello, world"
done

fruits="apple orange banana"
for i in $fruits; do
	echo $i
done

#for i in $(cat for.sh); do
#	echo $i
#done


