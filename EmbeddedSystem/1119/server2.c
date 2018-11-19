#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

// Internet Protocol
#include <arpa/inet.h>    // !!
#include <netinet/in.h>

#include <string.h> 
#include <stdio.h>

// Server Socket이 먼저 close 하면, TIME_WAIT 상태가 됩니다.
// -> Listen Socket은 TIME_WAIT 의미가 없다.
// => socket option을 통해 TIME_WAIT을 금지한다.
int main()
{
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;
	socklen_t caddrlen;
	int csock;
	int len;
	char buf[512];
	int option;

	// int fd = open(...);
	// SOCK_STREAM: TCP
	// SOCK_DGRAM:  UDP
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

	// accept: session을 생성하는 함수
	csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
	if (csock == -1) {
		perror("csock");
		return 1;
	}
	printf("New Connection...\n");

	// Echo Server
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
	close(ssock);

	return 0;
}














