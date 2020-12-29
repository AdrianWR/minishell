/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 14:12:57 by aroque            #+#    #+#             */
/*   Updated: 2020/05/17 10:57:50 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

static size_t	ft_strlen(const char *s)
{
	if (!*s)
		return (0);
	return (ft_strlen(++s) + 1);
}

static int		ft_strcmp(const char *s1, const char *s2)
{
	if ((*s1 != *s2) || !*s1)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (ft_strcmp(++s1, ++s2));
}

static char		*ft_strdup(const char *s1)
{
	int		i;
	char	*s;

	i = 0;
	if (!s1 || !(s = malloc((ft_strlen(s1) + 1) * sizeof(*s))))
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static void		node_value(t_htlist *tmp, t_htlist *node)
{
	if (!tmp)
	{
		node->next = tmp;
		tmp = node;
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_strdup(node->value);
		free(node->value);
		free(node->key);
		free(node);
	}
}

void			insert_node(t_hashtable *ht, t_htlist *node)
{
	unsigned int	i;
	t_htlist		*tmp;

	i = hash(node->key, ht->size);
	if (ht->array[i])
	{
		tmp = ht->array[i];
		while (tmp)
		{
			if (ft_strcmp(tmp->key, node->key) == 0)
				break ;
			tmp = tmp->next;
		}
		node_value(tmp, node);
	}
	else
	{
		node->next = NULL;
		ht->array[i] = node;
	}
}
