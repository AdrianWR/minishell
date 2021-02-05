/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:45:19 by aroque            #+#    #+#             */
/*   Updated: 2021/02/04 22:29:58 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "libft.h"
#include <unistd.h>

#define HT_SIZE_ENV 1031

t_hashtable		*load_env(char *envp[])
{
	char		**pair;
	t_hashtable	*env;

	env = ht_create(HT_SIZE_ENV);
	while (*envp)
	{
		pair = ft_split(*envp, '=');
		ht_set(env, pair[0], pair[1]);
		free(pair[0]);
		free(pair);
		envp++;
	}
	return (env);
}
