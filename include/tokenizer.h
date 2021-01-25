/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:42:49 by aroque            #+#    #+#             */
/*   Updated: 2021/01/25 09:19:27 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"

# define C_SQUOTE	'\''
# define C_DQUOTE	'"'
# define C_ESCAPE	'\\'
# define C_PIPE		'|'
# define C_LESS		'<'
# define C_GREATER	'>'
# define C_SMCOLON	';'
# define C_SPACE		' '
# define C_NULL		'\0'
# define C_GENERAL	-1

# define BUFFER_SIZE 4096

typedef enum	e_state
{
	S_GENERAL,
	S_SQUOTE,
	S_DQUOTE,
	S_ESCAPE
}				t_state;

typedef enum	e_type
{
	T_IDENTIFIER,
	T_SEPARATOR,
	T_REDIRECT,
	T_PIPE,
	T_END_OF_LINE
}				t_type;

typedef struct	s_token
{
	char		*value;
	t_type		type;
}				t_token;

typedef struct	s_tkdata
{
	size_t		i;
	size_t		j;
	t_state		state;
	char		*input;
	char		buffer[BUFFER_SIZE];
}				t_tkdata;

t_list			*tokenizer(char *input);

#endif
