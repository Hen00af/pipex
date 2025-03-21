
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define FAILED -1

void	handle_parent(int i, int ac, char **av)
{
	wait(NULL);
	if (i <= ac - 4)
		make_process(ac, av, i + 1);
}

void	handle_child(int pipe_fd[2], int i, int ac, char **av)
{
	if (i > 0) // exept for first process
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == FAILED)
			error_dup2();
		close(pipe_fd[0]);
	}
	if (i < ac - 3) // exept for final process
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == FAILED)
			error_dup2();
		close(pipe_fd[1]);
	}
	if (execve(av[i + 2], &av[i + 2], NULL) == FAILED)
		error_execve();
}

void	do_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == FAILED)
		error_pipe();
}
static int	make_process(int ac, char **av, int i)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (i <= ac - 4)
		do_pipe(pipe_fd);
	pid = fork();
	if (pid == FAILED)
		error_fork();
	else if (pid == 0) // child process
		handle_child(pipe_fd, i, ac, av);
	else // parent process
		handle_parent(i, ac, av);
	return (0);
}
int	main(int ac, char **av)
{
	int i = 0;
	make_process(ac, av, i);
	return (0);
}