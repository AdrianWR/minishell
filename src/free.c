/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:37:39 by gariadno          #+#    #+#             */
/*   Updated: 2021/02/04 22:39:55 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "tokenizer.h"

void		free_token(void *token)
{
	t_token	*tk;

	tk = (t_token *)token;
	free(tk->value);
	free(tk);
}

void		freemat(char **mat)
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

void		free_shell(t_shell *shell)
{
	ft_lstclear(&shell->tokens, free_token);
	ht_free(shell->env, free);
}
