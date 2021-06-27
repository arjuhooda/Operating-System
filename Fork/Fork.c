#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	printf("------ SYSTEM STATUS BEFORE FORKING ------\n");
	int status1 = system("ps");
	printf("\n");
	pid_t pid;
	for(int i=0; i<5; i++)
	{
		pid = fork();
		if(pid == -1)
		{
			printf("Error\n");
			exit(0);
		}
		else if(pid == 0)
		{
			printf("Child PID: %d  ", getpid());
			printf("Parent PID: %d\n", getppid());
			if(i == 0)
				printf("\n------ SYSTEM STATUS AFTER FORKING ------\n");
			exit(0);
		}
		
	}
	int status2 = system("ps");
	return 0;
}

