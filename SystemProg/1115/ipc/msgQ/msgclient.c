// gcc msgclient.c msglib.c -o client
#include "msglib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int qid, st;
	MSG_t msg;

	qid = OpenMQ(5000);

	if(qid < 0)
	{
		printf("q open fail: %d\n",errno);	
		return -1;
	}

	while(1) {
		int len;

		memset(msg.mtext,'\0',100); 
		printf("\ninput : ");
		fgets(msg.mtext, sizeof msg.mtext, stdin);
		len = strlen(msg.mtext);
		if (len > 0)
			msg.mtext[len - 1] = '\0';

		if(SendMQ(qid,1L,msg)<=0)   {
			printf("q send fail: %d\n",errno);	
			break;
		}

		if(!strcmp(msg.mtext, "exit"))    {
			printf("Client Process Exit\n");	
			break;
		}
		st = RecvMQ(qid, getpid(),&msg);
		if(st>0)
			printf("recv : %s\n", msg.mtext);
	}
	return 0;
}
