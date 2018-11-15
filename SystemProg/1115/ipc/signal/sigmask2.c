#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void show_mask()
{
	sigset_t sigset;

	// 현재의 sigmask를 얻는다.
	if (sigprocmask(0, NULL, &sigset) < 0)
		printf("sigprocmask error");

	if (sigismember(&sigset, SIGINT))       printf("SIGINT ");
	if (sigismember(&sigset, SIGQUIT))      printf("SIGQUIT ");
	if (sigismember(&sigset, SIGUSR1))      printf("SIGUSR1 ");
	if (sigismember(&sigset, SIGALRM))      printf("SIGALRM ");

	printf("\n");
}

int main(void)
{
	sigset_t newmask, oldmask;

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	sigaddset(&newmask, SIGINT);

	/* add SIGQUIT signal to blocked signal list */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("sigprocmask error");

	show_mask();
	pause();

	/* restore previous signal mask */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("sigprocmask error");

	exit (0);
}


