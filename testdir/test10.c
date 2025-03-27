// クライアントプログラム
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	pid_t	server_pid;

	// サーバーのPID（サーバーが表示したものを使う）
	printf("サーバーPIDを入力してください: ");
	scanf("%d", &server_pid);
	// SIGUSR1シグナルをサーバーに送る
	kill(server_pid, SIGUSR1);
	printf("サーバーにSIGUSR1を送信しました\n");
	return (0);
}
