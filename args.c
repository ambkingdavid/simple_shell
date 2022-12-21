#include "main.h"

/**
 * get_args - gets the arguments from stdin
 * @line: buffer to store the args
 *
 * Return: number of bytes read
 */

ssize_t get_args(char **line)
{
	char *prompt;
	size_t n;
	ssize_t read;

	prompt = "($) ";
	printf("%s", prompt);
	read = getline(line, &n, stdin);
	if (read == -1)
	{
		putchar('\n');
		exit(0);
	}

	return (read);
}

/**
 * split_args -splits the args into tokens
 * @line: the buffer that stores the args
 * @argc: the number of arguments
 *
 * Return: the address to the tokens
 */

char **split_args(char *line, int *argc)
{
	char **tokens, *token;

	*argc = 0;
	if (!line)
		return (NULL);

	tokens = malloc(sizeof(char *) * 100);
	if (!tokens)
		return (NULL);

	token = strtok(line, " \n");

	while (token)
	{
		tokens[(*argc)] = token;
		token = strtok(NULL, " \n");
		++(*argc);
	}
	tokens[*argc] = NULL;

	return (tokens);
}

/**
 * check_cmd - checks if a command is valid
 * @cmd: the command
 * @st: a struct stat
 *
 * Return: 0 if the command exits
 *         1 if the command does not exit or not executable
 */

int check_cmd(char *cmd, struct stat *st)
{
	int result_exe, result_cmd;

	result_exe = stat(cmd, st);
	result_cmd = check_builtin(cmd);

	if (result_cmd == 0)
	{
		return (0);
	}
	if (result_exe == 0)
	{
		if (st->st_mode & S_IXUSR)
			return (0);
		perror(cmd);
		return (1);
	}
	else
	{
		perror(cmd);
		return (1);
	}
	return (1);
}
