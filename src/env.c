/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:45:19 by aroque            #+#    #+#             */
/*   Updated: 2021/01/05 21:21:24 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "libft.h"

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

void			env(char **args, t_hashtable *env)
{
	(void)args;
	(void)env;
}

void			export(char **args, t_hashtable *env)
{
	(void)args;
	(void)env;
}

void			unset(char **args, t_hashtable *env)
{
	(void)args;
	(void)env;
}
