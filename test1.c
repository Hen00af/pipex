//子プロセスが孫プロセスを作成する場合のパターン
#include "pipex.h"

void	check_input(int ac, char **av)
{
	if (ac < 5)
	{
		perror("Error: Incorrect number of arguments\n");
		exit(1);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	pid_t pid1, pid2;
	printf("親  PID: %d, PPID: %d\n", getpid(), getppid());
	pid1 = fork(); // 1回目の fork
	if (pid1 == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pid1 == 0)
	{
		printf("子  PID: %d, PPID: %d\n", getpid(), getppid());
		pid2 = fork(); // 2回目の fork
		wait(NULL);
		if (pid2 == -1)
		{
			perror("fork failed");
			exit(1);
		}
		else if (pid2 == 0)
		{
			printf("子  PID: %d, PPID: %d\n", getpid(), getppid());
		}
	}
	else
		wait(NULL);
	return (0);
}
