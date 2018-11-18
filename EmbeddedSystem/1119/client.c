#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string.h>
#include <stdio.h>

// socket
// connect

int main()
{
	struct sockaddr_in saddr;
	char buf[512];
	int ret;

	// inet_addr: 문자열의 IPv4 주소를 32 비트 빅 엔디안으로 변경한다.
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sock, (struct sockaddr*)&saddr, sizeof saddr);

	while ((ret = read(0, buf, sizeof buf)) > 0) {
		write(sock, buf, ret);

		ret = read(sock, buf, sizeof buf);
		write(1, buf, ret);
	}

	close(sock);
}









