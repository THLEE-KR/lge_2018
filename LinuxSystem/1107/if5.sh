#!/bin/bash
read -p "input number: "
 
if (( (($REPLY % 2)) == 0 )); then
	echo "even"
else
	echo "odd"
fi 

