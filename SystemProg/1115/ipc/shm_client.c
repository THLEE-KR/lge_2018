#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int shm_id, ret;
	char *p;
	shm_id = shmget(0x2222, 100, IPC_CREAT|IPC_EXCL|0666 );
	if( shm_id < 0 )
	{
		perror( "shmget()" );
		shm_id = shmget(0x2222, 100, 0 );
	}
	printf("shm_id=%d\n", shm_id);

	p = shmat(shm_id, 0, 0);
	getchar();
	strcpy( p, "hello world\n");
	return 0;
}

