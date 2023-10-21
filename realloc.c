#include "shell.h"


/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * find_cmd_path - Finds the full path of a command in the PATH string
 * @info: The info struct
 * @pathstr: The PATH string
 * @cmd: The command to find
 *
 * Return: Full path of the command if found or NULL
 */
char *find_cmd_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && check_starts_with(cmd, "./"))
	{
		if (check_cmd(info, cmd))
		{
			return (cmd);
		}
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (check_cmd(info, path))
			{
				return (path);
			}
			if (!pathstr[i])
			{
				break;
			}
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * find_cmd - Finds a command in PATH
 * @info: The parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!check_delim(info->arg[i], " \t\n"))
		{
			k++;
		}
	}
	if (!k)
		return;

	path = find_cmd_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && check_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
