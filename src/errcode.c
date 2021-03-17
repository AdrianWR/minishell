/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errcode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:47:10 by aroque            #+#    #+#             */
/*   Updated: 2021/03/17 09:56:53 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "errcode.h"
#include "libft.h"

static void	errlog(const char *str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
}

void		error_message(t_errcode code, char *note)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (errno && code == ERRSYS)
		errlog(strerror(errno));
	else if (code > 0)
	{
		if (note)
		{
			errlog(note);
			errlog(": ");
		}
		errlog(g_errstr[code]);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else
		errlog("Fatal Error\n");
}

void		message_and_exit(t_errcode code, char *note)
{
	error_message(code, note);
	exit(g_errstatus[code]);
}
