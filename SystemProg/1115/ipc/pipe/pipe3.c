#include <unistd.h>
#include <signal.h>

#include <stdio.h>
// ./a.out ps sort 
// $ ps | sort
int main(int argc, char **argv)
{
	FILE *in, *out;
	char buf[100];
	
	in = popen("ps", "r");
	out = popen("sort", "w");

	while (fgets(buf, sizeof buf, in) != NULL) {
		fputs(buf, out);
	}

	pclose(in);
	pclose(out);
}






