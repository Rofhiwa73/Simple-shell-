#include "shell.h"

/**
 * _env - Print the current environment variables
 * @info: Structure containing potential arguments for a
 * constant function prototype
 * Return: Always 0
 */
int _env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Get the value of an environment variable
 * @info: Structure containing potential arguments
 * @envName: Environment variable name
 * Return: The value of the environment variable
 */
char *_getenv(info_t *info, const char *envName)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = check_starts_with(node->str, envName);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}


/**
 * _write_to_fd - Writes the character c to the given file descriptor.
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * This function writes the character @c to the specified file descriptor @fd.
 *
 * Return: On success, it returns 1. On error, -1 is returned
 * and errno is set appropriately.
 */
int _write_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * writes_str_to_fd - Writes an input string to the specified file descriptor.
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * This function writes the string @str to the specified file descriptor @fd.
 *
 * Return: The number of characters written to the file descriptor.
 */

int writes_str_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _write_to_fd(*str++, fd);
	}
	return (i);
}
