#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100

int main(void) 
{
    const char* input = "This is my sample string";
    const char* delimiter = " ";
    
    char* copy = strdup(input);
    if (!copy) 
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    char* token = strtok(copy, delimiter);
    size_t count = 0;

    char** words = (char**)malloc(MAX_WORDS * sizeof(char*));
    if (!words) 
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    while (token != NULL && count < MAX_WORDS) 
    { 
        words[count] = strdup(token);
        if (!words[count]) 
        {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, delimiter);
        count++;
    }

    printf("Number of words: %zu\n", count);
    for (size_t i = 0; i < count; i++) 
    {
        printf("Word %zu: %s\n", i + 1, words[i]);
        free(words[i]);
    }

    free(words);
    free(copy);

    return 0;
}

