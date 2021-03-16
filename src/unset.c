/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 22:01:22 by aroque            #+#    #+#             */
/*   Updated: 2021/03/15 23:22:37 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "minishell.h"

void	free_variable(void *v)
{
	free(((t_variable *)v)->value);
	free(v);
}

int		ft_unset(char **argv, t_hashtable *env)
{
	argv++;
	while (*argv)
		ht_remove(env, *argv++, free_variable);
	return (0);
}
