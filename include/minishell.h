/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:16:10 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 09:05:57 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "libft.h"
# include "hash.h"
# include "token.h"
# include "job.h"

typedef	struct	s_session
{
	t_job		*jobs;
	t_hashtable	*env;
	char		**envp;
	char		**child_envp;
	size_t		envp_size;
	bool		signal;
}				t_session;

extern t_session	*g_session;

void			repl(t_session *session);
void			prompt(t_hashtable *env);
void			sighandler_prompt(int signum);
void			sighandler_process(int signum);
int				pathslen(char c, const char *path);
char			*setpath(const char *path, const char *argv, int i);
char			*abspath(const char *argv);
char			**getpaths(const char *argv, const char *path);
int				execute_all(t_session *session);
int				execute_builtin(t_process *p, t_session *session,
					bool *builtin, int out);
int				execute_process(t_process *p, t_session *s, int in, int out);
int				file_descriptor_handler(int in, int out);
int				redirect_handler(t_process *p, int in, int out);

#endif
