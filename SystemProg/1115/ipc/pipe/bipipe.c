#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define 	MAXBUFF 	1024
void client(int readfd, int writefd){
	char 	buff[MAXBUFF];
	int 	n;

	if(fgets(buff, MAXBUFF, stdin) == NULL)
		printf("client: filename read error");
	n = strlen(buff);
	if(buff[n-1] == '\n')
		n--;
	if(write(writefd, buff, n) != n)			/* 파일 이름 전송 */
		printf("client: filename write error");

	while((n = read(readfd, buff, MAXBUFF)) > 0)	/* 파일 데이터 수신 */
		if(write(1, buff, n) != n)
			printf("client: data write error");
	if(n < 0)
		printf("client: data read error");
}

void server(int readfd, int writefd){
	char 	buff[MAXBUFF];
	int 	n, fd;  extern int errno;

	if ((n = read(readfd, buff, MAXBUFF)) <= 0)	/* 파일 이름 수신 */
		printf("server: filename read error");
	buff[n] = '\0';

	if ((fd = open(buff, O_RDONLY)) < 0) {
		strcat(buff, " can’t open\n");  
		n = strlen(buff);
		if(write(writefd, buff, n) != n)		/* 에러 메시지 전송 */
			printf("server: errmesg write error");
	} 	else {
		while((n = read(fd, buff, MAXBUFF)) > 0)
			if(write(writefd, buff, n) != n)	/* 파일 데이터 전송 */
				printf("server: data write error");
	}
}

int main(void){
	int 	childpid, pipe1[2], pipe2[2];

	if(pipe(pipe1) < 0 || pipe(pipe2) < 0)
		printf("pipe error");

	childpid = fork();
	if(childpid > 0) { 		/* parent process */
		close(pipe1[0]);
		close(pipe2[1]);
		client(pipe2[0], pipe1[1]);
		while(wait((int *) 0) != childpid);
		close(pipe1[1]);
		close(pipe2[0]);
	} else { 				/* child process */
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0], pipe2[1]);
		close(pipe1[0]);
		close(pipe2[1]);
	}
} 

