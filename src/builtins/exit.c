/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:41:39 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 21:59:14 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "errcode.h"
#include "free.h"
#include "libft.h"

static bool	numerical(char *str)
{
	if (!*str)
		return (true);
	if (!ft_isdigit(*str))
		return (false);
	return (numerical(str + 1));
}

int			ft_exit(t_session *session, char **argv, char **note)
{
	int		n;
	char	*tmp;

	n = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (argv[1] && !numerical(argv[1]))
		n = ENUMARG;
	else if (argv[1] && argv[2])
	{
		*note = ft_strdup("exit: ");
		return (ETMARGS);
	}
	if (n)
	{
		tmp = ft_strjoin("exit: ", argv[1]);
		error_message(n, tmp);
		free(tmp);
		n = g_errstatus[ENUMARG];
	}
	else if (argv[1])
		n = ft_atoi(argv[1]);
	free_shell(session);
	exit(n);
}
