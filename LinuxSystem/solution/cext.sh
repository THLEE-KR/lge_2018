
#!/bin/bash
  
FROM=$1
TO=$2

if [ $# != 2 ]; then
	echo "사용방법: cext.sh 기존확장자 새로운확장자"
	exit 2
fi

for i in *.$FROM; do
	j=$(basename $i .$FROM)
	mv $i $j.$TO 2> /dev/null
	if [ $? != 0 ]; then
		echo "그러한 확장자는 없습니다."
	fi
done

