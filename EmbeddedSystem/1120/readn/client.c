#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>

// Protocol을 설계해야 합니다.
//  client> 2 + 2 
//  => parsing
//     op(1):lhs(4):rhs(4)
//     op(max): values0(10), values1(20), values2(30)
//  => 서비스가 제공하고 있는 연산에 따라서 데이터의 길이는 달라진다.

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
	char op;
	int lhs, rhs;
	char *p;
	while (scanf("%d %c %d", &lhs, &op, &rhs) == 3) {
		printf("lhs: %d, rhs: %d, op: %c\n", lhs, rhs, op);

		// op(1):lhs(4):rhs(4)

		p = buf;
		*p = op;
		p += sizeof(op);

		*(int*)p = lhs;
		p += sizeof(lhs);

		*(int*)p = rhs;
		p += sizeof(rhs);

		// write(csock, buf, p - buf);
	}

	close(csock);
}










