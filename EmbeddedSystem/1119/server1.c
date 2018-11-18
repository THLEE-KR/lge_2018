// TCP/IP Network Programming
//  => Socket Programming

// Socket 종류
//  1. Socket : 데이터 read / write
//  2. Listen Socket(Server Socket): accept 

// Server
// 1. socket
// 2. bind
// 3. listen
// 4. accept

#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

// Internet Protocol
#include <arpa/inet.h>    // !!
#include <netinet/in.h>

#include <string.h> 
#include <stdio.h>


#if 0
int bind(int sockfd, const struct sockaddr *addr,
		socklen_t addrlen);
#endif

int main()
{
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;
	socklen_t caddrlen;
	int csock;
	int len;
	char buf[512];

	// int fd = open(...);
	// SOCK_STREAM: TCP
	// SOCK_DGRAM:  UDP
	int ssock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000); // 5000;
	saddr.sin_addr.s_addr = INADDR_ANY;

	// bind: socket이 어떤 주소를 가지고 있는지 기록하는 작업
	bind(ssock, (struct sockaddr*)&saddr, sizeof saddr);

	// listen: socket이 연결을 대기할 수 있도록 해준다.
	listen(ssock, SOMAXCONN);

	memset(&caddr, 0, sizeof caddr);
	caddrlen = sizeof caddr;

	// accept: session을 생성하는 함수
	csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
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














