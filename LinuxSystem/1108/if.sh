#!/bin/bash

read -p "input your age: "
if [[ ! $REPLY =~ ^[1-9][0-9]*$ ]]; then
    echo "wrong input"
    exit 1
fi

#if [ $REPLY -ge 13 -a $REPLY -le 19 ]; then
if (( (($REPLY >= 13)) && (($REPLY <= 19)) )); then
    echo "teenager"
else
    echo "not teenager"
fi

