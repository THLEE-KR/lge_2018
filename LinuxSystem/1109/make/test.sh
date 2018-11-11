#!/bin/bash
GLOBIGNORE="*"

set -x

N1=10
N2=20
OP_ARR='+ - / *'

for OP in $OP_ARR; do 
	echo $((N1 $OP N2))
done
