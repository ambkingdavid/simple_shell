#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


char **parse_command_line(char *command_line) {
  char **arguments = malloc(8 * sizeof(char *));
  if (arguments == NULL) {
    perror("malloc");
    exit(1);
  }

  int size = 8;
  int i = 0;
  char *token = strtok(command_line, " \t\n");
  while (token != NULL) {
    if (i == size) {
      // Array is full, allocate more memory
      size *= 2;
      char **new_arguments = realloc(arguments, size * sizeof(char *));
      if (new_arguments == NULL) {
        perror("realloc");
        exit(1);
      }
      arguments = new_arguments;
    }
    arguments[i] = token;
    i++;
    token = strtok(NULL, " \t\n");
  }
  arguments[i] = NULL;

  return arguments;
}

void execute_command(char *command, char **arguments, char **environment) {
  if (strcmp(command, "cd") == 0) {
    // Built-in command, handle it directly
    // ...
  } else {
    // Command is not a built-in, try to execute it as an external program
    pid_t child_pid = fork();
    if (child_pid == 0) {
      // This is the child process, execute the program
      execve(command, arguments, environment);
      // If execve returns, it means an error occurred
      perror("execve");
      exit(1);
    } else if (child_pid > 0) {
      // This is the parent process, wait for the child to finish
      int child_status;
      waitpid(child_pid, &child_status, 0);
    } else {
      // Fork failed
      perror("fork");
      exit(1);
    }
  }
}

int main(int argc, char *argv[], char *envp[]) {
  char *line = NULL;
  size_t line_size = 0;
  ssize_t line_length;
  
  while ((line_length = getline(&line, &line_size, stdin)) != -1) {
	  printf("%ld\n", line_length);
	  if (line_length == 1)
		  continue;
    char **arguments = parse_command_line(line);
    execute_command(arguments[0], arguments, envp);
    free(arguments);
    
    free(line);
    line = NULL;
    line_size = 0;
  }
  
  free(line);
  
  return 0;
}
