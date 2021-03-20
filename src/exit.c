/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:41:39 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 08:41:58 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int			ft_exit(t_session *session)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_shell(session);
	exit(EXIT_SUCCESS);
}
