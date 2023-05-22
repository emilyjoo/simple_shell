#include "shell.h"

void sig_handler(int sig);
int execute(char **args, char **front);

/**
 * sig_handler-New prompt signal
 * @sig: Signal
 */
void sig_handler(int sig)
{
	char *prompt = "\n#our_shell$ ";

	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, prompt, 10);
}

/**
 * execute-Executes a Command in a child process using fork.
 * @args:An array of arguments.
 * @front:2 pointer to the Debus of arguments.
 *
 * Return:Error code.
 *         O/w.
 */
int execute(char **args, char **front)
{
	pid_t child_process;
	int position, i = 0, j = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		i = 1;
		command = get_path(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			j = (costum_error(args, 126));
		else
			j = (costum_error(args, 127));
	}
	else
	{
		child_process = fork();
		if (child_process == -1)
		{
			if (i)
				free(command);
			perror("Error child process:");
			return (1);
		}
		if (child_process == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				j = (costum_error(args, 126));
			_freeenv();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(j);
		}
		else
		{
			wait(&position);
			j = WEXITSTATUS(position);
		}
	}
	if (i)
		free(command);
	return (j);
}

/**
 * main - Simple UNIX command interpreter.
 * @argc: The number of arguments supplied.
 * @argv: An array of pointers to the arguments.
 *
 * Return:Last executed command.
 */
int main(int argc, char *argv[])
{
	int i = 0, n;
	int *exeret = &n;
	char *prompt = "#our_shell$ ", *line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exeret = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);

       if (argc != 1)
	{
		i = proc_file_commands(argv[1], exeret);
		_freeenv();
		free_alias_list(aliases);
		return (*exeret);
	}


	if (!isatty(STDIN_FILENO))
	{
		while (i != END_OF_FILE && i != EXIT)
			i = handle_args(exeret);
		_freeenv();
		free_alias_list(aliases);
		return (*exeret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 10);
		i = handle_args(exeret);
		if (i == END_OF_FILE || i == EXIT)
		{
			if (i == END_OF_FILE)
				write(STDOUT_FILENO, line, 10);
			_freeenv();
			free_alias_list(aliases);
			exit(*exeret);
		}
	}

	_freeenv();
	free_alias_list(aliases);
	return (*exeret);
}
