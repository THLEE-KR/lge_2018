#include <stdio.h>
// # 함수의 이름에서 명령모드로 대문자 K를 입력하면,
//   메뉴얼을 바로 볼 수 있습니다.

// EOF(End Of File): 파일의 끝
//  #define EOF (-1)

// 텍스트 파일을 처리할 때는, 상관이 없습니다.
// 이진 파일을 처리할 때, int ch를 사용하지 않으면은
// 제대로 동작하지 않습니다.

int main()
{
	FILE *fp = fopen("file.c", "r");
	int ch;

	if (fp == NULL) {
		fprintf(stderr, "file open error.\n");
		return -1;
	}

	while ((ch = fgetc(fp)) != EOF) 
		fputc(ch, stdout);

	fclose(fp);
	return 0;
}

