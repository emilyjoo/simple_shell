#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 -Error message for execute denied.
 * @args:An array of arguments passed to the command.
 *
 * Return:Error.
 */
char *error_126(char **args)
{
	char *er, *hstr;
	int len;

	hstr = _itoa(hist);
	if (!hstr)
		return (NULL);

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
	_strcat(er, ": ");
	_strcat(er, args[0]);
	_strcat(er, ": Command invoked cannot execute.\n");

	free(hstr);
	return (er);
}

/**
 * error_127 -Error message for command not found.
 * @args: An array of arguments passed to the command.
 *
 * Return: Error.
 */
char *error_127(char **args)
{
	char *er, *hstr;
	int len;

	hstr = _itoa(hist);
	if (!hstr)
		return (NULL);

	len = _strlen(name) + _strlen(hstr) + _strlen(args[0]) + 16;
	er = malloc(sizeof(char) * (len + 1));
	if (!er)
	{
		free(hstr);
		return (NULL);
	}

	_strcpy(er, name);
	_strcat(er, ": ");
	_strcat(er, hist_str);
	_strcat(er, ": ");
	_strcat(er, args[0]);
	_strcat(er, ": Command not found.\n");

	free(hstr);
	return (er);
}
