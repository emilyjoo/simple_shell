#include "shell.h"

int number_count(int num);

/**
 * _itoa - Converture int to string.
 * @num: int.
 *
 * Return: converter string.
 */
char *_itoa(int num)
{
	char *cs;
	int len = number_count(num);
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
 * costum_error- Custom Error message .
 * @args:An array of arguments.
 * @err:The Error value.
 *
 * Return:The Error value.
 */
int costum_error(char **args, int err)
{
	char *e;

	switch (err)
	{
	case -1:
		e = nv_error(args);
		break;
	case 1:
		e = alias_error(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			e = exit_error(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			e = syntax_error(args);
		else
			e = cd_error(args);
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

/**
 * num_len-Count the digital length of a num.
 * @num: The number to be count.
 *
 * Return:length.
 */
int number_count(int num)
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
