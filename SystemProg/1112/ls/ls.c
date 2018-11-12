#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
// opendir

#include <stdio.h>

// 1. 디렉토리는 데이터에 현재 디렉토리 안에 있는 파일의 이름과 아이노드 번호를 저장한다.
// opendir
// readdir
// closedir

// /root
//   1000  a.c  -> struct dirent
//   2000  b.c
//     ...

int main()
{
	struct dirent* p;
	DIR* dp;
	dp = opendir(".");

	while ((p = readdir(dp)) != NULL) {
		printf("A: %s\n", p->d_name);
	}

	rewinddir(dp);

	while ((p = readdir(dp)) != NULL) {
		printf("B: %s\n", p->d_name);
	}

	closedir(dp);
}



// File
// open : int, 
//  -> fopen : FILE* 

// Directory
// open : int
//  -> opendir : DIR*

/*
int main()
{
	int fd = open(".", O_RDONLY);
	printf("fd: %d\n", fd);
}
*/
