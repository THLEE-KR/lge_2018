#!/bin/bash

foo() {
	echo $1 $2 $3
}

foo 10 20 30
echo $? 


echo $1 $2 $3
exit 42
