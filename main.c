#include "shell.h"

int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);

		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_err_puts(av[0]);
				_err_puts(": 0: Can't open ");
				_err_puts(av[1]);
				_err_putchar('\n');
				_err_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}

		info->readfd = fd;
	}

	add_to_env_list(info);

	read_hist(info);

	sloop(info, av);

	return (EXIT_SUCCESS);
}
