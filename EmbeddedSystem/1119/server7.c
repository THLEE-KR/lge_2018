#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/epoll.h>

#include <arpa/inet.h>    // !!
#include <netinet/in.h>

#include <string.h> 
#include <stdio.h>

// epoll - Linux System Call
//  : 최신 커널에서 지원하는 고성능 IO 모델의 핵심 시스템 콜입니다.
// Linux   - epoll
// Windows - IOCP
// Solaris - kqueue

// 1. 사용자가 직접 디스크립터를 관리하지 않는다.
//   => 커널이 관리한다.
// 2. 이벤트가 발생한 디스크립터를 배열로 직접 만들어준다.
// 3. 비동기 모델을 지원한다.

int main()
{
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;
	socklen_t caddrlen;
	int csock;
	int len;
	char buf[512];
	int option;
	int efd;
	struct epoll_event event;

	// 1. epoll 저장소를 생성합니다.
	efd = epoll_create1(0);
	if (efd == -1) {
		perror("epoll_create1");
		return 1;
	}

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

	// Server 소켓을 등록한다.
	event.data.fd = ssock;
	event.events = EPOLLIN;
	epoll_ctl(efd, EPOLL_CTL_ADD, ssock, &event);

	while (1) {
		int i;
		struct epoll_event revents[1024];
		int ret = epoll_wait(efd, revents, 1024, -1);
		if (ret == 0)
			continue;
	
		for (i = 0 ; i < ret ; ++i) {
			if (revents[i].data.fd == ssock) {
				memset(&caddr, 0, sizeof caddr);
				caddrlen = sizeof caddr;
				csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
				if (csock == -1) {
					perror("csock");
					return 1;
				}
				printf("New Connection...\n");
				event.data.fd = csock;
				event.events = EPOLLIN;
				epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event);
			} else {
				csock = revents[i].data.fd;
				len = read(csock, buf, sizeof buf);
				if (len <= 0) {
					close(csock);
					epoll_ctl(efd, EPOLL_CTL_DEL, csock, NULL);
					break;
				}

				write(csock, buf, len);
			}
		}
	}
	close(ssock);

	return 0;
}














