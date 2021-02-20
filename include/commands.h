/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:57:42 by aroque            #+#    #+#             */
/*   Updated: 2021/02/07 23:18:51 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "minishell.h"

void	ft_export(t_shell *shell);
void	ft_unset(t_shell *shell);
void	ft_env(t_shell *shell);
//void	ft_echo(t_shell *shell);
void	ft_echo(char *cmd_suffix, int fd[2]);
void	ft_pwd(t_shell *shell);
void	ft_cd(t_shell *shell);
void	ft_exit(t_shell *shell);

#endif
