#include "main.h"

/**
 * check_builtin - checks if a command is a built in
 * @cmd: the command.
 *
 * Return: 0 if a command is a builtin
 *         1 if a command is not a builtin.
 */

int check_builtin(char *cmd)
{
	int i;

	char *builtin[] = {"exit", NULL};

	i = 0;

	while (builtin[i] != NULL)
	{
		if (strcmp(cmd, builtin[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/**
 * execute - executes the command
 * @argv: array that stores the command and args
 * @argc: number of args
 */


void execute(char **argv, int argc)
{
	pid_t pid;

	if (check_builtin(argv[0]) == 0)
	{
		get_builtin(argv[0])(argv, argc);
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
