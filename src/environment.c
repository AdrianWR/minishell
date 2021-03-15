/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:45:19 by aroque            #+#    #+#             */
/*   Updated: 2021/03/15 08:53:14 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hash.h"
#include "libft.h"
#include "minishell.h"

#define HT_SIZE_ENV 1031

char			*get_value(t_hashtable *env, const char *key)
{
	void		*value;

	value = ht_get(env, key);
	return (value ? ((t_variable *)value)->value : ft_strdup(""));
}

char			*set_value(t_hashtable *env, const char *pair, bool is_env)
{
	t_variable	*variable;
	char		*tmp;
	char		*key;
	char		*value;

	if (!(variable = malloc(sizeof(*variable))))
		return (NULL);
	tmp = ft_strchr(pair, '=');
	key = ft_substr(pair, 0, tmp - pair);
	value = ft_strdup(tmp + 1);
	variable->value = value;
	variable->env = is_env;
	ht_set(env, key, variable);
	free(key);
	return (value);
}

t_hashtable		*load_env(char *envp[])
{
	t_hashtable	*env;

	env = ht_create(HT_SIZE_ENV);
	while (*envp)
		set_value(env, *envp++, true);
	set_value(env, "?=0", false);
	return (env);
}

static char		*node_to_envp(t_htlist *node)
{
	char		*str;
	char		*tmp;

	if (!node)
		return (NULL);
	tmp = ft_strjoin(node->key, "=");
	str = ft_strjoin(tmp, ((t_variable *)node->value)->value);
	free(tmp);
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
