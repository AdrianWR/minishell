/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:45:19 by aroque            #+#    #+#             */
/*   Updated: 2021/03/15 23:26:34 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hash.h"
#include "libft.h"
#include "minishell.h"

#define HT_SIZE_ENV 1031

t_hashtable		*load_env(char *envp[])
{
	t_hashtable	*env;

	env = ht_create(HT_SIZE_ENV);
	while (*envp)
		set_value(env, *envp++, true);
	set_value(env, "?=0", false);
	return (env);
}

char			*node_to_envp(t_htlist *node)
{
	char		*str;
	char		*tmp;

	if (!node)
		return (NULL);
	str = ((t_variable *)node->value)->value;
	if (str)
	{
		tmp = ft_strjoin("=", str);
		str = ft_strjoin(node->key, tmp);
		free(tmp);
	}
	else
		str = ft_strdup(node->key);
	return (str);
}

char			**unload_env(t_hashtable *env, size_t *envp_size)
{
	unsigned	i;
	unsigned	j;
	char		**envp;
	t_htlist	*tmp;

	i = 0;
	j = 0;
	if (!(envp = ft_calloc(env->storage + 1, sizeof(*envp))))
		return (NULL);
	while (i < env->size && j < env->storage)
	{
		tmp = env->array[i];
		while (tmp && j < env->storage)
		{
			if (((t_variable *)(tmp->value))->env)
				envp[j++] = node_to_envp(tmp);
			tmp = tmp->next;
		}
		i++;
	}
	envp[j] = NULL;
	if (envp_size)
		*envp_size = j;
	return (envp);
}

char			**local_envp(char **local_envp, char **envp, size_t envp_size)
{
	unsigned	i;
	unsigned	j;
	char		**new_envp;

	i = 0;
	j = 0;
	while (local_envp[i])
		i++;
	i += envp_size + 1;
	new_envp = ft_calloc(i, sizeof(*new_envp));
	new_envp[i] = NULL;
	while (j < i)
	{
		if (envp[j])
			new_envp[j] = *envp++;
		else
			new_envp[j] = *local_envp++;
		j++;
	}
	return (new_envp);
}
