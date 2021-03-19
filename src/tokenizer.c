/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:11:31 by aroque            #+#    #+#             */
/*   Updated: 2021/03/19 08:44:42 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "token.h"

static void		tokenize_quoted(t_tkdata *tk, char quote)
{
	tk->buffer[tk->j++] = tk->input[tk->i];
	if (quote == C_DQUOTE && tk->input[tk->i] == C_ESCAPE)
		tk->buffer[tk->j++] = tk->input[++tk->i];
	else if (tk->input[tk->i] == quote)
		tk->state = S_GENERAL;
}

static void		special_token(t_tkdata *tk, t_token **tokens)
{
	get_token(tk, tokens);
	tk->buffer[tk->j++] = tk->input[tk->i];
	if (tk->input[tk->i] == '>' && tk->input[tk->i + 1] == '>')
		tk->buffer[tk->j++] = tk->input[++tk->i];
	get_token(tk, tokens);
}

static void		tokenize_general(t_tkdata *tk, t_token **tokens)
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
		special_token(tk, tokens);
	else if (tk->input[tk->i] == C_ESCAPE)
	{
		tk->buffer[tk->j++] = tk->input[++tk->i];
		tk->type = T_WORD;
	}
	else if (tk->input[tk->i] == C_SPACE)
		get_token(tk, tokens);
	else
		tk->buffer[tk->j++] = tk->input[tk->i];
}

t_token			*tokenizer(const char *input, t_hashtable *env)
{
	t_token		*tokens;
	t_tkdata	*tk;

	tokens = NULL;
	tk = ft_calloc(1, sizeof(*tk));
	tk->input = input;
	tk->env = env;
	while (tk->input[tk->i])
	{
		if (tk->state == S_GENERAL)
			tokenize_general(tk, &tokens);
		else if (tk->state == S_DQUOTE)
			tokenize_quoted(tk, C_DQUOTE);
		else if (tk->state == S_SQUOTE)
			tokenize_quoted(tk, C_SQUOTE);
		if (tk->input[tk->i + 1] == C_NULL)
			get_token(tk, &tokens);
		tk->i++;
	}
	free(tk);
	return (tokens);
}
