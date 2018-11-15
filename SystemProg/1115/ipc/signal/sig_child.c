#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig(int sig)
{
	printf("child die(% d)\n", getpid());
}

int main()
{
	signal(SIGINT, sig);
	pause();
}

