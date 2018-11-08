#!/bin/bash

arr1=(10 20 30 40 50 60)
arr2=(1024 "one" $(pwd) $USER)

# count
echo ${#arr1[@]}
echo ${#arr2[@]}

echo ${arr1[1]}
echo ${arr2[1]}

# 배열의 전체를 출력하는 방법
echo ${arr1[*]}
echo ${arr2[*]}

arr3=([10]="ten" [0]="zero" [33]="33")
echo ${arr3[*]}
echo ${#arr3[@]}









