#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARGV 32
void run_command(int argc, char** argv);
int parse_command(char* buf, int* argc, char** argv);

// cd: 쉘 적용되는 명령어
// 일반 프로그램
//   : 자식 프로세스 + exec 

int main()
{
	char buf[1024];
	int argc = 0;
	char* argv[MAX_ARGV] = {0, };

	while (1)
	{
		char path[256];
		// pwd -> getcwd
		getcwd(path, sizeof path);

		printf("[%s]> ", path);
		if (fgets(buf, sizeof buf, stdin) == NULL)
			break;

		if (strlen(buf) == 1)
			continue;

		buf[strlen(buf) - 1] = '\0';
		if (strcmp(buf, "exit") == 0)
			break;

		parse_command(buf, &argc, argv);
		if (argc == 0)
			continue;

		run_command(argc, argv);
	}

	putchar('\n');
}

void run_command(int argc, char** argv)
{
	pid_t pid;

	if (strcmp(argv[0], "cd") == 0)
	{
		if (argc != 2) 
		{
			struct passwd *pw = getpwuid(getuid());
			chdir(pw->pw_dir);
			return;
		}

		chdir(argv[1]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execvp(argv[0], argv);
		perror("execvp");
		exit(0);
	}
	else if (pid > 0)
	{
		wait(0);
	}
	else
	{
		exit(0);
	}	
}

int parse_command(char* buf, int* argc, char** argv)
{
	char* p;
	int i = 0;

	p = strtok(buf, " ");
	while (p != NULL)
	{
		argv[i++] = p;
		p = strtok(NULL, " ");
	}
	argv[i] = (char*)0;
	*argc = i;

	/*
	   for (int i = 0 ; i < *argc; ++i)
	   printf("argv[%d]: %s\n", i, argv[i]);
	 */

	return 0;
}

