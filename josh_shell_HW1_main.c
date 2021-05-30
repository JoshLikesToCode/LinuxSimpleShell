/**************************************************************
* Description: For this project we're creating a simple shell
*	       which parses user input and then executues the
*	       user's commands.
****************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX 512

/* prompt for user */
void prompt()
{
	printf("> ");
}

/* helper function to test tokens */
void print_input1(char** string, int size)
{
	char* pc = *string;
	for(int i = 0; i < size; i++)
	{
		string = string + i;
		pc = *string;
		while(*pc != 0)
		{
			printf("%c", *pc);
			pc += 1;
		}
		printf("\n");
	}
}

int main()
{

	while(1)
	{
		prompt();
		int i = 0, status;
		char user_input[MAX+1];

		if (fgets(user_input, MAX, stdin) != NULL)
		{
			while(user_input[0] == ' ' || user_input[0] == '\n')
			{
				printf("Exiting..\n");
				return -1;
			}
			user_input[strlen(user_input)-1] = '\0';
			//print_input(user_input);

			char *p = strtok(user_input, " \n");
			char *tokens[(MAX/2)+1];

			/* tokenize user input */
			while(p)
			{
				tokens[i++] = strdup(p);
				p = strtok(NULL, "\n");
			}
			tokens[i] = NULL;
			//print_input1(tokens, i);

			/* provide a way to exit the shell */
                        if(strcmp(tokens[0], "exit") == 0)
                        {
                                exit(0);
                        }

			int pid = fork();

			/* child process */
			if(pid == 0)
			{
				execvp(tokens[0], tokens);
				return -1; /* error if we get here */
			}
			else if(pid > 0) /* parent process */
			{
				/* wait and return pid # along with status of child */
				waitpid(pid, &status, 0);
				if(WIFEXITED(status))
				{
					int exit_status = WEXITSTATUS(status);
					printf("Child %d exited with a status %d\n", pid, exit_status);
				}
			}
		}
		else
		{	/* invalid user input */
			printf("Error, please try again with valid input.\n");
		}
	}
}

