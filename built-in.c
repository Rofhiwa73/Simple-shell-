#include "shell.h"

/**
 * _myexit - Exit the shell
 * @info: Structure containing arguments. for maintain the function prototype
 * Return: Return exit with a given status (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitchecks;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitchecks = _erratoi(info->argv[1]);
		if (exitchecks == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_error_puts(info->argv[1]);
			_error_putchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Change the current directory
 * @info: Structure containing potential arguments. Used for the prototype
 * Return: Always return 0
 */
int _mycd(info_t *info)
{
	char *cdir, *ndir, buffer[1024];
	int chdir_res;

	cdir = getcwd(buffer, 1024);
	if (!cdir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		ndir = _getenv(info, "HOME=");
		if (!ndir)
			chdir_res = /* TODO: what should this be? */
				chdir((ndir = _getenv(info, "PWD=")) ? ndir : "/");
		else
			chdir_res = chdir(ndir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(cdir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_res = /* TODO: what should this be? */
			chdir((ndir = _getenv(info, "OLDPWD=")) ? ndir : "/");
	}
	else
		chdir_res = chdir(info->argv[1]);
	if (chdir_res == -1)
	{
		print_error(info, "can't cd to ");
		_error_puts(info->argv[1]);
		_error_putchar('\n');
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
