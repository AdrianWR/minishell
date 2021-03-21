/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 08:43:07 by aroque            #+#    #+#             */
/*   Updated: 2021/03/19 08:43:44 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void		push_token(t_token **token, t_token *new)
{
	t_token		*tmp;

	if (!*token)
		*token = new;
	else
	{
		tmp = *token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void			get_token(t_tkdata *tk, t_token **tokens)
{
	t_token		*token;

	if (!tk->j || !(token = malloc(sizeof(*token))))
		return ;
	ft_bzero(token, sizeof(*token));
	token->value = ft_strdup(tk->buffer);
	token->type = tk->type;
	lexer(token, tk->env);
	push_token(tokens, token);
	ft_bzero(tk->buffer, tk->j);
	tk->type = T_UNDEFINED;
	tk->j = 0;
}
