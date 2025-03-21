// pipeを使用するにおける、かんたんな例
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int pipefd[2]; //[1]データ書き込み  [0]データ読み込み
	pid_t pid1, pid2;
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		return (1);
	}
	/////////////////////////////////////////////////////////////////
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork failed");
		return (1);
	}
	dup2(pipefd[0], STDIN_FILENO);
	if (pid1 == 0) // child
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		// close(pipefd[1]);
		// dup2(pipefd[0], STDIN_FILENO);
		// close(pipefd[0]);

		execlp("ls", "ls", "-l", NULL);
		perror("exec failed");
		exit(1);
	}
	///////////////////////////////////////////////////////////////////
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid2 == 0)
	{
		close(pipefd[1]);               // 書き込み側は使わないので閉じる
		dup2(pipefd[0], STDIN_FILENO);  // 標準入力をパイプの読み取り側にリダイレクト
		close(pipefd[0]);               // パイプを閉じる (不要になったため)
		execlp("wc", "wc", "-l", NULL); // wc -l を実行
		perror("exec failed");          // exec 失敗時
		exit(1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);

	return (0);
}