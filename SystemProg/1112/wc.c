#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// isspace

int main(int argc, char **argv)
{
	FILE* fp;
	int ch;

	int width = atoi(argv[2]);
	int char_cnt = 0;
	int line_cnt = 0;
	int word_cnt = 0;
	int flag = 0;

	fp = fopen(argv[1], "r");
	while ((ch = fgetc(fp)) != EOF) {
		char_cnt++;
		if (ch == '\n')
			++line_cnt;

		// if (ch != '\n' && ch != ' ' && ch != '\t')
		if (!isspace(ch)) {
			if (flag == 0)
			{
				word_cnt++;
				flag = 1;
			}
		} else {
			flag = 0;
		}
	}

	// 각 값의 넓이를 동적으로 제어하는 방법
	printf("%*d %*d %*d %*s\n", 
		width, line_cnt, width, word_cnt, width, char_cnt, width, argv[1]);

	fclose(fp);
	return 0;
}














