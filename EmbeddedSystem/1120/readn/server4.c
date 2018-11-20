#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>

#include "packetlib.h"

ssize_t readn(int fd, void *vptr, size_t n);

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
		int packetlen;
		
		int len = readn(csock, &packetlen, sizeof packetlen);
		if (len <= 0) {
			break;
		}

		len = readn(csock, buf, packetlen);
		if (len <= 0) {
			break;
		}

		struct packet packet;
		construct(&packet, buf);
		
		op = read_byte(&packet);
		lhs = read_int32(&packet);
		rhs = read_int32(&packet);

		printf("op: %c, lhs: %d, rhs: %d\n", op, lhs, rhs);

		// write(csock, buf, len);
	}

	close(csock);
	close(ssock);
}





