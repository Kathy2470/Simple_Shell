#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char str[] = "This is my sample string";
    char delim[] = " "; 
    char *token;

    token = strtok(str, delim);
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, delim);
    }

    return 0;
}

