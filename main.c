#include "main.h"

/**
 * main - entry point
 * @ac: count
 * @av: vector
 * Return: 0 or 1
 */
int main(int ac, char **av)
{
	cmdinfo_t info[] = {
		{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL,
		NULL, NULL, 0, 0, NULL, 0, 0, 0}
	};
	int fd = 2;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_input_string(av[0]);
				print_input_string(": 0: Can not open ");
				print_input_string(av[1]);
				write_char('\n');
				write_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_fd = fd;
	}
	populate_envlist(info);
	myshell(info, av);
	return (EXIT_SUCCESS);
}
