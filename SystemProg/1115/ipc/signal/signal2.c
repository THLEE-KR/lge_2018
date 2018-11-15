#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void catchint(int signo)
{
	printf(" SIGINT Receive\n");
}  

int main()
{
	signal(SIGINT, catchint);

	printf("sleep call #1\n");      sleep(10);
	printf("sleep call #2\n");      sleep(10);
	printf("sleep call #3\n");      sleep(10);
	printf("sleep call #4\n");      sleep(10);
	printf("Exiting");

	return 0;
}

