/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:44:55 by aroque            #+#    #+#             */
/*   Updated: 2021/03/17 00:22:20 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "hash.h"
#include "libft.h"
#include "minishell.h"

char			*get_value(t_hashtable *env, const char *key)
{
	void		*value;

	value = ht_get(env, key);
	return (value ? ((t_variable *)value)->value : ft_strdup(""));
}

void			key_value_pair(const char *str, char *pair[])
{
	char *tmp;

	tmp = ft_strchr(str, '=');
	if (tmp)
	{
		pair[0] = ft_substr(str, 0, tmp - str);
		pair[1] = ft_strdup(tmp + 1);
	}
	else
	{
		pair[0] = ft_strdup(str);
		pair[1] = NULL;
	}
}

char			*set_value(t_hashtable *env, const char *str, bool is_env)
{
	t_variable	*variable;
	char		*pair[2];

	key_value_pair(str, pair);
	if ((variable = ht_get(env, pair[0])))
	{
		variable->value = pair[1];
		variable->env = is_env;
	}
	else
	{
		if (!(variable = malloc(sizeof(*variable))))
			return (NULL);
		variable->value = pair[1];
		variable->env = is_env;
		ht_set(env, pair[0], variable);
	}
	free(pair[0]);
	return (pair[1]);
}
