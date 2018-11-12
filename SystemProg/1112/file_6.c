#include <unistd.h> // usleep, sleep

#include <stdio.h>

int main()
{
	FILE* fp;
	int ch;
	int i;
	
	fp = fopen("file.c", "r");

	while ((ch = fgetc(fp)) != EOF) {
		usleep(1000 * 100);  // 100ms
		fputc(ch, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
