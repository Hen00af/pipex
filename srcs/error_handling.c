#include "pipex.h"

#define THIS_IS_NOT_FILE -1

int	dir_check(char *file)
{
	int	fd;

	fd = open(file, O_RDWR);
	close(fd);
	if (fd == -1)
		return (THIS_IS_NOT_FILE);
	return (0);
}

int	check_file(char *infile, char *outfile)
{
	int	infile_perm;
	int	outfile_perm;
	int	file_exist;

	infile_perm = access(infile, R_OK);
	outfile_perm = access(outfile, W_OK);
	if (outfile_perm)
	{
		file_exist = access(outfile, F_OK);
		if (file_exist)
			outfile_perm = 0;
	}
	if (!outfile_perm && !file_exist)
		outfile_perm = dir_check(outfile);
	if (!infile_perm)
		infile_perm = dir_check(infile);
	if (infile_perm || outfile_perm)
		return (1);
	return (0);
}
static void	check_args(int ac, char **av)
{
	if (ac < 5)
	{
		errno = EINVAL;
		perror("Error: ");
		exit(1);
	}
	if (check_file(av[1], av[ac - 1]) != 0)
	{
		perror("Error: Can't open file");
		exit(1);
	}
}
void	error_pipe(void)
{
	perror("pipe failed");
	exit(1);
}

void	error_fork(void)
{
	perror("fork failed");
	exit(1);
}

void	error_input_fd(int input_fd)
{
	perror("Error opening input file");
	close(input_fd);
	exit(1);
}

void	error_output_fd(int input_fd, int output_fd)
{
	perror("Error opening output file");
	close(input_fd);
	close(output_fd);
	exit(1);
}

void	error_dup2(void)
{
	perror("dup2 failed");
	exit(1);
}

void	error_execve(void)
{
	perror("execve failed");
	exit(1);
}
