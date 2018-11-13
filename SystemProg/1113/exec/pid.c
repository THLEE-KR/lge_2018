
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid = getpid();
	printf("pid: %d\n", pid);
	printf("pgid: %d\n", getpgid(0));

	while (1);
}
