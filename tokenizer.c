#include "shell.h"

/**
 * **strtow - Splits a string into words. Repeated delimiters are ignored.
 * @str: The input string
 * @d: The delimiter string
 *
 * Return: A pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!check_delim(str[i], d) && (check_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (check_delim(str[i], d))
			i++;

		k = 0;
		while (!check_delim(str[i + k], d) && str[i + k])
			k++;

		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}

	s[j] = NULL;
	return (s);
}

/**
 * rep_alias - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_begins_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}
