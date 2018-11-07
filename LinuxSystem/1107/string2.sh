#!/bin/bash
# 문자열 처리 - {}
# expr length "hello" 
str="hello"
echo ${#str}

# 부분 문자열
str="ABCDEFGHIJKL"
echo ${str:1:3}

# 길이를 명시하지 않으면, 끝까지 추출한다.
echo ${str:5}

# 문자열 삭제
str="ABCDEFABCDEFABCDEF123123"
# 가장 짧게 일치하는 것까지 
echo ${str#ABCDEF}

# 가장 길게 일치하는 것까지 
echo ${str##ABCDEF}


# replace
str="xyzABC123ABCxyz"
# echo ${str/ABC/***}
echo ${str//ABC/***}








