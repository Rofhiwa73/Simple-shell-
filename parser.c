#include "shell.h"

/**
 * check_cmd - Determines if a file is an executable command
 * @info: The info struct
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int check_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & __S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates characters from a string
 * @pathstr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to a new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];
		}
	}
	buf[k] = 0;
	return (buf);
}

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * sfree - frees a string of strings
 * @pp: string of strings
 */
void sfree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
