
#!/bin/sh

result=$(expr 2 + 2)
echo $result

# 무조건 띄어야 합니다.
result=$(expr  2  +   2 )
echo $result

# 변수 참조도 할 수 있습니다.
val1=10
val2=32
result=$(expr $val1 + $val2)
echo $result

# 여전히 잘 안돼요.
result=$(expr n1 \> n2)
