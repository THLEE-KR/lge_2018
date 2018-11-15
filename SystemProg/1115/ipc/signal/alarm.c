
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

void on_alarm(int signo)
{
	printf("SIGALRM Receive\n");
}  

int main() 
{
	signal(SIGALRM, on_alarm);

	alarm(5);

	pause();
}
