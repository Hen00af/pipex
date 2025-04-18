//環境変数を出力
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define FAILED -1

// void	handle_parent(int i, int ac, char **av)
// {
// 	wait(NULL);
// 	if (i <= ac - 4)
// 		make_process(ac, av, i + 1);
// }

// void	handle_child(int pipe_fd[2], int i, int ac, char **av)
// {
// 	if (i > 0) // exept for first process
// 	{
// 		close(pipe_fd[1]);
// 		if (dup2(pipe_fd[0], STDIN_FILENO) == FAILED)
// 			error_dup2();
// 		close(pipe_fd[0]);
// 	}
// 	if (i < ac - 3) // exept for final process
// 	{
// 		close(pipe_fd[0]);
// 		if (dup2(pipe_fd[1], STDOUT_FILENO) == FAILED)
// 			error_dup2();
// 		close(pipe_fd[1]);
// 	}
// 	if (execve(av[i + 2], &av[i + 2], NULL) == FAILED)
// 		error_execve();
// }

// void	do_pipe(int pipe_fd[2])
// {
// 	if (pipe(pipe_fd) == FAILED)
// 		error_pipe();
// }
// static int	make_process(int ac, char **av, int i)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;

// 	if (i <= ac - 4)
// 		do_pipe(pipe_fd);
// 	pid = fork();
// 	if (pid == FAILED)
// 		error_fork();
// 	else if (pid == 0) // child process
// 		handle_child(pipe_fd, i, ac, av);
// 	else // parent process
// 		handle_parent(i, ac, av);
// 	return (0);
// }

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	extern char	**environ;
	int			i;
	int			fd;
	int			diff_status;

	// output1.txt にリダイレクト
	fd = open("output1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open output1.txt");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output1.txt");
		close(fd);
		return (1);
	}
	close(fd); // `dup2` した後に閉じても問題ない
	// 環境変数を output1.txt に出力
	printf("From env:\n");
	fflush(stdout); // バッファリングを防ぐ
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	fflush(stdout);
	// output2.txt にリダイレクト
	fd = open("output2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open output2.txt");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output2.txt");
		close(fd);
		return (1);
	}
	close(fd);
	// 環境変数を output2.txt に出力
	printf("From environ:\n");
	fflush(stdout);
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	fflush(stdout);
	return (0);
}
