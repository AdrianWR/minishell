/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:58:03 by aroque            #+#    #+#             */
/*   Updated: 2021/03/18 00:18:33 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(t_hashtable *env, int status)
{
	t_variable *var;

	var = ht_get(env, "?");
	free(var->value);
	var->value = ft_itoa(status);
}
