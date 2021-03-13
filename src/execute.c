/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2021/03/13 18:34:39 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "commands.h"
#include "minishell.h"
#include "libft.h"
#include "errcode.h"
#include "job.h"

/*
** Use environment path and argv to make
** paths of a program to try to execute
*/

void	execute(char *const *argv, t_shell *shell)
{
	char	*pathtotry;
	char	*path;
	int		len;
	int		r;
	int		i;

	i = 0;
	r = -1;
	path = ht_get(shell->env, "PATH");
	len = pathslen(**argv, path);
	while (r < 0 && len--)
	{
		pathtotry = setpath(path, *argv, i++);
		r = execve(pathtotry, argv, shell->envp);
		free(pathtotry);
	}
	free(path);
	exit(0);
}

int		execute_builtin(t_process *process, t_shell *shell, int *status)
{
	char	*command;
	bool	exec;

	exec = true;
	command = process->argv[0];
	if (ft_streq(command, "exit"))
		*status = ft_exit(shell);
	else
		exec = false;
	return (!exec);
}

int		execute_process(t_process *p, t_shell *shell, int in, int out)
{
	pid_t	pid;
	int		status;

	status = 0;
	redirect_handler(p, in, out);
	if (!(execute_builtin(p, shell, &status)))
		return (status);
	if ((pid = fork()) < 0)
		message_and_exit(ERRSYS, NULL);
	else if (pid == 0)
	{
		file_descriptor_handler(in, out);
		execute(p->argv, shell);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}

int		execute_job(t_process *process, t_shell *shell)
{
	int	status;
	int in_fd;
	int out_fd;
	int	fd[2];

	status = 0;
	in_fd = STDIN_FILENO;
	while (process->next && !status)
	{
		if (pipe(fd) < 0)
			return (ERRSYS);
		out_fd = fd[1];
		status = execute_process(process, shell, in_fd, out_fd);
		close(out_fd);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		process = process->next;
	}
	if (!status)
		status = execute_process(process, shell, in_fd, STDOUT_FILENO);
	return (status);
}

int		execute_all(t_shell *shell)
{
	int status;

	status = 0;
	while (shell->jobs && !status)
	{
		shell->envp = unload_env(shell->env);
		status = execute_job(shell->jobs->process_list, shell);
		freemat(shell->envp);
		shell->jobs = shell->jobs->next;
	}
	return (status);
}
