#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) 
{
    int i;

    for (i = 0; i < 5; i++) 
   {
        pid_t child_pid = fork();

        if (child_pid == -1) 
	{
            perror("Error:");
            return (1);
        }

        if (child_pid == 0) 
	{
            
            char *argv[] = {"ls", "-l", "/tmp", NULL};
            if (execve("/usr/bin/ls", argv, NULL) == -1) 
	    {
                perror("Error:");
                return (1);
            }
        } else 
	{
            
            wait(NULL); 
        }
    }

    return (0);
}

