/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:45:19 by aroque            #+#    #+#             */
/*   Updated: 2021/03/10 20:06:19 by aroque           ###   ########.fr       */
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

static char		*node_to_envp(t_htlist *node)
{
	char		*str;
	char		*tmp;

	if (!node)
		return (NULL);
	tmp = ft_strjoin(node->key, "=");
	str = ft_strjoin(tmp, node->value);
	free(tmp);
	return (str);
}

char			**unload_env(t_hashtable *env)
{
	unsigned	i;
	unsigned	j;
	char		**envp;
	t_htlist	*tmp;

	i = 0;
	j = 0;
	if (!(envp = ft_calloc(env->storage, sizeof(*envp))))
		return (NULL);
	while (i < env->size && j < env->storage)
	{
		tmp = env->array[i];
		while (tmp && j < env->storage)
		{
			envp[j++] = node_to_envp(tmp);
			tmp = tmp->next;
		}
		i++;
	}
	return (envp);
}
