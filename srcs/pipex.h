#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define FAILED -1
# define THIS_IS_NOT_FILE -1

static int	make_process(int ac, char **av, int i);
static void	error_handling(int ac);
static void	check_input(int ac, char **av);

#endif // PIPEX_H