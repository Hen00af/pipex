#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char	*cmd1[] = {"cat", "input", NULL};
char	*cmd2[] = {"head", NULL};
char	*cmd3[] = {"grep", "char", NULL};
char	**cmds[] = {cmd1, cmd2, cmd3};
int		cmd_n = 3;

void	dopipes(int i)
{
	pid_t	ret;
	int		pp[2];

	if (i == cmd_n - 1)
	{
		// 最後のコマンドなら、単純にexecvpで実行
		execvp(cmds[i][0], cmds[i]);
		perror("execvp failed");
		exit(1);
	}
	else
	{
		// それ以外はパイプを作成し、子プロセスで再帰的に処理
		pipe(pp);
		ret = fork();
		if (ret == 0)
		{
			// 子プロセス
			close(pp[0]);               // 読み込み側は閉じる
			dup2(pp[1], STDOUT_FILENO); // 標準出力をパイプの書き込み側にリダイレクト
			close(pp[1]);
			// 次のコマンドを実行
			dopipes(i + 1);
		}
		else
		{
			// 親プロセス
			close(pp[1]);              // 書き込み側は閉じる
			dup2(pp[0], STDIN_FILENO); // 標準入力をパイプの読み込み側にリダイレクト
			close(pp[0]);
			// 現在のコマンドを実行
			execvp(cmds[i][0], cmds[i]);
			perror("execvp failed");
			exit(1);
		}
	}
}

int	main(void)
{
	pid_t	ret;

	// 最初に親プロセスがdopipesを呼び出して実行
	ret = fork();
	if (ret == 0)
	{
		dopipes(0); // 最初のコマンドを処理
	}
	else
	{
		wait(NULL); // 子プロセスの終了を待つ
	}
	return (0);
}
