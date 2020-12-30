/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 15:40:53 by aroque            #+#    #+#             */
/*   Updated: 2020/05/17 10:56:38 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

typedef struct		s_htlist {
	char			*key;
	void			*value;
	struct s_htlist	*next;
}					t_htlist;

typedef struct		s_hashtable {
	t_htlist		**array;
	unsigned int	size;
}					t_hashtable;

unsigned int	hash(const char *key, unsigned int size);
t_hashtable		*ht_create(unsigned int size);
int				ht_set(t_hashtable *ht, const char *key, void *value);
void			*ht_get(t_hashtable *ht, const void *key);
void			insert_node(t_hashtable *ht, t_htlist *node);
void			ht_free(t_hashtable *ht, void (del)(void *));

#endif
