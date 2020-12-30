/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:27:19 by aroque            #+#    #+#             */
/*   Updated: 2020/05/17 10:56:05 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	if ((*s1 != *s2) || !*s1)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (ft_strcmp(++s1, ++s2));
}

void		*ht_get(t_hashtable *ht, const void *key)
{
	unsigned int	i;
	t_htlist		*node;

	if (!ht)
		return (NULL);
	i = hash(key, ht->size);
	node = ht->array[i];
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			break ;
		node = node->next;
	}
	if (!node)
		return (NULL);
	return (node->value);
}
