#include "shell.h"

/**
 * get_args - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t r;
	char *prompt = "$ ";

	if (line)
		free(line);

	r = get_line(&line, &n, STDIN_FILENO);
	if (r == -1)
		return (NULL);
	if (r == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[r - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, r);

	return (line);
}

/**
 * call_args - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 * Return: The return value of the last executed command.
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int ret, idx;

	if (!args[0])
		return (*exe_ret);
	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], "||", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		}
		else if (_strncmp(args[idx], "&&", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++idx];
				idx = 0;
			}
			else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}
/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *   Otherwise - 0.
 */
int check_args(char **args)
{
	size_t i;
	char *curr, *_next;

	for (i = 0; args[i]; i++)
	{
		curr = args[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
				return (costum_error(&args[i], 2));
			_next = args[i + 1];
			if (_next && (_next[0] == ';' || _next[0] == '&' || _next[0] == '|'))
				return (costum_error(&args[i + 1], 2));
		}
	}
	return (0);
}
/**
 * run_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = str_tok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}
