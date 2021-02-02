/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:11:31 by aroque            #+#    #+#             */
/*   Updated: 2021/01/31 23:46:02 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include "tokenizer.h"

static t_tkdata	*init_tk(char *input)
{
	t_tkdata	*tk;

	if (!(tk = malloc(sizeof(*tk))))
		return (NULL);
	tk->i = 0;
	tk->j = 0;
	tk->state = S_GENERAL;
	tk->input = input;
	ft_bzero(tk->buffer, BUFFER_SIZE);
	return (tk);
}

static void		get_token(t_tkdata *tk, t_list **tokens)
{
	t_token		*token;

	if (!tk->j || !(token = malloc(sizeof(*token))))
		return ;
	token->value = ft_strdup(tk->buffer);
	ft_lstadd_back(tokens, ft_lstnew(token));
	ft_bzero(tk->buffer, tk->j);
	tk->j = 0;
}

static void		tokenize_quoted(t_tkdata *tk, char quote)
{
	tk->buffer[tk->j++] = tk->input[tk->i];
	if (tk->input[tk->i] == quote)
		tk->state = S_GENERAL;
}

static void		tokenize_general(t_tkdata *tk, t_list **tokens)
{
	if (tk->input[tk->i] == C_SQUOTE)
	{
		tk->state = S_SQUOTE;
		tk->buffer[tk->j++] = tk->input[tk->i];
	}
	else if (tk->input[tk->i] == C_DQUOTE)
	{
		tk->state = S_DQUOTE;
		tk->buffer[tk->j++] = tk->input[tk->i];
	}
	else if (ft_strchr("|<>;", tk->input[tk->i]))
	{
		get_token(tk, tokens);
		tk->buffer[tk->j++] = tk->input[tk->i];
		if (tk->input[tk->i] == '>' && tk->input[tk->i + 1] == '>')
			tk->buffer[tk->j++] = tk->input[++tk->i];
		get_token(tk, tokens);
	}
	else if (tk->input[tk->i] == C_ESCAPE)
		tk->buffer[tk->j++] = tk->input[++tk->i];
	else if (tk->input[tk->i] == C_SPACE)
		get_token(tk, tokens);
	else
		tk->buffer[tk->j++] = tk->input[tk->i];
}

t_list			*tokenizer(char *input)
{
	t_list		*tokens;
	t_tkdata	*tk;

	tokens = NULL;
	tk = init_tk(input);
	while (input[tk->i])
	{
		if (tk->state == S_GENERAL)
			tokenize_general(tk, &tokens);
		else if (tk->state == S_DQUOTE)
			tokenize_quoted(tk, C_DQUOTE);
		else if (tk->state == S_SQUOTE)
			tokenize_quoted(tk, C_SQUOTE);
		if (input[tk->i + 1] == C_NULL)
			get_token(tk, &tokens);
		tk->i++;
	}
	free(tk);
	return (tokens);
}
