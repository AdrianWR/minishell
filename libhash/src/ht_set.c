/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:21:38 by aroque            #+#    #+#             */
/*   Updated: 2020/12/30 18:27:24 by aroque           ###   ########.fr       */
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

static char	*ft_strdup(const char *s1)
{
	char	*s;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	if (!(s = malloc((i + 1) * sizeof(*s))))
		return (NULL);
	s[i] = '\0';
	while (i--)
		s[i] = s1[i];
	return (s);
}

static void	override_node(t_htlist *tmp, t_htlist *node)
{
	free(tmp->value);
	tmp->value = node->value;
	free(node->value);
	free(node->key);
	free(node);
}

static void	insert_node(t_hashtable *ht, t_htlist *node)
{
	unsigned int	i;
	t_htlist		*tmp;

	i = hash(node->key, ht->size);
	if (!ht->array[i])
	{
		node->next = NULL;
		ht->array[i] = node;
	}
	else
	{
		tmp = ht->array[i];
		while (tmp->next)
		{
			if (ft_strcmp(tmp->key, node->key) == 0)
			{
				override_node(tmp, node);
				return ;
			}
			tmp = tmp->next;
		}
		tmp->next = node;
	}
}

/*
** ht_set(): Insert key-value pair into some hashtable. The key
** must be a string of characters, while the value can be a pointer
** to any type. This function returns 0 in case of success, and 1
** in case of memory allocation or hash table addressing error.
**
** @ht: Pointer to hash table structure created from ht_create().
** @key: Unique identifier of list element, passed as string.
** @value: Pointer to list element content, which can be any type.
**
** Return: 0 in case of success, 1 otherwise.
*/

int			ht_set(t_hashtable *ht, const char *key, void *value)
{
	t_htlist	*node;

	if (!ht)
		return (1);
	node = malloc(sizeof(t_htlist));
	if (!node)
		return (1);
	node->key = ft_strdup(key);
	node->value = value;
	insert_node(ht, node);
	return (0);
}
