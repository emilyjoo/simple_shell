#include "shell.h"

/**
 * free_env-Frees the the env cp.
 */
void _freeenv(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * _getenv - Gets env from path.
 * @var: name of variable envirenment.
 *
 * Return: NULL.
 *        pointer env.
 */
char **get_env(const char *var)
{
	int i, lenght;

	lenght = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(var, environ[i], lenght) == 0)
			return (&environ[i]);
	}

	return (NULL);
}

/**
 * _copyenv -Copy of the environment.
 *
 * Return: NULL.
 *         New environement.
 */

char **copy_env(void)
{
	char **cp_env;
	size_t s;
	int i;

	for (s = 0; environ[s]; s++)
		;

	cp_env = malloc(sizeof(char *) * (s + 1));
	if (!cp_env)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		cp_env[i] = malloc(_strlen(environ[i]) + 1);

		if (!cp_env[i])
		{
			for (i--; i >= 0; i--)
				free(cp_env[i]);
			free(cp_env);
			return (NULL);
		}
		_strcpy(cp_env[i], environ[i]);
	}
	cp_env[i] = NULL;

	return (cp_env);
}
