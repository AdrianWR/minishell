/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2021/03/07 20:32:53 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commands.h"
#include "minishell.h"
#include "libft.h"
#include "errcode.h"
#include "job.h"

/*
** Use environment path and argv to make
** paths of a program to try to execute
*/

void		execute(char *const *argv, t_shell *shell)
{
	char	**paths;
	int		len;
	int		r;
	int		i;
	char	*path;

	path = ht_get(shell->env, "PATH");
	len = pathslen(**argv, path);
	if (!(paths = malloc((len + 1) * sizeof(char *))))
		return ;
	paths[len] = NULL;
	if (**argv == '/' || **argv == '~' || **argv == '.')
		paths[--len] = abspath(*argv);
	i = -1;
	while (++i < len)
		paths[i] = setpath(path, *argv, i);
	i = 0;
	r = -1;
	while (r < 0 && paths[i])
		r = execve(paths[i++], &argv[0], shell->envp);
	freemat(paths);
	exit(0);
}

int			execute_process(t_process *process, t_shell *shell)
{
	pid_t	pid;
	int		status;

	status = 0;
	if ((pid = fork()) < 0)
		message_and_exit(ERRSYS, NULL);
	else if (pid == 0)
		execute(process->argv, shell);
	else
		waitpid(pid, &status, 0);
	return (status);
}

int			execute_job(t_process *process, t_shell *shell)
{
	int	status;

	status = 0;
	while (process)
	{
		execute_process(process, shell);
		process = process->next;
	}
	return (status);
}

int			execute_all(t_shell *shell)
{
	int	status;

	status = 0;
	while (shell->jobs && !status)
	{
		shell->envp = unload_env(shell->env);
		status = execute_job(shell->jobs->process_list, shell);
		//freemat(shell->envp);
		shell->jobs = shell->jobs->next;
	}
	return (status);
}
