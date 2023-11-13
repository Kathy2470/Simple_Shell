#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int main(void) 
{
    int i = 0;

    while (environ[i] != NULL) 
    {
        printf("%s\n", environ[i]);
        i++;
    }

    return (0);
}

