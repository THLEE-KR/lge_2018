#ifndef MSGLIB_H
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#if 0
/* msgsnd와 msgrcv 호출을 위한 메세지 버퍼 */
struct msgbuf {
		long mtype;	/* type of message 메세지 타입 */
		char mtext[1];	/* message text 메세지 내용 */
};
#endif

typedef struct msg_q
{
	long to_mtype;
	//------------
	long fm_mtype;
	char mtext[100];
	//------------
} MSG_t;

int  CreateMQ( key_t );
int  OpenMQ( key_t );
long RecvMQ( int qid, long mtype, MSG_t *msgbuf );
long SendMQ( int qid, long mtype, MSG_t msgbuf );
int  RemoveMQ( int qid );
#endif
