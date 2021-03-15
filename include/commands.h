/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:57:42 by aroque            #+#    #+#             */
/*   Updated: 2021/03/15 00:12:45 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "hash.h"
# include "minishell.h"

int	ft_unset(t_shell *shell);
int	ft_env(char **envp, int out);
int	ft_export(char **argv, char **envp, int size, int out);
int	ft_echo(char **argv, int out);
int	ft_pwd(t_shell *shell);
int	ft_cd(t_shell *shell);
int	ft_exit(t_shell *shell);

#endif
