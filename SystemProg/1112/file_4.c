
#include <stdio.h>

int main()
{
	char buf[128];
	int ret;

	while ((ret = fread(buf, 1, sizeof buf, stdin)) != 0) {
	// while (ret = fread(buf, 1, sizeof buf, stdin)) {
		printf("ret: %d\n", ret);
		fwrite(buf, 1, ret, stdout);
	}
	
	return 0;
}
