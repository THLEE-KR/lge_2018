#include <stdio.h>

int main()
{
	FILE *fp;
	char buff[100];
	int ret; 
	
	fp = fopen("stdio.c", "r");

	while (ret = fread(buff, 1, sizeof buff, fp)) {
		fwrite(buff, 1, ret, stdout);
	}

	fclose(fp);
	return 0;
}
