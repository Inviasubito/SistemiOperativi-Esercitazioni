#include <unistd.h>	//fork
#include <stdio.h>	//printf
#include <stdlib.h>	//exit
#include <sys/wait.h>	//wait	
#include <sys/types.h>	//pid_t
#include <string.h>	//scanf

void interpreter();
void execute(char*);
void clear_vector(char**, int);
void print_vector(char**, int, int);

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
			interpreter();
			break;
		default:
			waitpid(pid, &status, 0);

			if(WEXITSTATUS(status)==1)
				printf("Terminated.\n");
			else 
				main();

			exit(0);
			break;
	}

	return 0;
}

void interpreter()
{
	char str[100];
	printf("DRB Command: ");

	if(scanf("%[^\n]s", str) != 1)
		printf("- invalid.\n");
	else if(strcmp(str, "q") == 0)
	{
		printf("exit\n");
		//kill(getppid(), SIGKILL);
	}
	else
		execute(str);

	exit(1);
}

void execute(char* str)
{
	const int MAX_FLAGS = 10;
	char* token = strtok(str, " ");
	char* flags[MAX_FLAGS];
	int i = 0;

	//Pulisco il vettore
	clear_vector(flags, MAX_FLAGS);

	//recupero tutti i segmenti
	while(token != NULL)
	{
		flags[i++] = token;       		
		token = strtok(NULL, " ");
	}

	//Stampo un resoconto
	printf("Path: %s \n", flags[0]);
	printf("Flags count: %d \n", i - 1);
	
	if(i > 1)
	{
		//Offset 1 perchè l'elemento 0 è il path
		printf("Flags: ");
		print_vector(flags, MAX_FLAGS, 1);
		printf("\n");
	}

	//Eseguo
	int exe = execvp(flags[0], flags);
	printf("L'esecuzione del comando %s ha causato un errore..\n", flags[0]);
	printf("Controlla la sintassi e riprova. \n");
	printf("Codice di errore: %d \n", exe);
}

void clear_vector(char** arr, int size)
{
	for(int i = 0; i < size; i++)
		arr[i] = NULL;
}

void print_vector(char** arr, int size, int offset)
{
	for(int i = offset; i < size; i++)
	{
		if(arr[i] != NULL)
			printf("%s ", arr[i]);
	}
}
