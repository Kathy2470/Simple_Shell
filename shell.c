#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void) 
{	
	pid_t child_pid;
	char *buf = NULL;
	size_t buf_size = 0;
	char *token;
	int status, i = 0;
	char **array;
	
	while (1)
	{
		write(1, "#cisfun$ ", 9);
		getline(&buf, &buf_size, stdin);
		token = strtok(buf, "\t\n");
		array = malloc(sizeof(char *) * 1024);

		while (token)
		{
			array[i] = token;
			token = strtok(NULL, "\t\n");
			i++;
		}
			child_pid =fork();
			array[i] = NULL;
			
		if (child_pid == 0)
		{
			if (execve(array[0], array, NULL) == -1)
				perror("Error");
		}
		else
		{
		wait(&status);
		}

		i = 0;
		free(array);
	}
}
