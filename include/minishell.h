/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:16:10 by aroque            #+#    #+#             */
/*   Updated: 2021/01/25 09:19:42 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "hash.h"

void			create_process(char *const *argv, char **envp,
					t_hashtable *env);
void			sighandler(int signum);
t_hashtable		*load_env(char *envp[]);
void			repl(t_hashtable *env, char **envp);
char			**getpaths(const char *argv, const char *path);
void			freemat(char **mat);

#endif
