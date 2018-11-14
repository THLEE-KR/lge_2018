
#include <stdio.h>

void foo()
{
	int fd1 = open("a.txt", O_RDONLY);
	if (fd1 == -1) {
		goto done;
	}

	int fd2 = open("a.txt", O_RDONLY);
	if (fd2 == -1) {
		goto close_fd1;
	}

	int fd3 = open("a.txt", O_RDONLY); 
	if (fd3 == -1) {
		goto close_fd2;
	}


close_fd2:
		close(fd2);
close_fd1:
		close(fd1);
done:
}
