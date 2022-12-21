#include "main.h"

/**
 * execute - executes the command
 * @argv: array that stores the command and args
 * @argc: number of args
 */


void execute(char **argv, int argc)
{
	pid_t pid;

	(void)argc;

	if ((get_builtin(argv[0])(argv, argc)) != 0)
	{

	}
	else
	{

		pid = fork();


		if (pid < 0)
			perror("Error");
		else if (pid > 0)
			wait(NULL);
		else
		{
			execvp(argv[0], argv);
			exit(0);
		}
	}
}
