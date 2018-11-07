#!/bin/sh

echo "Hello, Linux"

read name

# 내장 변수 REPLY를 통해 값을 읽어낼 수 있습니다.
read
echo $REPLY

exit 200
