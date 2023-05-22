#include "shell.h"


/**
 * alias_error-Error message for Alias.
 * @args:An array of arguments passed to the command.
 *
 * Return:Error.
 */
char *alias_error(char **args)
{
	char *er;
	int len;

	len = _strlen(name) + _strlen(args[0]) + 13;
	er = malloc(sizeof(char) * (len + 1));
	if (!er)
		return (NULL);

	_strcpy(er, "alias: ");
	_strcat(er, args[0]);
	_strcat(er, " Not Found\n");

	return (er);
}

/**
 * env_error-Error message for env.
 * @args:Arguments passed to the command.
 *
 * Return:Error.
 */
char *env_error(char **args)
{
	char *er, *hstr;
	int len;

	hstr = _itoa(hist);
	if (!hstr)
		return (NULL);

	args--;
	len = _strlen(name) + _strlen(hstr) + _strlen(args[0]) + 45;
	er = malloc(sizeof(char) * (len + 1));
	if (!er)
	{
		free(hstr);
		return (NULL);
	}

	_strcpy(er, name);
	_strcat(er, ": ");
	_strcat(er, hstr);
	_strcat(er, ": ");
	_strcat(er, args[0]);
	_strcat(er, ": Unable to Add OR Remove from environment\n");

	free(hstr);
	return (er);
}



/**
 * cd_error -Error message for cd.
 * @args:Arguments passed to the command.
 *
 * Return:Error.
 */
char *cd_error(char **args)
{
	char *er, *hstr;
	int len;

	hstr = _itoa(hist);
	if (!hstr)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(hstr) + _strlen(args[0]) + 24;
	er = malloc(sizeof(char) * (len + 1));
	if (!er)
	{
		free(hstr);
		return (NULL);
	}

	_strcpy(er, name);
	_strcat(er, ": ");
	_strcat(er, hstr);
	if (args[0][0] == '-')
		_strcat(er, ": cd: Illegal Choise ");
	else
		_strcat(er, ": cd: can't cd to ");
	_strcat(er, args[0]);
	_strcat(er, "\n");

	free(hstr);
	return (er);
}

/**
 * exit_error -Error message for exit.
 * @args: An array of arguments passed to the command.
 *
 * Return:Error.
 */
char *exit_error(char **args)
{
	char *er, *hstr;
	int len;

	hstr = _itoa(hist);
	if (!hstr)
		return (NULL);

	len = _strlen(name) + _strlen(hstr) + _strlen(args[0]) + 27;
	er = malloc(sizeof(char) * (len + 1));
	if (!er)
	{
		free(hstr);
		return (NULL);
	}

	_strcpy(er, name);
	_strcat(er, ": ");
	_strcat(er, hstr);
	_strcat(er, ": Exit, Illegal Number: ");
	_strcat(er, args[0]);
	_strcat(er, "\n");

	free(hstr);
	return (er);
}

/**
 * syntax_error -Error message for syntax.
 * @args:An array of arguments passed to the command.
 *
 * Return:Error.
 */
char *syntax_error(char **args)
{
	char *er, *hstr;
	int len;

	hstr = _itoa(hist);
	if (!hstr)
		return (NULL);

	len = _strlen(name) + _strlen(hstr) + _strlen(args[0]) + 33;
	er = malloc(sizeof(char) * (len + 1));
	if (!er)
	{
		free(hstr);
		return (NULL);
	}

	_strcpy(er, name);
	_strcat(er, ": ");
	_strcat(er, hstr);
	_strcat(er, ": Syntax Error: \"");
	_strcat(er, args[0]);
	_strcat(er, "\" Unexpected\n");

	free(hstr);
	return (er);
}
