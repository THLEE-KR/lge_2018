#include <unistd.h>
#include <stdio.h>

// p: path
int main()
{
	// ls -l
	// l
	// v
	char* argv[] = { "ls", "-l", NULL };
	execvp("ls", argv);
	// execlp( "ls", "ls", "-l", NULL );
}
