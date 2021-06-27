#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
	int pfds1[2], pfds2[2];
	char buf[40];
	pipe(pfds1);	// pipe for child to parent communication
	pipe(pfds2);	// pipe for parent to child communication
	if(!fork())
	{
		close(pfds1[0]);
		close(pfds2[1]);
		printf("Child--Parent: Please give content of file test.txt\n");
		write(pfds1[1], "test.txt", 9);
		while(read(pfds2[0],buf, 40)>0)
			printf("%s",buf);
		printf("Child--Parent: Exit\n");
		exit(0);
	}
	else
	{
		close(pfds1[1]);
		close(pfds2[0]);
		read(pfds1[0], buf, 40);
		FILE *f = fopen(buf,"r");
		if(f != NULL)
		{
			printf("Parent--Child: Contents of the file\n");
			while(fgets(buf, 40, f) != NULL)
				write(pfds2[1], buf, 40);
			close(pfds2[1]);	
		}
		else
			printf("File Not Exist.\n");
		fclose(f);
		wait(NULL);
				 
	}
	return 0;
}
