
// # FILE: 파일 구조체
//   중요한 정보 
//    1) 라이브러리 버퍼의 포인터
//    2) offset: 어디까지 파일을 읽거나 썼는지에 대한 정보

#include <stdio.h>

int main()
{
	char buff[100];
	int ret;

	FILE* fp = fopen("input.txt", "r");
	ret = fread(buff, 1, 2, fp);

	fwrite(buff, 1, ret, stdout);
	getchar();

	ret = fread(buff, 1, 2, fp);
	fwrite(buff, 1, ret, stdout);

	fclose(fp);
	return 0;
}
