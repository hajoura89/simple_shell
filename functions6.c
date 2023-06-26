#include "main.h"
/**
 * chain_check - checks we should continue chaining based on last status
 * @info: cmd info structure
 * @buffer: the char buffer
 * @pos: address of current position in buffer
 * @index: starting position in buffer
 * @len: length of buffer
 * Return: Void
 */
void chain_check(cmdinfo_t *info, char *buffer, size_t *pos,
		size_t index, size_t len)
{
	size_t j = *pos;

	if (info->cmd_buffer_type == AND)
	{
		if (info->status)
		{
			buffer[index] = 0;
			j = len;
		}
	}
	if (info->cmd_buffer_type == OR)
	{
		if (!info->status)
		{
			buffer[index] = 0;
			j = len;
		}
	}
	*pos = j;
}
/**
 * is_chain_delimeter - test if current char in buffer is a chain delimeter
 * @info: cmd info structure
 * @buffer: the char buffer
 * @pos: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain_delimeter(cmdinfo_t *info, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buffer_type = OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buffer_type = AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		info->cmd_buffer_type = CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}
