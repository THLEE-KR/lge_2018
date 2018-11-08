#!/bin/bash
read -p "정수 입력: "

i=0
sum=0
while true; do
  let ++i

  if ((i > $REPLY)); then
    break
  fi

  if (( (i % 2) == 1 )); then
    continue
  fi

  let sum+=i
done
echo "결과: $sum"

