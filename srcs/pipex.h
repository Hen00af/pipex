#ifndef PIPEX_H
# define PIPEX_H
# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define FAILED -1
# define THIS_IS_NOT_FILE -1

int		make_process(int ac, char **av, int i);
void	do_pipe(int pipe_fd[2]);
void	handle_parent(int i, int ac, char **av);
void	handle_child(int pipe_fd[2], int i, int ac, char **av);
int		pipex(int ac, char **av);
int		dir_check(char *file);
int		check_file(char *infile, char *outfile);
void	error_pipe(void);
void	error_fork(void);
void	error_input_fd(int input_fd);
void	error_output_fd(int input_fd, int output_fd);
void	error_dup2(void);
void	error_execve(void);
void	check_args(int ac, char **av);
void	error_cmd(void);

#endif // PIPEX_H