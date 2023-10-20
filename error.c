#include "shell.h"

/**
 * _err_puts - Prints an input string to stderr.
 * @str: The string to be printed
 *
 * This function prints the string @str to the standard error stream.
 */
void _err_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_err_putchar(str[i]);
		i++;
	}
}



/* 8888888888888888888888888888888888888888888 */

/**
 * _mysetenv - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_err_puts("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Used to maintain function prototype
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_err_puts("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		remove_env(info, info->argv[i]);

	return (0);
}

/**
 * add_to_env_list - Populate the environment linked list
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int add_to_env_list(info_t *info)
{
	list_t *envList = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_add_node_end(&envList, environ[i], 0);
	info->env = envList;
	return (0);
}
