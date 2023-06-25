#include "main.h"

/**
 * print_input_string - prints a string to the stderr output.
 * @str: the string to be printed
 * Return: Nothing
 */
void print_input_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		write_char(str[i]);
		i++;
	}
}

/**
 * write_char - writes character to stderr
 * @c: character to print
 * Return: On success 1.
 * On error, -1 is returned
 */
int write_char(char c)
{
	static int i;
	static char buf[BUFFER_WRITE];

	if (c == BUF_FLUSH || i >= BUFFER_WRITE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * write_to_fd - writes the character to file descriptor
 * @c:character to print
 * @fd: file descriptor to write to
 * Return: On success 1.
 * On error, -1 is returned
 */
int write_to_fd(char c, int fd)
{
	static int i;
	static char buf[BUFFER_WRITE];

	if (c == BUF_FLUSH || i >= BUFFER_WRITE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *print_to_fd - prints an input string
 * @str: string to be printed
 * @fd: file descriptor to write to
 * Return: the number of chars put
 */
int print_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += write_to_fd(*str++, fd);
	}
	return (i);
}

