/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:32:31 by aroque            #+#    #+#             */
/*   Updated: 2021/02/07 18:35:51 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"

t_astnode		*ft_nodenew(void *content)
{
	t_astnode	*node;
	if (!(node = calloc(1, sizeof(*node))))
		return (NULL);
	node->content = content;
	return (node);
}

void			ft_astdelone(t_astnode *node, void (*del)(void *))
{
	if (del)
		del(node->content);
	free(node);

}

void			ft_astclear(t_astnode *node, void (*del)(void *))
{
	if (node)
	{
		ft_astclear(node->left, del);
		ft_astclear(node->right, del);
		ft_astdelone(node, del);
	}
}
