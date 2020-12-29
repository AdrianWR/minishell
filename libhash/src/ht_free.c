/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 15:46:24 by aroque            #+#    #+#             */
/*   Updated: 2020/05/12 23:20:15 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

/*
** ht_free(): Completely erases a hash table from existence.
** Traverses the table linked list and free each one of its
** elements. Finally, frees the memory allocated for the hash
** table itself.
**
** @ht: The hashtable to be wiped out.
** @del: Pointer to function to free the value of each element.
*/

static void	ft_lstdelone(t_htlist *lst, void (*del)(void*))
{
	if (del)
		del(lst->value);
	free(lst->key);
	free(lst);
}

void		ht_free(t_hashtable *ht, void (*del)(void*))
{
	unsigned int i;

	if (!ht)
		return ;
	i = 0;
	while (i < ht->size)
	{
		if (ht->array[i])
			ft_lstdelone(ht->array[i], del);
		i++;
	}
	free(ht->array);
	free(ht);
}
