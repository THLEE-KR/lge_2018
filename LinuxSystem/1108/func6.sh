#!/bin/sh

get_hello() {
	# 결과를 전달하는 방법: 함수의 마지막에 echo 명령을 사용합니다.
	echo "hello"
	echo 3.14
	echo "Tom"
}

#ret=$(get_hello)
ret=`get_hello`
echo $ret
