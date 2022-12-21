#include "main.h"

/**
 * check_builtin - checks if a command is a built in
 * @argv: the array that holds the command.
 *
 * Return: 0 if a command is a builtin
 *         1 if a command is not a builtin.
 */

int check_builtin(char **argv)
{
	int i;

	char *builtin[] = {"exit", "cd", "env", NULL};

	i = 0;

	while (builtin[i])
	{
		if (argv[0] == builtin[i])
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

	if (check_builtin(argv) == 0)
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
