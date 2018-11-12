#include <stdio.h>

// 인자로 받은 파일의 사이즈를 구하는 프로그램을 작성한다.
// $ ./a.out file.c
//   filesize: 55

// EOF: -1
// ch: 0000 0000 1111 1111

// ch != EOF
// 0000 0000 1111 1111 != EOF

// # ch를 char으로 하면, 0xFF를 EOF로 판단한다.
int main(int argc, char** argv)
{
	FILE *fp = fopen(argv[1], "r");
	int ch;
	int count = 0;

	if (fp == NULL) {
		fprintf(stderr, "file open error.\n");
		return -1;
	}

	while ((ch = fgetc(fp)) != EOF) 
		++count;

	printf("filesize: %d\n", count);

	fclose(fp);
	return 0;
}





