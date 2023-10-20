#include "shell.h"

/**
 * get_env - Get a copy of the environment strings
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: The environment string array copy
 */
char **get_env(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * clear_info - Initialize the info_t struct
 * @info: The address of the info_t struct to initialize
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * init_info - Initialize the info_t struct and process command line arguments
 * @info: The address of the info_t struct to initialize
 * @av: Argument vector
 */
void init_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rep_alias(info);
		rep_vars(info);
	}
}
