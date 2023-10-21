#include "shell.h"

/**
 * sloop - Main shell loop
 * @info: The parameter & return info struct
 * @av: The argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int sloop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (is_interactive(info))
			_puts("$ ");
		_error_putchar(BUF_FLUSH);
		r = _get_input(info);
		if (r != -1)
		{
			init_info(info, av);
			builtin_ret = find_built_in(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_hist(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_built_in - Finds a built-in command
 * @info: The parameter & return info struct
 *
 * Return: -1 if built-in not found,
 *         0 if built-in executed successfully,
 *         1 if built-in found but not successful,
 *         2 if built-in signals exit()
 */
int find_built_in(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _alias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * fork_cmd - Forks an exec thread to run a command
 * @info: The parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
