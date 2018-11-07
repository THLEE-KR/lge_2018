#!/bin/bash
var=10
((var > 0 ? ++var : --var))
echo $var   # 11

var=10
((var > 0 ? (var+=1) : (var-=1) ))
echo $var   # 11

