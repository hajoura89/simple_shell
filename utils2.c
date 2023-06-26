#include "main.h"

/**
 * print_error - prints an error message
 * @info: info structure
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(cmdinfo_t *info, char *estr)
{
	print_input_string(info->filename);
	print_input_string(": ");
	print_decimal(info->error_count, STDERR_FILENO);
	print_input_string(": ");
	print_input_string(info->argv[0]);
	print_input_string(": ");
	print_input_string(estr);
}

/**
 * remove_comments - replaces first instance of '#' with '\0'
 * @buf: the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

/**
 * is_interactive - returns true if shell is_interactive mode
 * @info: info structure
 * Return: 1 if is_interactive mode, 0 otherwise
 */
int is_interactive(cmdinfo_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @c: char to check
 * @delim: the delimeter
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: character to input
 *Return: 1 if alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
