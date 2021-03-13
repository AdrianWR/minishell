/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 18:03:06 by aroque            #+#    #+#             */
/*   Updated: 2021/03/13 18:35:25 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "process.h"
#include "errcode.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int	redirect_handler(t_process *p, int in, int out)
{
	int		i;
	int		status;
	t_file	*file;

	i = 0;
	status = 0;
	file = p->input_file;
	if (file)
	{
		file->fd = open(file->path, file->flags);
		dup2(file->fd, in);
		close(file->fd);
	}
	while (p->output_file[i] && !status)
	{
		file = p->output_file[i++];
		file->fd = open(file->path, file->flags, 0644);
		dup2(file->fd, out);
		close(file->fd);
	}
	return (status);
}

int	file_descriptor_handler(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}
