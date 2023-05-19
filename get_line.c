#include "shell.h"

/**
 * re_alloc - reallocates a memory block using malloc and free.
 * @ptr: pointer to the mem previously allocated
 * @past_size: size in bytes for allocated space for ptr
 * @current_size: size in bytes for new mem block
 * Return: NULL - if current_size == past_size - ptr, if current_size == 0 and
 *	ptr is not NULL.
 *	otherwise - a pointer to the reallocated mem block
 */
void re_alloc(void *ptr, unsigned int past_size, unsigned int current_size)
{
	char *ptr_cp, *add;
	unsigned int idx;
	void *mem;

	if (current_size == past_size)
		return (ptr);
	if (ptr == NULL)
	{
		mem = malloc(current_size);
		if (mem == NULL)
			return (NULL);
		return (mem);
	}
	if (current_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	ptr_cp = ptr;
	mem = malloc(sizeof(*ptr_cp) * current_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}
	add = mem;
	for (idx = 0; idx < past_size && idx < current_size; idx++)
		add[idx] = *ptr_cp++;

	free(ptr);
	return (mem);
}
/**
 * assign_lineptr - reassigns the lineptr var for get_line function
 * @lineptr: a buffer to store an input string.
 * @n: size of lineptr
 * @buff: the string to assign to lineptr
 * @n_str: the size of the buffer
 */
void assign_lineptr(char **lineptr, size_t *n, char *buff, size_t n_str)
{
	if (*lineptr == NULL)
	{
		if (n_str > 120)
			*n = n_str;
		else
			*n = 120;
		*lineptr = buff;
	}
	else if (*n < n_str)
	{
		if (n_str > 120)
			*n = n_str;
		else
			*n = 120;
		*lineptr = buff;
	}
	else
	{
		_strcpy(*lineptr, buff);
		free(buff);
	}
}
/**
 * get_line - reads input from a stream
 * @lineptr: a buffre to store the input
 * @n: the size of lineptr
 * @stream: stream to read from
 * Return: the number of bytes read
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char d = 'x', *buff;
	int rd;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buff = malloc(sizeof(char) * 120);
	if (!buff)
		return (-1);
	while (d != '\n')
	{
		rd = read(STDIN_FILENO, &c, 1);
		if (rd == -1 || (rd == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (rd == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buff = re_alloc(buff, input, input + 1);

		buff[input] = d;
		input++;
	}
	buff[input] = '\0';
	assign_lineptr(lineptr, n, buff, input);

	ret = input;
	if (rd != 0)
		input = 0;
	return (ret);
}
