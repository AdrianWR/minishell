/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 21:18:05 by aroque            #+#    #+#             */
/*   Updated: 2021/01/05 21:36:29 by aroque           ###   ########.fr       */
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

static void	ft_lstdelone(t_htlist *node, void (*del)(void*))
{
	free(node->key);
	del(node->value);
	free(node);
}

void		del_node(t_htlist **head, const char *key, void (*del)(void*))
{
	t_htlist	*tmp;
	t_htlist	*prev;

	tmp = *head;
	prev = NULL;
	if (tmp == NULL)
		return ;
	if (tmp != NULL && !ft_strcmp(tmp->key, key))
	{
		*head = tmp->next;
		ft_lstdelone(tmp, del);
		return ;
	}
	while (tmp != NULL && !ft_strcmp(tmp->key, key))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	ft_lstdelone(tmp, del);
}

void		ht_remove(t_hashtable *ht, const char *key, void (*del)(void*))
{
	unsigned	i;
	t_htlist	*tmp;

	i = hash(key, ht->size);
	tmp = ht->array[i];
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			del_node(&tmp, key, del);
	}
}
