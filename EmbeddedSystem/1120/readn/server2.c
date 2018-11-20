#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>

// readn: Effective TCP/IP
//   TCP Stream 기반의 패킷을 처리하는 가장 완벽한 방법.

int main()
{
	int ssock;
	int option;
	struct sockaddr_in saddr;

	int csock;
	struct sockaddr_in caddr;
	socklen_t caddrlen;

	ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return -1;
	}

	option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);

	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;	
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
	if (bind(ssock, (struct sockaddr*)&saddr, sizeof saddr) == -1) {
		perror("bind");
		return 1;
	}

	if (listen(ssock, SOMAXCONN) == -1) {
		perror("listen");
		return 1;
	}

	memset(&caddr, 0, sizeof caddr);
	caddrlen = sizeof caddr;
	csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
	if (csock == -1) {
		perror("accept");
		return 1;
	}
	
	char op;
	int lhs, rhs;
	char *p;
	while (1) {
		char buf[512];
		int len = read(csock, buf, sizeof buf);
		if (len == 0) {
			printf("연결이 종료되었습니다.. \n");
			break;
		} else if (len == -1) {
			perror("read");
			break;
		}

		p = buf;
		op = *p;
		p += sizeof(op);

		lhs = *(int*)p;
		p += sizeof(lhs);

		rhs = *(int*)p;
		p += sizeof(rhs);

		printf("op: %c, lhs: %d, rhs: %d\n", op, lhs, rhs);

		// write(csock, buf, len);
	}

	close(csock);
	close(ssock);
}





