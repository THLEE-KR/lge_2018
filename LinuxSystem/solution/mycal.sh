#!/bin/bash

is_leap() {
	local year=$1
	if (( ((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0 )); then
		echo 1
	else
		echo 0
	fi
	exit 0
}

check_leap() {
	read -p "연도(1~9999)를 입력하세요: "
	if [[ ! $REPLY =~ ^[1-9][0-9]{0,3}$ ]]; then
		echo "잘못 입력하셨습니다. 아무 키나 누르세요..."
		read
		return 1
	fi

	ret=$(is_leap $REPLY)
	if (( ret == 1 )); then
		echo "윤년입니다."
	else
		echo "윤년이 아닙니다."
	fi
	read -p "아무 키나 누르세요..." 
	return 0
}

disp_mon() {
	read -p "연도(1~9999)와 월 입력하세요(예: 2016 2): " year month
	if [[ ( ! $year =~ ^[1-9][0-9]{0,3}$ ) || ( ! $month =~ ^1[0-2]$|^[1-9]$ ) ]]; then
		echo "잘못 입력하셨습니다. 아무 키나 누르세요..."
		read
		return 1
	fi

	days=([1]=31 28 31 30 31 30 31 31 30 31 30 31)
	if (( ((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0 )); then
		days[2]=29
	fi

	day=$(( year % 7 ))
	leap_cnt=$(( (year-1)/4 - (year-1)/100 + (year-1)/400 ))
	day=$(( (day + leap_cnt) % 7 ))

	for ((i = 1; i <= month-1; i++ )); do
		day=$(( day + ${days[i]} ))
	done
	day=$(( day % 7 ))


	echo " Su Mo Tu We Th Fr Sa"
	for ((i = 0; i < day; i++)); do
		printf "   "
	done

	for ((i = 1; i <= ${days[month]}; i++)); do
		printf "%3d" $i
		if (( (i + day) % 7 == 0 )); then
			printf "\n"
		fi
	done
	echo 
	read -p "아무 키나 누르세요..."
	return 0
}

day_of_week() {
 read -p "연과 월 그리고 일을 입력하세요(예: 2016 8 15): " year month day
 result=$(date -d "$month/$day/$year" +"%A" 2> /dev/null)
 if (( $? != 0 )); then
   read -p "잘못 입력하셨습니다. 아무 키나 누르세요…"
   return -1
 fi
 echo "$result입니다."
 read -p "아무 키나 누르세요…"
 return 0
}



flag=false
trap flag=true SIGINT

disp_time() {
	while true; do
		if $flag; then
			flag=false
			break
		fi

		clear
		date +"%Y년 %m월 %d일 %T 입니다."
		echo "메뉴로 돌아가려면 'CTRL + C'를 입력하세요."
		sleep 1
	done
	read -p "아무 키나 누르세요..."
}

select_menu() {
	clear
	echo "# 달력 프로그램 #"
	echo "-----------------"
	echo "1. 윤년 확인"
	echo "2. 달력 출력"
	echo "3. 요일 확인"
	echo "4. 현재 시간 출력"
	echo "-----------------"
	read -p "입력(0. 종료): "
}

while true; do
	select_menu;

	case $REPLY in
		0) exit 0;;
		1) check_leap;;
		2) disp_mon;;
		3) day_of_week;;
		4) disp_time;;
		*) echo "잘못 입력하셨습니다."; read;;
	esac
done



