#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("$ ");
		line = _getline();
		args = split_line(line);
		status = execute(args);

		free(line);
		free(args);
	}

		while (status);
		{
			return (0);
		}
		return (0);
}
/**
 * get_line -  Reads a line of input from the user.
 *
 * Return: The input line.
 */
char *_getline(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read = getline (&line, &len, stdin);
	if (read == -1)
	{
		perror("rofhiwa");
		exit(EXIT_FAILURE);
	}
	return (line);
}
