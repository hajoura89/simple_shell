#include "main.h"
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
