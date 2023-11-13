#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;

    while (1) 
{
        printf("kathylene$ ");
        ssize_t getline_result = getline(&input, &input_size, stdin);

        if (getline_result == -1) 
	{

            printf("\n");
            break;
        }

        input[getline_result - 1] = '\0';

        printf("%s\n", input);
    }

    free(input);
    return 0;
}

