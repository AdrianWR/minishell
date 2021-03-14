/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:47:10 by aroque            #+#    #+#             */
/*   Updated: 2021/03/14 14:51:11 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "errcode.h"
#include "libft.h"

static void		errlog(const char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
}

void			message_and_exit(t_errcode code, int exit_status, char *note)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (errno && code == ERRSYS)
		errlog(strerror(errno));
	else if (code > 0)
	{
		if (note)
		{
			ft_putstr_fd(note, STDERR_FILENO);
			free(note);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putstr_fd(g_errstr[code], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else
		ft_putstr_fd("Fatal Error\n", STDERR_FILENO);
	exit(exit_status);
}
