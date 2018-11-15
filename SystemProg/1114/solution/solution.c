
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define	NLOOP	   	100
#define	Q_MAX	    16

typedef struct queue_t {
	int		data[Q_MAX];	
	int		nitem;		
	int		head;
	int		tail;
	pthread_mutex_t	mutex;
	pthread_cond_t	c_cond;	
	pthread_cond_t	p_cond;
}queue_t;

queue_t queue = {
	.mutex = PTHREAD_MUTEX_INITIALIZER,
	.c_cond = PTHREAD_COND_INITIALIZER,
	.p_cond = PTHREAD_COND_INITIALIZER,
};

void put( int d ) 
{
	queue.data[queue.head] = d;
	queue.head = (queue.head+1)%Q_MAX;
	queue.nitem++;
}

int get() 
{
	int temp =  queue.data[queue.tail];
	queue.tail = (queue.tail+1)%Q_MAX;
	queue.nitem--;
	return temp;
}

int is_empty( )
{
	return queue.nitem == 0;
}

int is_full( )
{
	return queue.nitem ==  Q_MAX;
}
void * produce(void *vptr)
{
	int		i;
	for (i = 0; i < NLOOP; i++) 
	{
		pthread_mutex_lock(&queue.mutex);
		if ( is_full() )
			pthread_cond_wait(&queue.p_cond, &queue.mutex);

		usleep(((rand()%5) + 1) * 1000);
		printf("produce %d\n", i);
		put( i );

		pthread_cond_signal(&queue.c_cond);
		pthread_mutex_unlock(&queue.mutex);
	}
	return 0;
}

void * consume(void *vptr)
{
	int		i, val;
	for (i = 0; i < NLOOP; i++) {
		pthread_mutex_lock(&queue.mutex);
		while ( is_empty() )
			pthread_cond_wait(&queue.c_cond, &queue.mutex);

		usleep(((rand()%2) + 2) * 1000);
		val = get();
		printf("\t\tconsume %d\n", val);

		pthread_cond_signal(&queue.p_cond);
		pthread_mutex_unlock(&queue.mutex);
	}
	return 0;
}

int main(int argc, char **argv)
{
	int			n;
	pthread_t	tidA, tidB;
	srand(time(0));

	pthread_create(&tidA, 0, &produce, 0);
	pthread_create(&tidB, 0, &consume, 0);
	pthread_join(tidA, 0);
	pthread_join(tidB, 0);
	return 0;
}



