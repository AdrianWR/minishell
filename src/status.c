/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:58:03 by aroque            #+#    #+#             */
/*   Updated: 2021/03/14 14:58:20 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(t_hashtable *env, int status)
{
	char *exit_status;

	exit_status = get_value(env, "?");
	free(exit_status);
	exit_status = ft_strdup(ft_itoa(status));
}
