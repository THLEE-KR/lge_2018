#!/bin/bash

directory_count=`find . -maxdepth 1 -type d | wc -l`
file_count=`find . -maxdepth 1 -type f | wc -l`

((directory_count-=1))

printf "File count: %d Directory count: %d\n" $file_count $directory_count
