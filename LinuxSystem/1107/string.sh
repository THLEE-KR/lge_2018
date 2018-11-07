#!/bin/sh
# 문자열 처리
expr length "hello" 

# index가 1부터 시작한다. 오류 발생시 0을 반환한다.
expr index "hello" "el"

str="ABCDEFGHIJKLMNOPQR"
expr substr $str 2 5
