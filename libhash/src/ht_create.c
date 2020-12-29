/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:20:06 by aroque            #+#    #+#             */
/*   Updated: 2020/05/12 23:20:15 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

/*
** Creates new hashtable data structure, with allocated memory on
** ht->array (a linked list similar structure) and list max size as
** unsigned int on ht->size.
**
** @size: Max number of keys which can be stored
** at hash table. Must be greater than 1
**
** Return: The memory address of the new allocated hash table.
** In case of error, it returns 0x0 memory address.
*/

t_hashtable	*ht_create(unsigned int size)
{
	unsigned int	i;
	t_hashtable		*ht;

	i = 0;
	if (size < 1)
		return (NULL);
	if (!(ht = malloc(sizeof(*ht))))
		return (NULL);
	if (!(ht->array = malloc(size * sizeof(t_htlist))))
		return (NULL);
	while (i < size)
	{
		ht->array[i] = 0;
		i++;
	}
	ht->size = size;
	return (ht);
}
