/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:36:28 by aroque            #+#    #+#             */
/*   Updated: 2021/02/07 23:18:32 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "minishell.h"

//void	ft_echo(t_shell *shell)
//{
//	int	flag;
//
//	flag = 0;
//	if (ft_streq(*shell->args, "-n"))
//		flag = 1;
//	if (!flag)
//		shell->args++;
//	while (*shell->args)
//		ft_putstr_fd(*shell->args++, shell->fd);
//	if (flag)
//		ft_putchar_fd('\n', shell->fd);
//}

#define NO_NL_OPTION	"-n "
#define EMPTY			""

void		ft_echo(char *suffix, int fd[2])
{
	bool	newline;

	newline = ft_strncmp(suffix, NO_NL_OPTION, 3);
	ft_strreplace(&suffix, NO_NL_OPTION, EMPTY);
	ft_putstr_fd(suffix, fd[1]);
	if (newline)
		ft_putchar_fd('\n', fd[1]);
}
