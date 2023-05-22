#include "shell.h"


/**
 * _strcpy -Copy the string pointed to by src.
 * @dest: copy string pointer to the destination.
 * @src: the source string pointer to the src.
 *
 * Return:dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t t;

	for (t = 0; src[t] != '\0'; t++)
		dest[t] = src[t];
	dest[t] = '\0';
	return (dest);
}



/**
 * _strncat-Concant 2 strings.
 * @dest:string pointer to destination.
 * @src:string pointer to source.
 *
 * Return:dest.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dn = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dn + i] = src[i];
	dest[dn + i] = '\0';

	return (dest);
}

/**
 * _strcat - Concant 2 strings.
 * @dest:string pointer to destination .
 * @src:string pointer to source .
 *
 * Return:dest.
 */

char *_strcat(char *dest, const char *src)
{
	char *destT;
	const char *srcT;

	destT = dest;
	srcT =  src;

	while (*destT != '\0')
		destT++;

	while (*srcT != '\0')
		*destT++ = *srcT++;
	*destT = '\0';
	return (dest);
}

/**
 * _strlen -The len string.
 * @s:characters string pointer.
 *
 * Return:the len string.
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len]; len++)
		;
	return (len);
}
