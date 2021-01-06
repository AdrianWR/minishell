/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:16:10 by aroque            #+#    #+#             */
/*   Updated: 2021/01/05 21:28:30 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "hash.h"

typedef enum	e_type
{
	COMMAND,
	PARAMETER,
	OPERATOR
}				t_type;

typedef struct	s_token
{
	char		*command;
}				t_token;

void			create_process(char *const *argv);
char			**tokenizer(char *input);
t_hashtable		*load_env(char *envp[]);
void			repl(t_hashtable *env);

#endif
