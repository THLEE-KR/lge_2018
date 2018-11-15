#include <unistd.h>
#include <signal.h>

#include <stdio.h>






// Signal Set을 다루는 방법
//  int sigemptyset(sigset_t *set);
//  int sigfillset(sigset_t *set);
//  int sigaddset(sigset_t *set, int signum);
//  int sigdelset(sigset_t *set, int signum);
//  int sigismember(const sigset_t *set, int signum);


#if 1
int main()
{
	// bitset 형태로 구현되어 있습니다.
	sigset_t set;
	sigemptyset(&set);
	// sigfillset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGUSR2);

	sigdelset(&set, SIGINT);

	if (sigismember(&set, SIGINT)) {
		printf("SIGINT set\n");
	} else {
		printf("SIGINT clear\n");
	}
}
#endif

















