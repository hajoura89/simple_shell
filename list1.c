#include "main.h"

/**
 * add_node - adds node to the start of a list
 * @head: pointer to head node
 * @str: node
 * @num: node index
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->number = num;
	if (str)
	{
		new_head->str = _strduplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->nextnode = *head;
	*head = new_head;
	return (new_head);
}
/**
 * node_start_with - node that  starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_start_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->nextnode;
	}
	return (NULL);
}
/**
 * get_node_index - the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->nextnode;
		i++;
	}
	return (-1);
}
/**
 * add_node_toend - adds node to the end of the list
 * @head: pointer to head node
 * @str: str field of node
 * @num: node index
 * Return: size of list
 */
list_t *add_node_toend(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->number = num;
	if (str)
	{
		new_node->str = _strduplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nextnode)
			node = node->nextnode;
		node->nextnode = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
 * delete_node_at - deletes node at given index
 * @head: pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_at(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->nextnode;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->nextnode = node->nextnode;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->nextnode;
	}
	return (0);
}
