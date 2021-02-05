/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:36:28 by aroque            #+#    #+#             */
/*   Updated: 2021/02/04 22:36:41 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *shell)
{
	int	flag;

	flag = 0;
	if (ft_streq(*shell->args, "-n"))
		flag = 1;
	if (!flag)
		shell->args++;
	while (*shell->args)
		ft_putstr_fd(*shell->args++, shell->fd);
	if (flag)
		ft_putchar_fd('\n', shell->fd);
}
