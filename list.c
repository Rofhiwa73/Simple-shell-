#include "shell.h"

/**
 * add_to_node - Adds a node to the start of the list
 * @head: Address of pointer to head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: The newly added node
 */
list_t *add_to_node(list_t **head, const char *str, int num)
{
	list_t *newNode;

	if (!head)
		return (NULL);

	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;

	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}

	newNode->next = *head;
	*head = newNode;
	return newNode;
}

/**
 * _add_node_end - Adds a node to the end of the list
 * @head: Address of pointer to head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: The newly added node
 */
list_t *_add_node_end(list_t **head, const char *str, int num)
{
	list_t *newNode, *currentNode;

	if (!head)
		return (NULL);

	currentNode = *head;

	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;

	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}

	if (currentNode)
	{
		while (currentNode->next)
			currentNode = currentNode->next;
		currentNode->next = newNode;
	}
	else
	{
		*head = newNode;
	}

	return newNode;
}

/**
 * print_list_str - Prints only the str element of a list_t linked list
 * @head: Pointer to the first node
 *
 * Return: The number of nodes in the list
 */
size_t print_list_str(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}

	return count;
}

/**
 * del_node_at_index - Deletes a node at the given index
 * @head: Address of pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_node_at_index(list_t **head, unsigned int index)
{
	list_t *currentNode, *prevNode;
	unsigned int currentIndex = 0;

	if (!head || !*head)
		return 0;

	if (!index)
	{
		currentNode = *head;
		*head = (*head)->next;
		free(currentNode->str);
		free(currentNode);
		return 1;
	}

	currentNode = *head;

	while (currentNode)
	{
		if (currentIndex == index)
		{
			prevNode->next = currentNode->next;
			free(currentNode->str);
			free(currentNode);
			return 1;
		}

		currentIndex++;
		prevNode = currentNode;
		currentNode = currentNode->next;
	}

	return 0;
}

/**
 * free_list - Frees all nodes of a list
 * @headPtr: Address of pointer to head node
 *
 * Return: Void
 */
void free_list(list_t **headPtr)
{
	list_t *currentNode, *nextNode, *head;

	if (!headPtr || !*headPtr)
		return;

	head = *headPtr;
	currentNode = head;

	while (currentNode)
	{
		nextNode = currentNode->next;
		free(currentNode->str);
		free(currentNode);
		currentNode = nextNode;
	}

	*headPtr = NULL;
}
