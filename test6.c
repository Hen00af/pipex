#include "srcs/libft/libft.h"
#include <stdio.h>

//入力した値をコマンド部とオプション部分にわけ、そこから環境変数
//づてにコマンドが格納されているパスを見つける。
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	//パスを格納
	// while (paths[++i])
	// 	printf("%s\n", paths[i]);
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		// printf("%s", part_path);
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}
int	main(int ac, char **arv, char **env)
{
	char	**cmd;
	int		i;
	char	*path;
	char	*av;

	av = "ls -l";
	i = -1;
	cmd = ft_split(av, ' ');
	// while (cmd[++i])
	// 	printf("%s\n", cmd[i]);
	path = find_path(cmd[0], env);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		return (1);
	}
	if (execve(path, cmd, env) == -1)
		return (2);
}
