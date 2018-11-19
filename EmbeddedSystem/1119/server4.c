#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <arpa/inet.h>    // !!
#include <netinet/in.h>

#include <signal.h>
#include <sys/wait.h>

#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

// 동시 처리 서버
//  : 클라이언트들의 요청을 동시에 처리할 수 있어야 한다.
// 1. fork() : 멀티 프로세스 기반 서버
//   1) 부모 프로세스: accept
//   2) 자식 프로세스: socket(csock) - read / write
//  => 좀비 프로세스를 방지해야 한다.

// 2. pthread_create() : 멀티 스레드 기반 서버
// 3. poll / epoll: 멀티 플렉싱 기반 서버

// 자식 프로세스의 종료를 비동기적으로 수거한다.
void on_disconnected(int signum) {
	while (waitpid(0, NULL, WNOHANG) > 0) {
		printf("disconnected...\n");
	}
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
	pid_t pid;

	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return 1;
	}

	signal(SIGCHLD, on_disconnected);

	option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);

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
		csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
		if (csock == -1) {
			perror("csock");
			return 1;
		}
		printf("New Connection...\n");
		pid = fork();
		if (pid == 0) {
			close(ssock);

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
			exit(0);
		} else if (pid == -1) {
			perror("fork");
			exit(1);
		}
	}
	close(ssock);

	return 0;
}














