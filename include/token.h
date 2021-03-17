/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:42:49 by aroque            #+#    #+#             */
/*   Updated: 2021/03/16 20:52:36 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "hash.h"
# include "libft.h"

# define C_SQUOTE	'\''
# define C_DQUOTE	'"'
# define C_ESCAPE	'\\'
# define C_PIPE		'|'
# define C_LESS		'<'
# define C_GREATER	'>'
# define C_SMCOLON	';'
# define C_SPACE	' '
# define C_NULL		'\0'
# define C_GENERAL	-1

# define TOKEN_BUFFER_SIZE 4096

typedef enum		e_state
{
	S_GENERAL,
	S_SQUOTE,
	S_DQUOTE,
	S_ESCAPE
}					t_state;

typedef enum		e_type
{
	T_UNDEFINED,
	T_WORD,
	T_SEPARATOR,
	T_PIPE,
	T_END_OF_LINE,
	T_IREDIRECT,
	T_OREDIRECT,
	T_OAPPEND
}					t_type;

typedef struct		s_tkdata
{
	size_t			i;
	size_t			j;
	const char		*input;
	t_state			state;
	t_hashtable		*env;
	char			buffer[TOKEN_BUFFER_SIZE];
}					t_tkdata;

typedef struct		s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
}					t_token;

t_token				*tokenizer(const char *input, t_hashtable *env);
int					lexer(t_token *token, t_hashtable *env);
void				free_tokens(t_token **tokens);

#endif
