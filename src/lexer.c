/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:44:50 by aroque            #+#    #+#             */
/*   Updated: 2021/03/06 18:18:57 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errcode.h"
#include "hash.h"
#include "libft.h"
#include "token.h"
#include <stdbool.h>

static void	replace_env(char **str, t_hashtable *env, size_t *i)
{
	size_t	j;
	char	*key;
	char	*value;

	j = 0;
	while (ft_isalnum_or_uscore((*str)[*i + j + 1]))
		j++;
	key = ft_substr(*str, *i, j + 1);
	value = ht_get(env, key + 1);
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

	if (env == NULL)
		return (0);
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			replace_env(str, env, &i);
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

int			lexer(t_token *token, t_hashtable *env)
{
	int		err;

	err = 0;
	if (ft_streq(token->value, ">"))
		token->type = T_OREDIRECT;
	else if (ft_streq(token->value, ">>"))
		token->type = T_OAPPEND;
	else if (ft_streq(token->value, "<"))
		token->type = T_IREDIRECT;
	else if (ft_streq(token->value, ";"))
		token->type = T_SEPARATOR;
	else if (ft_streq(token->value, "|"))
		token->type = T_PIPE;
	else if (token->value[0] == '\'')
		err = lex_squote(token);
	else if (token->value[0] == '"')
		err = lex_dquote(token, env);
	else
	{
		expand_env(&token->value, env);
		token->type = T_WORD;
	}
	return (err);
}
