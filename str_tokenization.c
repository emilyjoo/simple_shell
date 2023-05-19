#include "shell.h"

/**
 * token_size -identifies the delimeter position, marks the end
 *	of the first token within an input string
 * @str: string to be searched
 * @delim: the delimeter character
 * Return: the delimeter index
 */
int token_size(char *str, char *delim)
{
	int idx = 0, size = 0;

	while (*(str + idx) && *(str + idx) != *delim)
	{
		size++;
		idx++;
	}
	return (size);
}
/**
 * record_tokens - counts and records the number of delimited words in a string
 * @str: the string to be searched
 * @delim: delim character
 * Return: the number of words contained within str
 */
int record_tokens(char *str, char *delim)
{
	int idx, tokens = 0, size = 0;

	for (idx = 0; *(str + idx); idx++)
		size++;
	for (idx = 0; idx < size; idx++)
	{
		if (*(str + idx) != *delim)
		{
			tokens++;
			idx += token_size(str + idx, delim);
		}
	}
	return (tokens);
}
/**
 * str_tok - tokenizes a string
 * @lineptr: the string
 * @delim: delimeter character to tokenize the str with
 * Return: pointer to an array of tokenized words
 */
char **str_tok(char *lineptr, char *delim)
{
	char **ptr;
	int idx = 0, tokens, t, letters, l;

	tokens = record_tokens(lineptr, delim);
	if (tokens == 0)
		return (NULL);
	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);
	for (t = 0; t < tokens; t++)
	{
		while (lineptr[idx] == *delim)
			idx++;
		letters = token_size(lineptr + idx, delim);
		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}
		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = lineptr[idx];
			idx++;
		}
		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
