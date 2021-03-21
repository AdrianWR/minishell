/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:42:49 by aroque            #+#    #+#             */
/*   Updated: 2021/03/19 08:46:49 by aroque           ###   ########.fr       */
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
	t_type			type;
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
int					validate_tokens(t_token *token, char **note);
void				get_token(t_tkdata *tk, t_token **tokens);
int					expand_env(char **str, t_hashtable *env);

#endif
