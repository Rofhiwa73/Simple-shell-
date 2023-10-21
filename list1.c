#include "shell.h"

/**
 * len_of_list - Determines the length of a linked list
 * @head: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t len_of_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * list_to_str - Converts a linked list to an array of strings from list->str
 * @head: Pointer to the first node
 *
 * Return: Array of strings
 */
char **list_to_str(list_t *head)
{
	list_t *node = head;
	size_t numNodes = len_of_list(head);
	size_t i;
	char **strArray;
	char *str;

	if (!head || !numNodes)
		return (NULL);

	strArray = malloc(sizeof(char *) * (numNodes + 1));

	if (!strArray)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);

		if (!str)
		{
			size_t j;

			for ( j = 0; j < i; j++)
				free(strArray[j]);
			free(strArray);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strArray[i] = str;
	}

	strArray[i] = NULL;
	return (strArray);
}

/**
 * print_list - Prints all elements of a list_t linked list
 * @head: Pointer to the first node
 *
 * Return: Size of the list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_num_to_str(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * node_begins_with - Returns a node whose string starts with the given prefix
 * @head: Pointer to list head
 * @prefix: String to match
 * @c: The next character after the prefix to match, or -1 for any
 *
 * Return: The matching node or NULL
 */
list_t *node_begins_with(list_t *head, char *prefix, char c)
{
	char *ptr = NULL;

	while (head)
	{
		ptr = check_starts_with(head->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (head);
		head = head->next;
	}

	return (NULL);
}

/**
 * get_index_of_node - Gets the index of a node in the list
 * @head: Pointer to list head
 * @targetNode: Pointer to the node
 *
 * Return: The index of the node or -1 if not found
 */
ssize_t get_index_of_node(list_t *head, list_t *targetNode)
{
	size_t index = 0;

	while (head)
	{
		if (head == targetNode)
			return (index);
		head = head->next;
		index++;
	}

	return (-1);
}

/**
 * _err_putchar - Writes the character c to the standard error stream.
 * @c: The character to print
 *
 * This function writes the character @c to the standard error stream (stderr).
 *
 * Return: On success, it returns 1. On error, -1 is returned
 * and errno is set appropriately.
 */
int _error_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
