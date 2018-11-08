#!/bin/bash

foo() {
	echo "foo"
}

# C: atexit
# Exit Handler
# 스크립트가 종료된 이후에 수행되는 작업을 정의한다.
# 정상 종료를 하든, 시그널에 의해 종료를 하든 수행된다.
trap foo EXIT

for ((i=1; i<=10; ++i)); do
	echo "Loop $i"
	sleep 1
done
