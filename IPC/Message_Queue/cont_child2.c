#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<stdio.h>
#include<stdlib.h>

struct my_msgbuf 
{
	long mtype;       /* message type, must be > 0 */
        char mtext[100];    /* message data */
 };


int main()
{
	struct my_msgbuf buf1;
	key_t msg_key;int msg_id;
	msg_key=ftok("file.txt",0);
	if((msg_id=msgget(msg_key,IPC_EXCL|0664))==-1)
	{
		perror("Message queue fails");
		return -1;
	}
	printf("msgget success..\n");
	int i;
	for(i=0;;i++)
	{
	if(msgrcv(msg_id,&buf1,sizeof(buf1.mtext),2,0)==-1)
	{
		perror("msgrcv fails..\n");
		return -1;
	}
	printf("msgrcv1 success..\n");
printf("%s\n",buf1.mtext);
	/*if(msgrcv(msg_id,&buf,sizeof(buf.mtext),0,0)==-1)
	{
		perror("msgrcv fails..\n");
		return -1;
	}
	printf("msgrcv2 success..\n");
printf("%s\n",buf.mtext);*/
	}
	
}

