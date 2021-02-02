/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:37:39 by gariadno          #+#    #+#             */
/*   Updated: 2021/01/31 22:48:28 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

void	freemat(char **mat)
{
	int i;

	i = 0;
	while (mat && mat[i])
	{
		free(mat[i]);
		mat[i++] = NULL;
	}
	if (mat)
	{
		free(mat);
		mat = NULL;
	}
}
