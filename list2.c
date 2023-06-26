#include "main.h"

/**
 * list_length - determines length of ll
 * @h: pointer to first node
 * Return: size of list
 */
size_t list_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->nextnode;
		i++;
	}
	return (i);
}
/**
 * print_str_list - prints only the str element of a ll
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_str_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->nextnode;
		i++;
	}
	return (i);
}
/**
 * list_to_string - returns an array of strings
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_string(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->nextnode, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * print_list - prints all elements of a ll
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->nextnode;
		i++;
	}
	return (i);
}
/**
 * free_list - frees all nodes of a list
 * @head_ptr: pointer to head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->nextnode;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
