#include <unistd.h>
#include <sys/types.h>   
#include <sys/socket.h>

#include <arpa/inet.h>    
#include <netinet/in.h>

#include <string.h> 
#include <stdio.h>

#include <pthread.h>

// 1. Process per connection Model
// 2. Thread per connection Model
void *thread_routine(void *arg) {
	int len;
	char buf[512];

	int csock = (intptr_t)arg;
		
	while (1) {
		len = read(csock, buf, sizeof buf);
		if (len == 0) {
			printf("연결이 종료되었습니다...\n");
			break;
		} else if (len == -1) {
			perror("read");
			break;
		}

		write(csock, buf, len);
	}

	close(csock);
}



int main()
{
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;
	socklen_t caddrlen;
	int csock;
	int len;
	char buf[512];
	int option;
	pthread_t thread;

	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return 1;
	}

	//--------
	option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);
	//--------

	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000); // 5000;
	saddr.sin_addr.s_addr = INADDR_ANY;

	// bind: socket이 어떤 주소를 가지고 있는지 기록하는 작업
	if (bind(ssock, (struct sockaddr*)&saddr, sizeof saddr) == -1) {
		perror("bind");
		return 1;
	}

	// listen: socket이 연결을 대기할 수 있도록 해준다.
	if (listen(ssock, SOMAXCONN) == -1) {
		perror("listen");
		return 1;
	}

	memset(&caddr, 0, sizeof caddr);
	caddrlen = sizeof caddr;

	while (1) {
		intptr_t arg;
		csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
		if (csock == -1) {
			perror("csock");
			return 1;
		}
		printf("New Connection...\n");
		arg = csock;
		pthread_create(&thread, NULL, thread_routine, (void*)arg);

		// pthread_join을 비동기적으로 수행하는 것이 어렵다.
		// => pthread_detach를 사용하면 스레드 종료시 바로 메모리가 해지될 수 있다.
		pthread_detach(thread);

	}
	close(ssock);

	return 0;
}
