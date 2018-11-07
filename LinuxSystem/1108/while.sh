#!/bin/bash

cnt=1
while (( $cnt <= 5 ))
do
	printf "%d - hello\n" $cnt
	let ++cnt
done

cnt=1
while (($cnt <= 5)); do
	printf "%d - hello\n" $cnt
	let ++cnt
done

#cnt=1
#while true; do
#	printf "%d - hello\n" $((++cnt))
#done










