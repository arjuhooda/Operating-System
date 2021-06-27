#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

int main()
{
	if(!fork())
	{
		printf("----- CHILD PROCESS -----\n");
		printf("Child PID: %d\n", getpid());
		printf("Parent PID: %d\n", getppid());
		printf("Client Program:\n");
		char *args[] = {"./Clientprogram", NULL};
		execvp(args[0], args);
		exit(0);
	}
	system("ps");
	return 0;
}
