/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:36:28 by aroque            #+#    #+#             */
/*   Updated: 2021/03/14 19:59:57 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

int		ft_echo(char **argv, int fd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (argv[i] && ft_streq(argv[i], "-n"))
	{
		newline = false;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', fd);
	return (0);
}
