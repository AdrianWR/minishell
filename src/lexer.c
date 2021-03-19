/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:44:50 by aroque            #+#    #+#             */
/*   Updated: 2021/03/18 23:22:29 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errcode.h"
#include "hash.h"
#include "libft.h"
#include "token.h"
#include "minishell.h"
#include <stdbool.h>

static void	replace_env(char **str, t_hashtable *env, size_t *i)
{
	size_t	j;
	char	*key;
	char	*value;

	j = 0;
	value = NULL;
	if ((*str)[1] == '?')
		j++;
	else
	{
		while (ft_isalnum_or_uscore((*str)[*i + j + 1]))
			j++;
	}
	key = ft_substr(*str, *i, j + 1);
	value = get_value(env, key + 1);
	if (!value)
		value = "";
	*str = ft_strreplace(str, key, value);
	*i += ft_strlen(value);
	j = 0;
	free(key);
}

int			expand_env(char **str, t_hashtable *env)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			replace_env(str, env, &i);
		else if ((*str)[i] == '~')
			ft_strreplace(str, "~", get_value(env, "HOME"));
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
	token->type = T_WORD;
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
	token->type = T_WORD;
	expand_env(&token->value, env);
	return (0);
}

bool		special_token(t_token *token, const char *str)
{
	return (ft_streq(token->value, str) && token->type == T_UNDEFINED);
}

int			lexer(t_token *token, t_hashtable *env)
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
