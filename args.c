#include "main.h"

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

int check_cmd(char *cmd, struct stat *st)
{
	int result;

	result = stat(cmd, st);

	if (result == 0)
	{
		if (st->st_mode & S_IXUSR)
			return (0);
		else
		{
			return (1);
		}
	}
	else
	{
		return (1);
	}
}
