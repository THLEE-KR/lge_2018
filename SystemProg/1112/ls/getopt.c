
#include <unistd.h>
#include <stdio.h>

#define LIST  1
#define INODE 2
#define RECUR 3
#define ALL   4

int isList = 0;
int isInode = 0;
int isRecur = 0;
int isAll = 0;

int main(int argc, char** argv)
{
	int ch;

	while ((ch = getopt(argc, argv, "liRa")) !=  -1) {
		switch (ch) {
			case 'l':
				isList = 1;
				break;
			case 'i':
				isInode = 1;
				break;
			case 'R':
				isRecur = 1;
				break;
			case 'a':
				isAll = 1;
				break;
		}
	}

	printf("isList: %d\n", isList);
	printf("isInode: %d\n", isInode);
	printf("isRecur: %d\n", isRecur);
	printf("isAll: %d\n", isAll);
}
