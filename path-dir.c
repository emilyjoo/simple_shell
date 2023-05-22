#include "shell.h"

char *fillpath(char *path);
list_t *_dirpath(char *path);

/**
 * fillpath - Copie Path
 * @path: The colon Separated list of dir.
 *
 * Return: Path copy.
 */
char *fillpath(char *path)
{
	int i, len = 0;
	char *cp_path, *pwd;

	pwd = *(get_env("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	cp_path = malloc(sizeof(char) * (len + 1));
	if (!cp_path)
		return (NULL);
	cp_path[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(cp_path, pwd);
				_strcat(cp_path, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(cp_path, ":");
				_strcat(cp_path, pwd);
			}
			else
				_strcat(cp_path, ":");
		}
		else
		{
			_strncat(cp_path, &path[i], 1);
		}
	}
	return (cp_path);
}

/**
 * _dirpath - Tokenizes a colon Separated list.
 * @path:Colon Separated list of dir.
 *
 * Return: head.
 */
list_t *dirpath(char *path)
{
	int i;
	char **d, *cp_path;
	list_t *hd = NULL;

	cp_path = fillpath(path);
	if (!cp_path)
		return (NULL);
	d = str_tok(cp_path, ":");
	free(cp_path);
	if (!d)
		return (NULL);

	for (i = 0; d[i]; i++)
	{
		if (add_node_end(&hd, d[i]) == NULL)
		{
			free_list(hd);
			free(d);
			return (NULL);
		}
	}

	free(d);

	return (hd);
}

/**
 * get_path - Find the PATH.
 * @command: The command to find.
 *
 * Return: NULL.
 *         Full pathname.
 */

char *get_path(char *command)
{
	char **path, *tp;
	list_t *d, *h;
	struct stat sts;

	path = get_env("PATH");
	if (!path || !(*path))
		return (NULL);

	d = _dirpath(*path + 5);
	h = d;

	while (d)
	{
		tp = malloc(_strlen(d->dir) + _strlen(command) + 2);
		if (!tp)
			return (NULL);

		_strcpy(tp, d->dir);
		_strcat(tp, "/");
		_strcat(tp, command);

		if (stat(tp, &sts) == 0)
		{
			free_list(h);
			return (tp);
		}

		d = d->next;
		free(tp);
	}

	free_list(h);

	return (NULL);
}
