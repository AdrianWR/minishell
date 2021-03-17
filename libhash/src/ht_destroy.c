/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 23:29:29 by aroque            #+#    #+#             */
/*   Updated: 2021/03/16 23:57:54 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

void	ht_destroy(t_hashtable *ht, void (*del)(void *))
{
	unsigned	i;
	t_htlist	*tmp;
	t_htlist	*next;

	i = 0;
	while (i < ht->size)
	{
		tmp = ht->array[i];
		while (tmp)
		{
			next = tmp->next;
			del(tmp->value);
			free(tmp->key);
			free(tmp);
			tmp = next;
		}
		i++;
	}
	free(ht->array);
	free(ht);
}
