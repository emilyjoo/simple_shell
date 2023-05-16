#include "shell.h"

/**
 * prompt - displays the prompt for stdin
 * @av: argument vector
 * @env: environment variable
 */

void prompt(char **av, char **env)
{
	char *str_input = NULL;
	int i, j, position;
	size_t n = 0;
	ssize_t num_char;
	char *argv[] = {NULL, NULL};
	pid_t child_process;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#our_shell$ ");
		num_char = getline(&str_input, &n, stdin);
		if (num_char == -1)
		{
			free(str_input);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (str_input[i])
		{
			if (str_input[i] == '\n')
				str_input[i] = 0;
			i++;
		}
		j = 0;
		argv[j] = strtok(str_input, " ");
		while (argv[j])
			argv[++j] = strtok(NULL, " ");
		child_process = fork();
		if (child_process == -1)
		{
			free(str_input);
			exit(EXIT_FAILURE);
		}
		if (child_process == 0)
		{
			if (execve(argv[0], argv, env) == -1)
				printf("%s: No such file or directory\n", av[0]);
		}
		else
			wait(&position);
	}
}
