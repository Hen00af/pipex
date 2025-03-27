#include "./srcs/pipex.h"

int	dir_check(char *file)
{
	int	fd;

	fd = open(file, O_RDWR);
	if (fd == -1)
		return (THIS_IS_NOT_FILE);
	close(fd);
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
void	check_args(int ac, char **av)
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
void	error_cmd(void)
{
	perror("zsh: command not found:");
	exit(1);
}

char	*find_path(char *cmd, char **environ)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(environ[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(environ[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
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

// execute: コマンド文字列を分割し、find_pathで実行可能なパスを取得してexecveで実行
void	execute(char *cmd)
{
	extern char	**environ;
	char		**args;
	char		*path;

	args = ft_split(cmd, ' ');
	path = find_path(args[0], environ);
	if (!path)
		error_cmd();
	if (execve(path, args, environ) == -1)
		error_cmd();
}

int	main(int argc, char **argv)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		i;

	int infile, outfile;
	int fd_in; // 現在の入力元ファイルディスクリプタ
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 ... cmdN outfile\n",
			STDERR_FILENO);
		return (1);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_input_fd(infile);
	fd_in = infile; // 最初の入力はinfile
	for (i = 2; i < argc - 1; i++)
	{
		if (i < argc - 2)
		{
			if (pipe(pipe_fd) == -1)
				error_pipe();
		}
		pid = fork();
		if (pid == -1)
			error_fork();
		if (pid == 0) // 子プロセス
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
				error_dup2();
			close(fd_in);
			if (i < argc - 2)
			{
				close(pipe_fd[0]); // 読み取り側は使わないので閉じる
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
					error_dup2();
				close(pipe_fd[1]);
			}
			else // 最後のコマンドの場合は outfile に出力
			{
				outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
						0644);
				if (outfile < 0)
					error_output_fd(fd_in, outfile);
				if (dup2(outfile, STDOUT_FILENO) == -1)
					error_dup2();
				close(outfile);
			}
			execute(argv[i]);
			exit(0);
		}
		// 親プロセス
		wait(NULL);
		if (fd_in != infile)
			close(fd_in);
		if (i < argc - 2)
		{
			close(pipe_fd[1]); // 書き込み側は親側では不要
			fd_in = pipe_fd[0];
		}
	}
	return (0);
}
