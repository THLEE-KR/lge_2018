// lock 을 사용할 때는 항상 데드락을 주의해야 한다.
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

int main()
{
	pthread_mutex_init( &mutex , 0 );

	pthread_mutex_lock( &mutex );
	pthread_mutex_lock( &mutex );
	printf("임계영역 진입\n");
	pthread_mutex_unlock( &mutex );
	return 0;
}

