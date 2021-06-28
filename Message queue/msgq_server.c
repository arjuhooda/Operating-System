#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
	long mtype;
	char num[64];
};
int main(void)
{
	struct msgbuf buffer;
	int msqid;
	key_t key;
	
	if ((key = ftok("msgq_server.c", 'A')) == -1) { 
		perror("ftok");
		exit(1);
	}
	
	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) { 
		perror("msgget");
		exit(1);
	}
	
	printf("Waiting for clients...\n");
	while(1) 
	{ 
		if (msgrcv(msqid, &buffer, sizeof(buffer.num), 0, 0) == -1) 
		{
			perror("msgrcv");
			exit(1);
		}
		
		int k = atoi(buffer.num), j;
		char binary[64];
		printf("Received number from client %ld: %d\n",buffer.mtype, k );
		
		for(j=0;k>0;j++)    
		{    
			binary[j]= k%2 + '0';    
			k=k/2;    
		}  
		binary[j] = '\0';
		int len = strlen(binary);
		j=0;
		for(int i = len-1; i>=0; i--)
		{
			buffer.num[j] = binary[i];
			j++;
		}
		buffer.num[j] = '\0';
		printf("Binary format: %s\n", buffer.num);
		
		if (msgsnd(msqid, &buffer, sizeof(buffer.num), 0) == -1) 
			perror("msgsnd");
	}
	
	if (msgctl(msqid, IPC_RMID, NULL) == -1) 
	{
		perror("msgctl");
		exit(1);
	}
	return 0;
}
