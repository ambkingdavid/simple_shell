#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ;

/**
 * struct alias - A linked list alias structure.
 * @name: The alias name.
 * @value: The corresponding value of the alias.
 * @next: the pointer to the next alias
 */

struct alias
{
	char *name;
	char *value;
	struct alias *next;
};

/**
 * struct builtin_t - A struct builtin.
 * @name: The builtin command.
 * @f: The associated function.
 */
typedef struct builtin_t
{
	char *name;
	int (*f)(char **filename, int argc);
} builtin;

/* testing */
ssize_t get_args(char **line);
char **split_args(char *line, int *argc);
void execute(char **argv, int argc);
void exec_builtin(char **argv, int argc);
int check_cmd(char *cmd, struct stat *st);



/*builtin commamnd functions*/
int exit_cmd(char **argv, int argc);
int (*get_builtin(char *s))(char **, int);

/*alias handler*/
int add_alias(char *name, char *value);
char *find_alias(char *name);
void remove_alias(char *name);
int handle_alias(int argc, char *argv[]);


/*helper functions*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *line, char *delim);

/*env -- memory helpers*/
char **copy_env();
void free_env(char **e);

/*utilities*/
char *remove_newline(char *str);
ssize_t line_get(char **line, size_t *n);
char **parse_str(char *line, int *argc, char **cmd);
int validate_cmd(char *shell, int loop_count, char *cmd);

/*errors*/
int cmd_error(char *shell, int loop_count, char *cmd);

#endif
