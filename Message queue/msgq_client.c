#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
	long mtype;
	char num[200];
};

int main(void)
{
	struct msgbuf buffer;
	int msqid;
	key_t key;
	long x;
	
	if ((key = ftok("msgq_server.c", 'A')) == -1) 
	{
		perror("ftok");
		exit(1);
	}
	if ((msqid = msgget(key, 0644)) == -1) 
	{
		perror("msgget");
		exit(1);
	}
	printf("Enter a unique client number: ");
	scanf("%ld",&x);
	buffer.mtype = x; 
	getchar();
	printf("Enter an interger: ");
	while(fgets(buffer.num, sizeof buffer.num, stdin) != NULL) 
	{
		int len = strlen(buffer.num);
		if (buffer.num[len-1] == '\n') 
			buffer.num[len-1] = '\0';
			
		if (msgsnd(msqid, &buffer, len+1, 0) == -1) 
			perror("msgsnd");
			
		if (msgrcv(msqid, &buffer, sizeof(buffer.num), x, 0) == -1) 
		{
			perror("msgrcv");
			exit(1);
		}
		printf("Received binary format: %s\n", buffer.num);
		printf("Enter an interger: ");
	}
		
	return 0;
}
