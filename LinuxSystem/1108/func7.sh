#!/bin/bash

display() {
  count=$1
  if (( count == 0 )); then
    return 42
  fi
  echo $2
  count=$(( count - 1 ))
  display $count "$2"
}

display 3 hello
# 함수의 최종 반환값을 확인하는 방법
echo $?

