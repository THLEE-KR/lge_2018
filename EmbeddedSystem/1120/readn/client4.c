#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>




int main()
{
	struct sockaddr_in saddr;
	char buf[512];

	int csock = socket(PF_INET, SOCK_STREAM, 0);
	if (csock == -1) {
		perror("socket");
		return 1;
	}

	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(csock, (struct sockaddr*)&saddr, sizeof saddr) == -1) {
		perror("connect");
		return 1;
	}

	int i;
	char op = '+';
	int lhs = 10, rhs = 32;
	char *p;
	for (i = 0 ; i < 1000 ; ++i) {
		struct packet packet;
		construct(&packet, buf);

		write_byte(&packet, op);
		write_int32(&packet, lhs);
		write_int32(&packet, rhs);
		int len = packet_length(&packet);

		write(csock, &len, sizeof len); 
		write(csock, buf, len);
	}

	close(csock);
}










