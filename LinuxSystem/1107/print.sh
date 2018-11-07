#!/bin/sh
# 개행을 포함합니다.
echo "hello, world"

# -n: 개행 하지 않습니다.
# echo -n "hello"
printf "hello, world\n"

# echo "USER:$USER, HOME:$HOME"
# echo 'USER:$USER, HOME:$HOME'
# echo "USER:\$USER, HOME:\$HOME"

# printf "USER:%s, HOME:%s\n" $USER $HOME 
# printf 'USER:$USER, HOME:$HOME\n'

printf "age:%d\n" 18
printf "name:%s\n" "Tom"
printf "PI: %f\n" 3.14












