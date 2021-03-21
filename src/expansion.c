/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 08:45:43 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 21:58:55 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"

static void	replace_env(char **str, t_hashtable *env, size_t *i)
{
	size_t	j;
	char	*key;
	char	*value;

	j = 0;
	value = NULL;
	if ((*str)[1] == '?')
		j++;
	else
	{
		while (ft_isalnum_or_uscore((*str)[*i + j + 1]))
			j++;
	}
	key = ft_substr(*str, *i, j + 1);
	value = get_value(env, key + 1);
	if (!value)
		value = "";
	*str = ft_strreplace(str, key, value);
	*i += ft_strlen(value);
	j = 0;
	free(key);
}

static int	literal_variable(char **s, int i)
{
	char	*str;

	str = *s;
	ft_memmove(&str[i], &str[i + 1], ft_strlen(str) - i);
	return (2);
}

int			expand_env(char **str, t_hashtable *env)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] == '$')
			i += literal_variable(str, i);
		else if ((*str)[i] == '$')
			replace_env(str, env, &i);
		else if ((*str)[i] == '~')
			ft_strreplace(str, "~", get_value(env, "HOME"));
		i++;
	}
	return (0);
}
