/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:57:42 by aroque            #+#    #+#             */
/*   Updated: 2021/03/14 19:58:36 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "minishell.h"

int	ft_export(t_shell *shell);
int	ft_unset(t_shell *shell);
int	ft_env(t_shell *shell);
int	ft_echo(char **argv, int out);
int	ft_pwd(t_shell *shell);
int	ft_cd(t_shell *shell);
int	ft_exit(t_shell *shell);

#endif
