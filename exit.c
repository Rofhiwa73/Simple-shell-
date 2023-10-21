#include "shell.h"

/**
 * _strncpy - Copy a string with a specified length
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The maximum number of characters to be copied
 * Return: The concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}




/**
 * print_decimal - Print a decimal (integer) number (base 10)
 * @number: The input number
 * @fd: The file descriptor to write to
 * Return: Number of characters printed
 */
int print_decimal(int number, int fd)
{
	int (*putCharFunction)(char) = _putchar;
	int i, count = 0;
	unsigned int absoluteValue, current;

	if (fd == STDERR_FILENO)
		putCharFunction = _error_putchar;
	if (number < 0)
	{
		absoluteValue = -number;
		putCharFunction('-');
		count++;
	}
	else
		absoluteValue = number;
	current = absoluteValue;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absoluteValue / i)
		{
			putCharFunction('0' + current / i);
			count++;
		}
		current %= i;
	}
	putCharFunction('0' + current);
	count++;

	return (count);
}

/**
 * convert_num_to_str - Convert a number to a string in a specified base
 * @num: The number
 * @base: The base
 * @flags: Argument flags
 * Return: A string representation of the number
 */

#include "shell.h"
#include <stdio.h>

char *convert_num_to_str(long int num, int base, int flags)
{
	char buffer[32]; 
	char *result = NULL;

	if (base < 2 || base > 36)
	{
		
		return (NULL);
	}

	if (flags & CONVERT_LOWERCASE)
	{
		if (base > 10)
		{
			snprintf(buffer, sizeof(buffer), "%lx", num);
		}
		else
		{
			snprintf(buffer, sizeof(buffer), "%ld", num);
		}
	}
	else
	{
		if (base > 10)
		{
			snprintf(buffer, sizeof(buffer), "%lX", num);
		}
		else
		{
			snprintf(buffer, sizeof(buffer), "%ld", num);
		}
	}

	if (buffer[0] != '\0')
	{
		result = _strdup(buffer);
	}

	return result;
}

/**
 * remove_comments - Replace the first instance of '#' with '\0' in a string
 * @buf: Address of the string to modify
 * Return: Always 0
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
