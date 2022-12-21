#include "main.h"

/**
 * exit_cmd - terminate a process
 * @argv: process id in string format
 * @argc: num of args
 *
 * Return: exit_success
 */

int exit_cmd(char **argv, int argc)
{
	int status;

	if (argc == 1)
		exit(0);
	else if (argc == 2)
	{
		status = atoi(argv[1]);
		if (status == 0 && strcmp(argv[1], "0") != 0)
		{
			return (-1);
		}
		else
			exit(status);
	}
	status = atoi(argv[argc - 1]);
	exit(status);
}

/**
 * get_builtin - gets the built command function
 * @s: builtin name;
 *
 * Return: pointer to the function
 */

int (*get_builtin(char *s))(char **, int)
{
	struct builtin_t ops[] = { {"exit", exit_cmd}, {NULL, NULL} };
	int i;

	i = 0;

	while (ops[i].name != NULL && strcmp(ops[i].name, s) != 0)
		i++;

	return (ops[i].f);
}
