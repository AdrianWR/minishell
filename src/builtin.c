/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:16:23 by aroque            #+#    #+#             */
/*   Updated: 2021/03/19 08:30:29 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "process.h"
#include "commands.h"
#include "errcode.h"

int		select_builtin(t_process *p, t_shell *s, int out, char **n)
{
	int status;

	status = 0;
	if (ft_streq(p->command, "echo"))
		status = ft_echo(p->argv, out);
	else if (ft_streq(p->command, "pwd"))
		status = ft_pwd(p->argv, out, n);
	else if (ft_streq(p->command, "cd"))
		status = ft_cd(p->argv, s->env, n);
	else if (ft_streq(p->command, "exit"))
		status = ft_exit(s);
	else if (ft_streq(p->command, "env"))
		status = ft_env(s->envp, out);
	else if (ft_streq(p->command, "export"))
		status = ft_export(p, s, out, n);
	else if (ft_streq(p->command, "unset"))
		status = ft_unset(p->argv, s->env);
	else
		status = ECOMMAND;
	return (status);
}

int		execute_builtin(t_process *p, t_shell *shell, bool *exec, int out)
{
	unsigned	i;
	int			status;
	char		*note;

	i = 0;
	status = 0;
	*exec = true;
	note = NULL;
	while (!p->command && p->local_env[i])
		set_value(shell->env, p->local_env[i++], false);
	if (!p->command)
		return (status);
	status = select_builtin(p, shell, out, &note);
	if (status == ECOMMAND)
		*exec = false;
	else if (status)
	{
		status = error_message(status, note);
		free(note);
	}
	return (status);
}
