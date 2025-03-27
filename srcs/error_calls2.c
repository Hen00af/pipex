/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_calls2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:08:36 by shattori          #+#    #+#             */
/*   Updated: 2025/03/27 20:08:45 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
