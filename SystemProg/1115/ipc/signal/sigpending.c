#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

static void sig_quit(int);

int main(void){
	sigset_t newmask, oldmask, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		printf("can't catch SIGQUIT");

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	/* block SIGQUIT and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		printf("SIG_BLOCK error");

	sleep(5);       /* SIGQUIT here will remain pending */

	// sigpending은 지연된 시그널 셋을 얻어올 수 있다.
	if (sigpending(&pendmask) < 0)
		printf("sigpending error");
	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");


	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		printf("SIG_SETMASK error");
	printf("SIGQUIT unblocked\n");
	sleep(5);       /* SIGQUIT here will terminate with core file */
	exit(0);
}

static void sig_quit(int signo){
	sigset_t pendmask;
	printf("caught SIGQUIT\n");

	if (sigpending(&pendmask) < 0)
		printf("sigpending error");
	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending2\n");

	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		printf("can't reset SIGQUIT");
	return;
}
