#!/bin/bash

val1=100
val2=5

result=`echo "scale=5; $val1/$val2" | bc`
echo $result

# Here Document
echo $(bc << END
scale=5
3.14 * $val1 / $val2
END
)
