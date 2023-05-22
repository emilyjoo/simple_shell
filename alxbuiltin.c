#include "shell.h"


/**
 * get_builtin - Command with a corresponding
 *               get builtin function.
 * @command: The command to corresponding.
 *
 * Return: A function.
 */

int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t functions[] = {
		{ "exit", shell_exit },
		{ "env", env_cmd },
		{ "setenv", setenv_cmd },
		{ "unsetenv", unsetenv_cmd },
		{ "cd", cd_cmd },
		{ "alias", alias_cmd },
		{ "help", shell_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; functions[i].name; i++)
	{
		if (_strcmp(functions[i].name, command) == 0)
			break;
	}
	return (functions[i].f);
}

/**
 * shell_exit - Normal argument termination
 *                for the shellby exit.
 * @args: An array of arguments have the exit value.
 * @front: 2 pointer to the debus of args.
 *
 * Return:  -3.
 *         - 2.
 *         O/w .
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */

int shell_exit(char **args, char **front)
{
	int i = 0, leni = 10;
	unsigned int n = 0, x = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			leni++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= leni && args[0][i] >= '0' && args[0][i] <= '9')
				n = (n * 10) + (args[0][i] - '0');
			else
				return (costum_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (n > x - 1)
		return (costum_error(--args, 2));
	args -= 1;
	free_args(args, front);
	_freeenv();
	free_alias_list(aliases);
	exit(n);
}
/**
 * cd_cmd - Changes the current directory.
 * @args: An array of arguments.
 * @front: 2 pointer to the Debus of args.
 *
 * Return:  - 2.
 *          -1.
 *         Otherwise - 0.
 */
int cd_cmd(char **args, char **front)
{
	char **df, *nline = "\n";
	char *opwd = NULL, *pwd = NULL;
	struct stat d;

	opwd = getcwd(opwd, 0);
	if (!opwd)
		return (-1);
	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
			    args[0][1] == '\0')
			{
				if (get_env("OLDPWD") != NULL)
					(chdir(*get_env("OLDPWD") + 7));
			}
			else
			{
				free(opwd);
				return (costum_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &d) == 0 && S_ISDIR(d.st_mode)
			    && ((d.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(opwd);
				return (costum_error(args, 2));
			}
		}
	}
	else
	{
		if (get_env("HOME") != NULL)
			chdir(*(get_env("HOME")) + 5);
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);
	df = malloc(sizeof(char *) * 2);
	if (!df)
		return (-1);
	df[0] = "OLDPWD";
	df[1] = oldpwd;
	if (setenv_cmd(df, df) == -1)
		return (-1);
	df[0] = "PWD";
	df[1] = pwd;
	if (setenv_cmd(df, df) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, nline, 1);
	}
	free(opwd);
	free(pwd);
	free(df);
	return (0);
}
/**
 * shell_help - Displays information commands.
 * @args: An array of arguments.
 * @front: A pointer to the debus of args.
 *
 * Return:  -1.
 *         Otherwise - 0.
 */
int shell_help(char **args, char **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));
	return (0);
}
