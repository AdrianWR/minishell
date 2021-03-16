/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:36:50 by gariadno          #+#    #+#             */
/*   Updated: 2021/03/16 03:11:56 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	sighandler_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		prompt(g_shell->env);
		set_exit_status(g_shell->env, 130);
	}
	else if (signum == SIGQUIT)
		ft_putstr_fd("\b \b\b \b", 1);
}

void	sighandler_process(int signum)
{
	ft_putchar_fd('\n', 1);
	if (signum == SIGINT)
		set_exit_status(g_shell->env, 130);
	else if (signum == SIGQUIT)
		set_exit_status(g_shell->env, 131);
}
