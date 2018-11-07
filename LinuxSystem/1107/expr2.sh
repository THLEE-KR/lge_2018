#!/bin/bash

# result=$[2 * 2]
result=$[2*2]
echo $result

n1=10
n2=20
result=$(expr $n1 + $n2)
result=$[$n1 + $n2]
result=$[n1 + n2]

echo $result

