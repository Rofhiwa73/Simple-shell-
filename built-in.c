#include "shell.h"

/**
 * _myexit - Exit the shell
 * @info: Structure containing arguments. for maintain the function prototype
 * Return: Return exit with a given status (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitCode;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitCode = _erratoi(info->argv[1]);
		if (exitCode == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_err_puts(info->argv[1]);
			_err_putchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - Change the current directory
 * @info: Structure containing potential arguments. Used for the prototype
 * Return: Always return 0
 */
int _cd(info_t *info)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		newDir = _getenv(info, "HOME=");
		if (!newDir)
			chdirResult = /* TODO: what should this be? */
				chdir((newDir = _getenv(info, "PWD=")) ? newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdirResult = /* TODO: what should this be? */
			chdir((newDir = _getenv(info, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = chdir(info->argv[1]);
	if (chdirResult == -1)
	{
		print_error(info, "can't cd to ");
		_err_puts(info->argv[1]);
		_err_putchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * check_delim - Checks if a character is a delimiter
 * @c: Character to check
 * @delim: Delimiter string
 * Return: 1 if true, 0 if false
 */
int check_delim(char c, char *delim)
{
	while (*delim)

		if (*delim++ == c)
			return (1);
	return (0);
}
