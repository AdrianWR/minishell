/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:16:10 by aroque            #+#    #+#             */
/*   Updated: 2021/01/20 02:40:03 by gariadno         ###   ########.fr       */
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

void			create_process(char *const *argv, char **envp,
					t_hashtable *env);
void			sighandler(int signum);
char			**tokenizer(char *input);
t_hashtable		*load_env(char *envp[]);
void			repl(t_hashtable *env, char **envp);
char			**getpaths(const char *argv, const char *path);
void			freemat(char **mat);

#endif
