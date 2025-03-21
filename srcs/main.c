#include "error_handling.c"
#include "make_process.c"
#include "pipex.h"

int	pipex(int ac, char **av)
{
	int	input_fd;
	int	output_fd;

	input_fd = open(av[1], O_RDONLY);
	if (input_fd == FAILED)
		error_input_fd(input_fd);
	output_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == FAILED)
		error_output_fd(input_fd, output_fd);
	if (dup2(input_fd, STDIN_FILENO) == FAILED)
		error_dup2();
	if (dup2(output_fd, STDOUT_FILENO) == FAILED)
		error_dup2();
	close(input_fd);
	close(output_fd);
	return (make_process(ac, av, 0));
}

int	main(int ac, char **av)
{
	check_args(ac, av); // 引数の検証
	pipex(ac, av);      // pipex関数の呼び出し
	return (0);
}
