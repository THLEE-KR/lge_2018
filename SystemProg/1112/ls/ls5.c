#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <stdio.h>
#include <string.h>

void my_ls( char *dname ) {
	DIR *dp;
	struct dirent *p;
	struct stat buf;
	chdir(dname);
	printf("%s:\n", dname);

	dp = opendir(".");
	while( p = readdir( dp ))  {
		printf("%s ", p->d_name );
	}
	putchar('\n');

	rewinddir(dp);

	while( p = readdir( dp ))  {
		lstat(p->d_name, &buf);

		if( S_ISDIR(buf.st_mode) )
		{
			if( strcmp( p->d_name, "." ) 
					&& strcmp( p->d_name, ".." ) ) {
				putchar('\n');
				my_ls(p->d_name);
			}
		}
	}
	closedir(dp);
	chdir("..");
}

int main()
{
	my_ls(".");   // 디렉토리의 순회 구현을 모듈화 한다.
	return 0;
}

