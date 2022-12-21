#include "main.h"

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
