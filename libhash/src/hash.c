/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:48:40 by aroque            #+#    #+#             */
/*   Updated: 2020/05/12 18:09:21 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "hash.h"

/*
** Hash function related to hash table data structure. This function
** let the assignment of an unique unsigned int related to each new
** key to be inserted or retrieved from the hash table. In this library,
** it was implemented the djb2 hashing algorithm.
**
** @key: String of characters used as unique identifier of list element.
** @size: Hash table max number of elements.
**
** Return: Numeric unique identifier related to input key.
*/

unsigned int	hash(const char *key, unsigned int size)
{
	unsigned int	hash;
	unsigned int	i;

	hash = 0x1505;
	i = 0;
	while (key && key[i])
	{
		hash = (hash << 0x0005) + hash + key[i];
		i++;
	}
	return (hash % size);
}
