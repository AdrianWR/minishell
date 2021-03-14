/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2021/03/14 16:21:00 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
	path = get_value(shell->env, "PATH");
	len = pathslen(**argv, path);
	while (r < 0 && len--)
	{
		pathtotry = setpath(path, *argv, i++);
		r = execve(pathtotry, argv, shell->envp);
		free(pathtotry);
	}
	free(path);
	if (r)
		message_and_exit(ECMDNF, 127, argv[0]);
	exit(r);
}

int		execute_builtin(t_process *process, t_shell *shell, bool *exec)
{
	char	*command;
	int		status;

	status = 0;
	*exec = true;
	command = process->argv[0];
	if (ft_streq(command, "echo"))
		status = ft_echo(process->argv);
	else if (ft_streq(command, "exit"))
		status = ft_exit(shell);
	else
		*exec = false;
	return (status);
}

int		execute_process(t_process *p, t_shell *shell, int in, int out)
{
	pid_t	pid;
	int		status;
	bool	builtin;

	status = 0;
	builtin = false;
	redirect_handler(p, in, out);
	//file_descriptor_handler(in, out);
	status = execute_builtin(p, shell, &builtin);
	if (!builtin && !status)
	{
		if ((pid = fork()) < 0)
			message_and_exit(ERRSYS, EXIT_FAILURE, NULL);
		else if (pid == 0)
			execute(p->argv, shell);
		else
			waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	set_exit_status(shell->env, status);
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
	//int fd[2];

	status = 0;
	while (shell->jobs)
	{
		//fd[0] = dup(0);
		//fd[1] = dup(1);
		shell->envp = unload_env(shell->env);
		status = execute_job(shell->jobs->process_list, shell);
		freemat(shell->envp);
		//dup2(fd[0], 0);
		//dup2(fd[1], 1);
		//close(fd[0]);
		//close(fd[1]);
		shell->jobs = shell->jobs->next;
	}
	return (status);
}
