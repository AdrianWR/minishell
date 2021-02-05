/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:16:10 by aroque            #+#    #+#             */
/*   Updated: 2021/02/04 22:44:07 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>

# include "libft.h"
# include "hash.h"

# define BIN	"./minishell"

typedef	struct	s_shell
{
	int			status;
	t_list		*tokens;
	t_hashtable	*env;
	t_hashtable	*builtins;
	char		**envp;
	char		*input;
	bool		exit;
	char		**args;
	int			fd;
}				t_shell;

extern t_shell	*g_shell;

int				create_process(char *const *argv, t_shell *shell);
void			sighandler(int signum);
void			repl(t_shell *shell);
char			**getpaths(const char *argv, const char *path);
void			freemat(char **mat);
bool			ft_streq(const char *s1, const char *s2);
t_hashtable		*load_env(char *envp[]);
int				execute_command(t_shell *shell);
void			free_shell(t_shell *shell);

int				pathslen(char c, const char *path);
char			*setpath(const char *path, const char *argv, int i);
char			*abspath(const char *argv);

#endif
