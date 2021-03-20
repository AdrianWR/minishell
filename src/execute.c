/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 15:07:27 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include "builtins.h"
#include "minishell.h"
#include "libft.h"
#include "errcode.h"
#include "environment.h"
#include "free.h"

/*
** Use environment path and argv to make
** paths of a program to try to execute
*/

void	execute(t_process *p, t_session *session)
{
	char	*pathtotry;
	char	*path;
	int		len;
	int		r;
	int		i;

	i = 0;
	r = -1;
	path = get_value(session->env, "PATH");
	len = pathslen(p->argv[0][0], path);
	while (r < 0 && len--)
	{
		pathtotry = setpath(path, p->command, i++);
		r = execve(pathtotry, p->argv, session->child_envp);
		free(pathtotry);
	}
	if (r == -1 && !path)
		r = error_message(ENOFDI, p->command);
	if (r == -1)
		r = error_message(ECMDNF, p->command);
	freemat(session->child_envp);
	free_shell(session);
	exit(r);
}

int		execute_process(t_process *p, t_session *s, int in, int out)
{
	pid_t	pid;
	int		status;
	bool	builtin;

	status = 0;
	redirect_handler(p, in, out);
	status = execute_builtin(p, s, &builtin, out);
	if (!builtin)
	{
		if ((pid = fork()) < 0)
			message_and_exit(ERRSYS, NULL);
		else if (pid == 0)
		{
			file_descriptor_handler(in, out);
			s->child_envp = local_envp(p->local_env, s->envp, s->envp_size);
			execute(p, s);
		}
		else
			waitpid(pid, &status, 0);
	}
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (!WIFSIGNALED(status))
		set_exit_status(s->env, status);
	return (status);
}

int		execute_job(t_process *process, t_session *session)
{
	int	status;
	int in_fd;
	int out_fd;
	int	fd[2];

	status = 0;
	in_fd = STDIN_FILENO;
	while (process->next)
	{
		if (pipe(fd) < 0)
			return (ERRSYS);
		out_fd = fd[1];
		status = execute_process(process, session, in_fd, out_fd);
		close(out_fd);
		if (in_fd != 0)
			close(in_fd);
		in_fd = fd[0];
		process = process->next;
	}
	status = execute_process(process, session, in_fd, STDOUT_FILENO);
	return (status);
}

int		execute_all(t_session *session)
{
	int		status;
	int		fd[2];
	t_job	*job;

	status = 0;
	job = session->jobs;
	signal(SIGINT, sighandler_process);
	signal(SIGQUIT, sighandler_process);
	while (job && job->process_list)
	{
		fd[0] = dup(0);
		fd[1] = dup(1);
		session->envp = unload_env(session->env, &(session->envp_size));
		status = execute_job(job->process_list, session);
		freemat(session->envp);
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		job = job->next;
	}
	return (status);
}
