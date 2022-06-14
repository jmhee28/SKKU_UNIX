#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

#define T_MSG 20
#define MAX_LEN 512

struct msg
{
	long msgtype;
	int sender;
	char text[MAX_LEN];
};

struct msg_rt
{
	long msgtype;
	char timestamp[MAX_LEN];
};

int main()
{
	key_t key = ftok(".", 'a');
	int my_id, receiver_id, pid;

	printf("My id: ");
	scanf("%d", &my_id);
	getchar();
	printf("Receiver's id: ");
	scanf("%d", &receiver_id);
	getchar();

	int qid = msgget(key, IPC_CREAT | 0x1FF);

	if (qid < 0)
	{
		perror("msgget faild");
	}
	/* Please do not modify up to this point */

	if ((pid = fork()) == 0)
	{
		while (1)
		{
			struct msg m; 
			if (msgrcv(qid, (void *)&m, sizeof(struct msg), my_id, IPC_NOWAIT) > 0)
			{
				
				printf("RECEIVED: %s", m.text);
				struct msg_rt t;
				struct msg_rt *temp = &t;
				time_t t1;
				time(&t1);
				strcpy(temp->timestamp, ctime(&t1));
				temp->msgtype = receiver_id + 0x10000;
				msgsnd(qid, (void *)temp, sizeof(struct msg_rt), IPC_NOWAIT);
			}
			if (msgrcv(qid, (void *)&m, sizeof(struct msg), my_id + 0x10000, IPC_NOWAIT) > 0)
			{
				printf("ACK FROM %d AT\t%s", receiver_id, m.text);
			}
		}
	}
	else
			{
				while (1)
				{
					struct msg n;
					n.msgtype = receiver_id;
					fgets(n.text, 256, stdin);
					if(strcmp(n.text, "quit\n")==0)
					{
						printf("QUIT\n");
						kill(pid,SIGKILL);
						exit(0);
					}
					msgsnd(qid, (void *)&n, sizeof(struct msg), 0); 
																	
				}
			}

			return 0;
}
