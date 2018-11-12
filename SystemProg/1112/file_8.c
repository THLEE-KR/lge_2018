#include <unistd.h> // usleep, sleep

#include <stdio.h>

// fgetc / fputc : byte 단위
// fgets / fputs : 라인 단위
// fread / fwrite : 버퍼 단위

int main()
{
	FILE* fp;
	char buff[100];
	int ret;  // 읽은 바이트 수!!!!!!  
	
	fp = fopen("file.c", "r");

	while (ret = fread(buff, 1, sizeof buff, fp)) {
		usleep(1000 * 100);  // 100ms

		fwrite(buff, 1, ret, stdout);
		fflush(stdout);
	}

	fclose(fp);
	return 0;
}
