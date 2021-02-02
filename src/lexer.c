/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:44:50 by aroque            #+#    #+#             */
/*   Updated: 2021/02/01 00:31:39 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errcode.h"
#include "hash.h"
#include "libft.h"
#include "tokenizer.h"
#include <stdbool.h>

static bool	ft_streq(const char *s1, const char *s2)
{
	return (!(ft_strncmp(s1, s2, ft_strlen(s2) + 1)));
}

int			expand_env(char **str, t_hashtable *env)
{
	size_t	i;
	size_t	j;
	char	*key;
	char	*value;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			while (ft_isalnum_or_uscore((*str)[i + j + 1]))
				j++;
			key = ft_substr(*str, i, j + 1);
			value = ht_get(env, key + 1);
			if (!value)
				value = STR_EMPTY;
			*str = ft_strreplace(str, key, value);
			i += ft_strlen(value);
			j = 0;
			free(key);
		}
		i++;
	}
	return (0);
}

static int	lex_squote(t_token *token)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(token->value);
	if (token->value[len - 1] != '\'')
		return (EUNFQT);
	tmp = ft_substr(token->value, 1, len - 2);
	free(token->value);
	token->value = tmp;
	token->type = T_LITERAL;
	return (0);
}

static int	lex_dquote(t_token *token, t_hashtable *env)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(token->value);
	if (token->value[len - 1] != '\"')
		return (EUNFQT);
	tmp = ft_substr(token->value, 1, len - 2);
	free(token->value);
	token->value = tmp;
	token->type = T_LITERAL;
	expand_env(&token->value, env);
	return (0);
}

int			lexical_analysis(t_token *token, t_hashtable *env)
{
	int		err;

	err = 0;
	if (ft_streq(token->value, ">"))
		token->type = T_REDIRECT_OUTPUT;
	else if (ft_streq(token->value, ">>"))
		token->type = T_APPEND_OUTPUT;
	else if (ft_streq(token->value, "<"))
		token->type = T_REDIRECT_INPUT;
	else if (ft_streq(token->value, ";"))
		token->type = T_SEPARATOR;
	else if (ft_streq(token->value, "|"))
		token->type = T_PIPE;
	else if (token->value[0] == '\'')
		err = lex_squote(token);
	else if (token->value[0] == '\"')
		err = lex_dquote(token, env);
	else
	{
		expand_env(&token->value, env);
		token->type = T_LITERAL;
	}
	return (err);
}
