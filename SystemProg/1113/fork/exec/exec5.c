#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// exec 계열의 시스템 콜은 현재의 프로세스를 해당 프로그램으로
// 변경한다.

int main()
{
	int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(1);
	dup(fd);

 	char* argv[] = { "ls", "-l", NULL };
	// char* argv[] = { "./a.out", NULL };
	execvp(argv[0], argv);

	printf("Show me the money...\n");
}
