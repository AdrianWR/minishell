/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:44:50 by aroque            #+#    #+#             */
/*   Updated: 2021/03/19 08:47:52 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errcode.h"
#include "hash.h"
#include "libft.h"
#include "token.h"
#include "minishell.h"
#include <stdbool.h>

static int		lex_squote(t_token *token)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(token->value);
	if (token->value[len - 1] != '\'')
		return (EUNFQT);
	tmp = ft_substr(token->value, 1, len - 2);
	free(token->value);
	token->value = tmp;
	token->type = T_WORD;
	return (0);
}

static int		lex_dquote(t_token *token, t_hashtable *env)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(token->value);
	if (token->value[len - 1] != '\"')
		return (EUNFQT);
	tmp = ft_substr(token->value, 1, len - 2);
	free(token->value);
	token->value = tmp;
	token->type = T_WORD;
	expand_env(&token->value, env);
	return (0);
}

static bool		special_token(t_token *token, const char *str)
{
	return (ft_streq(token->value, str) && token->type == T_UNDEFINED);
}

int				lexer(t_token *token, t_hashtable *env)
{
	int		err;

	err = 0;
	if (special_token(token, ">"))
		token->type = T_OREDIRECT;
	else if (special_token(token, ">>"))
		token->type = T_OAPPEND;
	else if (special_token(token, "<"))
		token->type = T_IREDIRECT;
	else if (special_token(token, ";"))
		token->type = T_SEPARATOR;
	else if (special_token(token, "|"))
		token->type = T_PIPE;
	else if (token->value[0] == '\'')
		err = lex_squote(token);
	else if (token->value[0] == '"')
		err = lex_dquote(token, env);
	else
	{
		if (!token->type)
			expand_env(&token->value, env);
		token->type = T_WORD;
	}
	return (err);
}
