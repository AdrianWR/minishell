/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:21:38 by aroque            #+#    #+#             */
/*   Updated: 2020/05/12 23:20:15 by aroque           ###   ########.fr       */
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

int				ht_set(t_hashtable *ht, const char *key, void *value)
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
