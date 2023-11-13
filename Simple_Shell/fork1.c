#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t pid;

    printf("Before fork\n");
    pid = fork();
    if (pid == -1)
    {
        perror("Error:");
        return (1);
    }

    if (pid == 0)
    {
        my_pid = getpid();
        printf("Nooooooooooooo. My pid is %u\n", my_pid);
    }
    else
    {
        my_pid = getpid();
        printf("I am your father. My pid is %u\n", my_pid);
    }
    
    printf("After fork\n");

    return (0);
}

