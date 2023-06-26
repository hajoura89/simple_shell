#include "main.h"

/**
 * start_with - find substring at start
 * @str: string to search
 * @sub: substring to find
 * Return: address of next char or NULL
 */
char *start_with(const char *str, const char *sub)
{
	while (*sub)
		if (*sub++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 **_strncpy - copies a string
 *@dest: destination string
 *@src: source string
 *@n: numbers of characters to be copied
 *Return: the result string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: 1st string
 *@src: 2nd string
 *@n: nbr of bytes to be used
 *Return: the result string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string
 *@c: the character to look for
 *Return: result character
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

