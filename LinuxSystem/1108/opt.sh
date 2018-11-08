#!/bin/bash

# ./opt.sh -a -l
# ./opt.sh -al
# ./opt.sh -l -a
# getopt

while getopts "als:" opt; do
	case $opt in
		a) echo "Option All";;
		l) echo "Option List";;
		s) echo "Option String" $OPTARG;;
		*) echo "Unknown";;
	esac
done
