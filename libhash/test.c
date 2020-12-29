/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 15:28:51 by aroque            #+#    #+#             */
/*   Updated: 2020/12/28 22:35:48 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define HT_SIZE 92

int	main(int argc, char *argv[])
{
	t_hashtable	*ht;

	ht = ht_create(HT_SIZE);
	ht_set(ht, "pao", strdup("queijo"));
	ht_set(ht, "bolo", strdup("banana"));
	ht_set(ht, "bolo", strdup("morango"));
	int i = -1;
	while (++i < ht->size)
		if (ht->array[i])
			printf("%d\t%s\t%s\n", i, ht->array[i]->key, (char *)ht->array[i]->value);
	printf("Chave: %s | Valor: %s\n", "bolo", ht_get(ht, "bolo"));
	ht_free(ht, free);
	return (0);
}
