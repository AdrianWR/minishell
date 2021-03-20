/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:57:42 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 18:24:20 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int ft_unset(char **argv, t_hashtable *env);
int	ft_env(char **envp, int out);
int	ft_export(t_process *process, t_session *session, int out, char **note);
int	ft_echo(char **argv, int out);
int	ft_pwd(char **argv, int out, char **note);
int	ft_cd(char **argv, t_hashtable *env, char **note);
int	ft_exit(t_session *session, char **argv, char **note);

#endif
