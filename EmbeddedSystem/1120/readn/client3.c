#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>

// TCP 프로토콜
//  => 데이터의 길이를 반드시 보내야 한다.
//    len(4):op(1):lhs(4):rhs(4)

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

	// while (fgets(buf, sizeof buf, stdin)) {
	int i;
	char op = '+';
	int lhs = 10, rhs = 32;
	char *p;
	for (i = 0 ; i < 1000 ; ++i) {
		p = buf;
		*p = op;
		p += sizeof(op);

		*(int*)p = lhs;
		p += sizeof(lhs);

		*(int*)p = rhs;
		p += sizeof(rhs);

		int len = p - buf;
		write(csock, &len, sizeof len); 
		write(csock, buf, len);
	}

	close(csock);
}










