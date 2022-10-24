#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int status;
	int pid = fork();

    switch(pid)
	{
		case -1:
			printf("fork error.\n");
			break;
		case 0:
            printf("Sleep...\n");
			sleep(5);
            printf("Run \n");
            exit(5);
			break;
		default:
			wait(&status);
			printf("Status: %d \n", status);

			break;
	}

	return 0;    
}