/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:36:27 by gariadno          #+#    #+#             */
/*   Updated: 2021/03/13 18:35:51 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int		ft_exit(t_shell *shell)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	shell->exit = true;
	return (0);
}

void	ft_pwd(t_shell *shell)
{
	char	cwd[4096 + 1];

	(void)shell;
	if (getcwd(cwd, 4096) == NULL)
		return ;
	ft_putendl_fd(cwd, STDOUT_FILENO);
}

void	ft_export(t_shell *shell)
{
	(void)shell;
}

void	ft_unset(t_shell *shell)
{
	(void)shell;
}

void	ft_cd(t_shell *shell)
{
	if (chdir(shell->args[1]) != 0)
		return ;
}
