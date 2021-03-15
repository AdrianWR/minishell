/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2021/03/14 16:21:00 by aroque           ###   ########.fr       */
=======
/*   Updated: 2021/03/14 20:01:49 by aroque           ###   ########.fr       */
>>>>>>> 871a1be (Fix file descriptor built-in bug)
=======
/*   Updated: 2021/03/15 09:21:44 by aroque           ###   ########.fr       */
>>>>>>> 8882b57 (Implement local env variables)
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

char **local_envp(char **local_envp, char **envp, size_t envp_size)
{
	unsigned i;
	unsigned j;
	char **new_envp;

	i = 0;
	j = 0;
	while (local_envp[i])
		i++;
	i += envp_size + 1;
	new_envp = ft_calloc(i, sizeof(*new_envp));
	new_envp[i] = NULL;
	while (j < i)
	{
		if (envp[j])
			new_envp[j] = *envp++;
		else
			new_envp[j] = *local_envp++;
		j++;
	}
	return (new_envp);
}

/*
** Use environment path and argv to make
** paths of a program to try to execute
*/

void	execute(t_process *p, t_shell *shell)
{
	char	*pathtotry;
	char	*path;
	int		len;
	int		r;
	int		i;
	char 	**child_env;

	child_env = local_envp(p->local_env, shell->envp, shell->envp_size);
	i = 0;
	r = -1;
	path = get_value(shell->env, "PATH");
	len = pathslen(p->argv[0][0], path);
	while (r < 0 && len--)
	{
		pathtotry = setpath(path, p->command, i++);
		r = execve(pathtotry, p->argv, child_env);
		free(pathtotry);
	}
	freemat(child_env);
	free(path);
	if (r)
		message_and_exit(ECMDNF, 127, p->command);
	exit(r);
}

int		execute_builtin(t_process *p, t_shell *shell, bool *exec, int out)
{
	unsigned	i;
	int			status;

	i = 0;
	status = 0;
	*exec = true;
	while (!p->command && p->local_env[i])
		set_value(shell->env, p->local_env[i++], false);
	if (!p->command)
		return (status);
	if (ft_streq(p->command, "echo"))
		status = ft_echo(p->argv, out);
	else if (ft_streq(p->command, "exit"))
		status = ft_exit(shell);
	else if (ft_streq(p->command, "env"))
		status = ft_env(shell->envp, out);
	else if (ft_streq(p->command, "export"))
		status = ft_export(p->argv, shell->envp, shell->envp_size, out);
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
	status = execute_builtin(p, shell, &builtin, out);
	if (!builtin && !status)
	{
		if ((pid = fork()) < 0)
			message_and_exit(ERRSYS, EXIT_FAILURE, NULL);
		else if (pid == 0)
		{
			file_descriptor_handler(in, out);
			execute(p, shell);
		}
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
		fd[0] = dup(0);
		fd[1] = dup(1);
		shell->envp = unload_env(shell->env, &(shell->envp_size));
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
