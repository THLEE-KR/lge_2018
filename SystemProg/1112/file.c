
#include <stdio.h>

// 라이브러리 버퍼를 비우는 함수
//  : fflush(FILE*)

int main()
{
	FILE *fp = fopen("output.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "file open error...\n");
		return -1;
	}

	fprintf(fp, "Hello, world...\n");
	fflush(fp);
	getchar();

	fclose(fp);
}
