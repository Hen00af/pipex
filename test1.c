#include <fcntl.h> // open()を使うために必要
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	int			fd;
	char		*argv[3];
	extern char	**environ;

	// if ((fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
	// {
	// 	perror("open");
	// 	return (-1);
	// }
	// if (dup2(fd, 1) < 0)
	// {
	// 	perror("dup2");
	// 	close(fd);
	// 	return (-1);
	// }
	// close(fd);
	argv[0] = "echo";
	argv[1] = "Hello World";
	argv[2] = NULL;
	execve("/bin/echo", argv, environ);
	perror("execve");
	return (-1);
}
