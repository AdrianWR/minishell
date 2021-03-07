/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:37:39 by gariadno          #+#    #+#             */
/*   Updated: 2021/03/07 20:18:29 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "token.h"

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
	while (mat[i])
		free(mat[i++]);
	free(mat);
}

void		free_shell(t_shell *shell)
{
	ht_free(shell->env, free);
}
