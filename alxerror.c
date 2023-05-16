#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len-Count the digital length of a num.
 * @num: The number to be count.
 *
 * Return:length.
 */
int num_len(int num)
{
	unsigned int numone;
	int length = 1;

	if (num < 0)
	{
		length++;
		numone = num * -1;
	}
	else
	{
		numone = num;
	}
	while (numone > 9)
	{
		length++;
		numone /= 10;
	}

	return (length);
}

/**
 * _itoa - Converture int to string.
 * @num: int.
 *
 * Return: converter string.
 */
char *_itoa(int num)
{
	char *cs;
	int len = num_len(num);
	unsigned int numone;

	cs = malloc(sizeof(char) * (len + 1));
	if (!cs)
		return (NULL);

	cs[len] = '\0';

	if (num < 0)
	{
		numone = num * -1;
		cs[0] = '-';
	}
	else
	{
		numone = num;
	}

	len--;
	do {
		cs[len] = (numone % 10) + '0';
		numone /= 10;
		len--;
	} while (numone > 0);

	return (cs);
}


/**
 * create_error - Custom Error message .
 * @args:An array of arguments.
 * @err:The Error value.
 *
 * Return:The Error value.
 */
int create_error(char **args, int err)
{
	char *e;

	switch (err)
	{
	case -1:
		e = error_env(args);
		break;
	case 1:
		e = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			e = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			e = error_2_syntax(args);
		else
			e = error_2_cd(args);
		break;
	case 126:
		e = error_126(args);
		break;
	case 127:
		e = error_127(args);
		break;
	}
	write(STDERR_FILENO, e, _strlen(e));

	if (e)
		free(e);
	return (err);

}
