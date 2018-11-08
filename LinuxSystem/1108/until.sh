#!/bin/bash
# while은 조건이 참일때 까지 수행하지만,
i=1
while (( i < 5 )); do
  let ++i
  echo "hello, world"
done

echo "--until--"

# until은 조건이 거짓일때까지 수행된다. 
i=1
until (( i >= 5 )); do
  let ++i
  echo "hello, world"
done
