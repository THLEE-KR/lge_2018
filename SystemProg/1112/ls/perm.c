#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	struct stat buf;
	char perm[11] = "----------";
	char rwx[] = "rwx";
	int i;
	lstat( argv[1], &buf );

	for( i=0; i<9; i++ )
	{
		if( (buf.st_mode >> (8-i)) & 0x1 )
			perm[1+i] = rwx[i%3];
	}
	printf("%s\n", perm );
	return 0;
}

