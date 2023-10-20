#include "shell.h"

/**
 * _erratoi - Convert a string to an integer
 * @s: The string to be converted
 *
 * Return: 0 if no numbers in the string
 * the converted number otherwise, -1 on error
 */

int _erratoi(char *s)
{
	int index = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* Skip the plus sign, if present */
	for (index = 0; s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			result *= 10;
			result += (s[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}


/**
 * print_error - Print an error message
 * @info: Structure containing parameters and return information
 * @errorType: String containing a specified error type
 *
 * Return: Nothing
 */
void print_error(info_t *info, char *errorType)
{
	_err_puts(info->fname);
	_err_puts(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_err_puts(": ");
	_err_puts(info->argv[0]);
	_err_puts(": ");
	_err_puts(errorType);
}

/**
 * _strncat - Concatenate two strings with a specified length
 * @dest: The first string
 * @src: The second string
 * @n: The maximum number of bytes to be used
 *
 * Return: The concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - Locate a character in a string
 * @s: The string to be searched
 * @c: The character to look for
 *
 * Return: A pointer to the found character in the memory area s
 */
char *_strchr(char *v, char c)
{
	do {
		if (*v == c)
		{
			return (v);
		}
	} while (*v++ != '\0');

	return (NULL);
}
