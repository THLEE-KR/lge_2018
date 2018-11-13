#include <stdio.h>

// system("ls -l");
//       argv[0] = "ls"
//       argv[1] = "-l"


int main(int argc, char **argv, char **envp)
{
	char **env;
	int i;
	for (i = 0 ; i < argc ; ++i) {
		printf("argv[%d] : %s\n", i, argv[i]);
	}

/*
	for (env = envp; *env != 0 ; env++) {
		printf("%s\n", *env);
	}
*/
}




// system: 표준 라이브러리 함수
//   내부적으로 exec 계열의 시스템 콜을 사용하고 있다.

//  자료 형태(둘중에 하나만 사용)
//   l: list
//   v: vector

//  환경 변수(Optional)
//   e: 환경 변수 인자
//   p: path 참조

/*
execl
execlp
execle
execv
execvp
execvpe
*/

// execve 최종 호출입니다.
