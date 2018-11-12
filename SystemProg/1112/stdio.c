
#include <stdio.h>
#include <string.h>

// # C 표준 입출력 라이브러리가 버퍼링을 하고 있다.
//  이유?
//   : User mode와 Kernel mode간의 문맥 교환의 비용이 크다.

// # 정책
//   1) 라인 버퍼링: 엔터가 올때까지 버퍼링 합니다.     : stdout
//   2) 풀 버퍼링: 버퍼가 가득 찰때까지 버퍼링 합니다.  : 일반 파일
//   3) 노 버퍼링: 버퍼링을 하지 않습니다.              : stderr

int main()
{
	int i;
	char *s = "hello";
	for (i = 0; i < strlen(s) ; ++i) {
		putchar(s[i]);
	}
	
}
