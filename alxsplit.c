#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len -Find the delim index marking the end of the first token.
 * @str:String to be searched.
 * @delim:Delim char.
 *
 * Return:Length.
 */
int token_len(char *str, char *delim)
{
	int i = 0, lenght = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		lenght++;
		i++;
	}

	return (lenght);
}

/**
 * count_tokens - Counts the number of delim words contained.
 * @str: String to be searched.
 * @delim: The delim char.
 *
 * Return:Tokens.
 */
int count_tokens(char *str, char *delim)
{
	int i, tokens = 0, lenght = 0;

	for (i = 0; *(str + i); i++)
		lenght++;

	for (i = 0; i < lenght; i++)
	{
		if (*(str + i) != *delim)
		{
			tokens++;
			i += token_len(str + i, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok-Tokenizes a string.
 * @line:String.
 * @delim: The delim char to tokenize the string by.
 *
 * Return:Pointer.
 */
char **_strtok(char *line, char *delim)
{
	char **pnt;
	int i = 0, tokens, j, let, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	pnt = malloc(sizeof(char *) * (tokens + 2));
	if (!pnt)
		return (NULL);

	for (j = 0; j < tokens; j++)
	{
		while (line[i] == *delim)
			i++;

		let = token_len(line + i, delim);

		pnt[j] = malloc(sizeof(char) * (let + 1));
		if (!pnt[j])
		{
			for (i -= 1; i >= 0; i--)
				free(pnt[i]);
			free(pnt);
			return (NULL);
		}

		for (l = 0; l < let; l++)
		{
			ptr[j][l] = line[i];
			i++;
		}

		ptr[j][l] = '\0';
	}
	pnt[j] = NULL;
	pnt[j + 1] = NULL;

	return (pnt);
}
