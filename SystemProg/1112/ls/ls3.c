#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

void my_ls( char *dname )
{
	DIR *dp;
	struct dirent *p;
	chdir(dname);      
	dp = opendir(".");
	while( p = readdir( dp ))
		printf("%s\n", p->d_name );
	closedir(dp);
	chdir("..");      
}

int main()
{
	my_ls(".");   // 디렉토리의 순회 구현을 모듈화 한다.
	return 0;
}

