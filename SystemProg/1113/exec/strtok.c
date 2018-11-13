#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char s[] = "ls -ali";
	char *argv[20];
	int i = 0;
	int n;
	char* p;
	
	// strtok
	//   인자로 전달된 문자열을 수정합니다.
	// strdup
	//  char* s = malloc(strlen(p) + 1);
	//  strcpy(s, p);

	for (p = strtok(s, " ") ; p != NULL ; p = strtok(NULL, " ")) {
		printf("%s\n", p);
		argv[i++] = strdup(p);
	}
	argv[i] = NULL;

	for (i = 0 ; argv[i] != NULL ; ++i) {
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	for (i = 0 ; argv[i] != NULL ; ++i) {
		free(argv[i]);
	}

	


	/*
	p = strtok(s, " ");
	printf("%s\n", p);

	p = strtok(NULL, " ");
	printf("%s\n", p);
	*/





}
