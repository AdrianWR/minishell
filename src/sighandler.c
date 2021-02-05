/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:36:50 by gariadno          #+#    #+#             */
/*   Updated: 2021/02/03 21:15:03 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"
#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_shell->exit = true;
	}
	g_shell->exit = true;
}
