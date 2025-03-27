/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_calls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:06:43 by shattori          #+#    #+#             */
/*   Updated: 2025/03/27 20:07:01 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
