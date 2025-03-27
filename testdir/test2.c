#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	execute_cmd(char *cmd, int in_fd, int out_fd)
{
	pid_t	pid;
	int		pipe_fd[2];

	// パイプを作成
	pipe(pipe_fd);
	pid = fork(); // 子プロセスを作成
	if (pid == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		// 子プロセスの処理
		if (in_fd != -1)
		{
			dup2(in_fd, STDIN_FILENO); // 入力をリダイレクト
			close(in_fd);
		}
		if (out_fd != -1)
		{
			dup2(out_fd, STDOUT_FILENO); // 出力をリダイレクト
			close(out_fd);
		}
		close(pipe_fd[0]); // パイプの読み込み側を閉じる
		// コマンドを実行
		execlp(cmd, cmd, NULL);
		perror("exec failed");
		exit(1);
	}
	else
	{
		// 親プロセス
		close(pipe_fd[1]); // 書き込み側を閉じる
		wait(NULL);        // 子プロセスの終了を待つ
	}
}

int	main(int argc, char *argv[])
{
	if (argc < 4)
	{
		fprintf(stderr, "Usage: %s <input_file> <cmd1> <cmd2> <output_file>\n",
			argv[0]);
		return (1);
	}
	int input_fd = open(argv[1], O_RDONLY); // 入力ファイルを開く
	if (input_fd == -1)
	{
		perror("Error opening input file");
		return (1);
	}
	int output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 出力ファイルを開く
	if (output_fd == -1)
	{
		perror("Error opening output file");
		return (1);
	}
	// コマンド1を実行
	execute_cmd(argv[2], input_fd, output_fd);
	close(input_fd);
	close(output_fd);
	return (0);
}