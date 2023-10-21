#include "shell.h"

/**
 * check_chain_delim - test if the current character in the buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int check_chain_delim(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') 
	{
		buf[j] = 0; 
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


/**
 * rep_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			rep_str(&(info->argv[i]),
					_strdup(convert_num_to_str(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			rep_str(&(info->argv[i]),
					_strdup(convert_num_to_str(getpid(), 10, 0)));
			continue;
		}
		node = node_begins_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			rep_str(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		rep_str(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * rep_str - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
