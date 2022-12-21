#include "main.h"

/**
 * main - a simple shell
 * @ac: number of args.
 * @av: array of arguments
 *
 * Return: 0 on success
 */

int main(int ac, char *av[])
{
	int argc;
	char **argv;
	char *line;
	struct stat st;

	(void)ac;
	(void)av;
	while (1)
	{
		get_args(&line);
		argv = split_args(line, &argc);
		if (check_cmd(argv[0], &st) != 0)
			continue;
		execute(argv, argc);
	}

	return (0);
}
