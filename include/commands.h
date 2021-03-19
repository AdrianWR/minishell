/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:57:42 by aroque            #+#    #+#             */
/*   Updated: 2021/03/18 20:20:12 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "hash.h"
# include "minishell.h"

int ft_unset(char **argv, t_hashtable *env);
int	ft_env(char **envp, int out);
int	ft_export(t_process *process, t_shell *shell, int out, char **note);
int	ft_echo(char **argv, int out);
int	ft_pwd(int out);
int	ft_cd(char **argv, t_hashtable *env, char **note);
int	ft_exit(t_shell *shell);

#endif
