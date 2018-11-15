#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

// # kill -USR1 <PID>
// # kill -USR2 <PID>

void handler(int sig) {
	printf("signal no(%d) Received\n",sig);
}

int main() {
	if (signal(SIGUSR1, handler) == SIG_ERR) {
		fprintf(stderr,"cannot set USR1\n");
		exit(1);
	}                

	if (signal(SIGUSR2, handler) == SIG_ERR) {
		fprintf(stderr,"cannot set USR2\n");
		exit(1);
	}
	
	while (1)       
		pause();
} 

