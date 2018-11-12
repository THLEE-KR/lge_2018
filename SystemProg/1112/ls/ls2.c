#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include <stdio.h>

// # File의 속성을 추출할 때는 lstat 이라는 시스템 콜을 이용하면 됩니다.
//  * stat: 심볼릭 링크를 처리할 수 없다.
//      st_mode: 파일의 종류 & 권한
//      st_nlink: 연결 계수(하드 링크)
//      st_uid: user id(int)  ->  getpwuid  -> char* 
//      st_gid: group id(int) ->  getgrgid  -> char*
//      st_mtime: 파일의 수정 시간(long) -> localtime -> char*

// 파일의 종류를 읽어오는 방법

// ls2.c : 81a4
// 100000 110 100 100
//    -   rw- r-- r--

// S_ISREG: regular file
// S_ISDIR: directory file
// S_ISCHR: char device file
// S_ISBLK: block device file
// S_ISFIFO: named pipe
// S_ISLNK:  symbolic link
// S_ISSOCK: socket file

char* print_file_category(mode_t mode)
{
	if (S_ISREG(mode)) {
		return "-";
	} else if (S_ISDIR(mode)) {
		return "d";
	} else if (S_ISCHR(mode)) {
		return "c";
	} else if (S_ISBLK(mode)) {
		return "b";
	} else if (S_ISFIFO(mode)) {
		return "p";
	} else if (S_ISLNK(mode)) {
		return "l";
	} else if (S_ISSOCK(mode)) {
		return "s";
	}

	return "unknown";
}

int main()
{
	struct dirent* p;
	DIR* dp;

	struct stat buf;
	struct tm* tm;
	char str[128];
	dp = opendir(".");
	char* category;

	//   st_mode
	// -rwxr-xr-x 1 root root 8816 11월 12 14:32 a.out
	while ((p = readdir(dp)) != NULL) {

		lstat(p->d_name, &buf);

		
		tm = localtime(&buf.st_mtime);
		
		// 11월 12 15:24
		// printf("%s: %x\n", p->d_name, buf.st_mode);
		sprintf(str, "%d월 %d %d:%d", 
			tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
		
		category = print_file_category(buf.st_mode);
		printf("%10s %5ld %5s %5s %5s %10s", 
			category,
			buf.st_nlink,
			getpwuid(buf.st_uid)->pw_name, 
			getgrgid(buf.st_gid)->gr_name,
			str, p->d_name);

		if (category[0] == 'l')
		{
			// 심볼릭 링크가 바라보는 파일의 패스를 얻어온다.
			int ret = readlink(p->d_name, str, sizeof str);
			str[ret] = '\0';
			printf(" -> %s", str); 
		}

		putchar('\n');
	}

	closedir(dp);
}



















