
#include <unistd.h>
#include <stdio.h>

#define LIST  1     // 0001
#define INODE 1<<1  // 0010
#define RECUR 1<<2  // 0100
#define ALL   1<<3  // 1000

int flags = 0;
int main(int argc, char** argv)
{
	int ch;

	while ((ch = getopt(argc, argv, "liRa")) !=  -1) {
		switch (ch) {
			case 'l':
				flags |= LIST;
				break;
			case 'i':
				flags |= INODE;
				break;
			case 'R':
				flags |= RECUR;
				break;
			case 'a':
				flags |= ALL;
				break;
		}
	}

	// Zero: False(0)
	// Non-Zero: True(1)

	printf("isList: %d\n", (flags & LIST));
	printf("isInode: %d\n", flags & INODE);
	printf("isRecur: %d\n", !!(flags & RECUR));
	printf("isAll: %d\n", flags & ALL);
}







