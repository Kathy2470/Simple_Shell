#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void check_command(char *command) 
{
    char full_path[4096];
    FILE *fp;
    char *which_cmd = "/usr/bin/which"; 

    snprintf(full_path, sizeof(full_path), "%s %s", which_cmd, command);

    fp = popen(full_path, "r");
    if (fp == NULL) 
    {
        perror("popen");
        return;
    }

    if (fgets(full_path, sizeof(full_path), fp) != NULL) 
    {
        full_path[strcspn(full_path, "\n")] = '\0';
	  {
       		printf("checking command: %s\n", command);

        	if (access(command, F_OK) == 0) 
	
            	printf("CISFUN$: %s: FOUND THE FILE\n", command);
         
		else 
	
            	printf("CISFUN$: %s: FILE DOESN'T EXIST\n", command);
           }
    }

    pclose(fp);
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    char *token;

    while (1) {
        write(1, "CISFUN$", 8);
        getline(&buffer, &buffer_size, stdin);
        token = strtok(buffer, "\t\n");

        if (strcmp(token, "which") == 0) 
	{
	    token[strcspn(token, "\n")] = '\0';
            token = strtok(NULL, "\t\n");
            while (token) 
	    {
                check_command(token);
                token = strtok(NULL, "\t\n");
            }
        } else {
            write(1, "COMMAND DOESN'T EXIST\n", 22);
        }
    }

    free(buffer);
    return 0;
}

