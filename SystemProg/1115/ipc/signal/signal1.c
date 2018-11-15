#include <unistd.h>
#include <signal.h>

#include <stdio.h>

int main()
{
	printf("SIGINT 동작을 무시합니다.\n");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	getchar();
	getchar();

	printf("원래 동작으로 복구합니다...\n");
	signal(SIGINT, SIG_DFL);

	getchar();
}

