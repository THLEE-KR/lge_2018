#include <unistd.h> // usleep, sleep

#include <stdio.h>

// fgetc / fputc : byte 단위
// fgets / fputs : 라인 단위
// fread / fwrite : 버퍼 단위

int main()
{
	FILE* fp;
	char buff[100];
	int i;
	
	fp = fopen("file.c", "r");

	// while ((fgets(buff, sizeof buff, fp)) != NULL) {
	while (fgets(buff, sizeof buff, fp)) {
		usleep(1000 * 100);  // 100ms

		fputs(buff, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
