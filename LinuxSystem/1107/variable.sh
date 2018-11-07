#!/bin/sh

name="Tom"
echo $name

# Shell command의 결과를 변수에 집어넣는 두가지 방법
# 1. $(date)
# 2. `date`

# today=$(date)
today=`date`
echo $today
