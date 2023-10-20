#include "shell.h"

/**
 * _history - Display the command history with line numbers starting at 0
 * @info: Structure containing potential arguments for a const func prototype
 * Return: Always 0
 */
int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Remove an alias from the list
 * @info: Parameter structure
 * @aliasStr: String alias
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *aliasStr)
{
	char *equalSign, savedChar;
	int result;

	equalSign = _strchr(aliasStr, '=');
	if (!equalSign)
		return (1);
	savedChar = *equalSign;
	*equalSign = 0;
	result = del_node_at_index(&(info->alias),
		get_index_of_node(info->alias, node_begins_with(info->alias, aliasStr, -1)));
	*equalSign = savedChar;
	return (result);
}

/**
 * set_alias - Set an alias to a string
 * @info: Parameter structure
 * @aliasStr: String alias
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *aliasStr)
{
	char *equalSign;

	equalSign = _strchr(aliasStr, '=');
	if (!equalSign)
		return (1);
	if (!*++equalSign)
		return (unset_alias(info, aliasStr));

	unset_alias(info, aliasStr);
	return (_add_node_end(&(info->alias), aliasStr, 0) == NULL);
}

/**
 * print_alias - Print an alias string
 * @node: Alias node
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *equalSign = NULL, *begin = NULL;

	if (node)
	{
		equalSign = _strchr(node->str, '=');
		for (begin = node->str; begin <= equalSign; begin++)
			_putchar(*begin);
		_putchar('\'');
		_puts(equalSign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - Mimics the alias built-in (man alias)
 * @info: Structure containing arguments to maintain the function prototype
 * Return: Always 0
 */
int _alias(info_t *info)
{
	int i = 0;
	char *equalSign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equalSign = _strchr(info->argv[i], '=');
		if (equalSign)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_begins_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
