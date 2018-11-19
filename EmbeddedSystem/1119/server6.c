#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

// Internet Protocol
#include <arpa/inet.h>    // !!
#include <netinet/in.h>
#include <poll.h>

#include <string.h> 
#include <stdio.h>

// poll 단점
// 1. 사용자가 직접 디스크립터 배열을 관리해야 한다.
// 2. 성능이 나쁘다.

int main()
{
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;
	socklen_t caddrlen;
	int csock;
	int len;
	char buf[512];
	int option;
	struct pollfd fds[1024];
	int nfds = 0;

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

	fds[0].fd = ssock;
	fds[0].events = POLLIN;
	nfds++;

	while (1) {
		int i;
		int ret = poll(fds, nfds, -1);
		if (ret == 0) 
			continue;
			
		if (fds[0].revents & POLLIN) {
			memset(&caddr, 0, sizeof caddr);
			caddrlen = sizeof caddr;
			csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
			if (csock == -1) {
				perror("csock");
				return 1;
			}

			printf("New Connection...\n");
			fds[nfds].fd = csock;
			fds[nfds].events = POLLIN;
			nfds++;
		}

		for (i = 1; i < nfds ; ++i) {
			if (fds[i].revents & POLLIN) {
				csock = fds[i].fd;
				len = read(csock, buf, sizeof buf);
				if (len <= 0) {
					close(csock);
					fds[i].fd = fds[nfds - 1].fd;
					fds[i].events = fds[nfds - 1].events;
					nfds--;
					break;
				}

				write(csock, buf, len);
			}
		}

	}
	close(ssock);

	return 0;
}














