/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 22:36:28 by aroque            #+#    #+#             */
/*   Updated: 2021/03/03 23:27:48 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "minishell.h"

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
