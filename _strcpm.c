#include "shell.h"
/**
 * _strspn -The len of a prefix sub.
 * @s:searched string.
 * @accept:measured prefix.
 *
 * Return:Number.
 */
int _strspn(char *s, char *accept)
{
	int b = 0;
	int i;

	while (*s)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*s == accept[i])
			{
				b++;
				break;
			}
		}
		s++;
	}
	return (b);
}

/**
 * _strncmp -2 Sting compared.
 * @s1: string Pointer .
 * @s2: string Pointer .
 * @n:Compare first n bytes of the strings.
 *
 * Return: < than 0 if s1 is < than s2.
 *         0 if s1 and s2 =.
 *         > than 0 if s1 is > than s2.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t z;

	for (z = 0; s1[z] && s2[z] && i < n; z++)
	{
		if (s1[z] > s2[z])
			return (s1[z] - s2[z]);
		else if (s1[z] < s2[z])
			return (s1[z] - s2[z]);
	}
	if (z == n)
		return (0);
	else
		return (-15);
}

/**
 * _strchr -string to localate.
 * @s: searched string.
 * @c: located character.
 *
 * Return: If c is found :a pointer to the first occurence.
 *         If c is not found :NULL.
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == c)
			return (s + i);
	}

	return (NULL);
}

/**
 * _strcmp -2 sting to compare.
 * @s1:compared first string.
 * @s2:compared second string.
 *
 * Return: Positive byte difference if s1 greater s2
 *         0 if s1 equal s2
 *         Negative byte difference if s1 less s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}
