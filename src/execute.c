/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2021/03/03 23:28:48 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commands.h"
#include "minishell.h"
#include "libft.h"
#include "errcode.h"

/*
** Use environment path and argv to make
** paths of a program to try to execute
*/

void		execute(char *const *argv, char **envp, char *path)
{
	char	**paths;
	int		len;
	int		r;
	int		i;

	len = pathslen(**argv, path);
	if (!(paths = malloc((len + 1) * sizeof(char *))))
		return ;
	paths[len] = NULL;
	if (**argv == '/' || **argv == '~' || **argv == '.')
		paths[--len] = abspath(*argv);
	i = 0;
	while (len--)
		paths[len] = setpath(path, *argv, i++);
	i = 0;
	r = -1;
	while (r < 0 && paths[i])
		r = execve(paths[i++], &argv[0], envp);
	freemat(paths);
}

int			create_process(t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = 0;
	if ((pid = fork()) < 0)
		message_and_exit(ERRSYS, NULL);
	else if (pid == 0)
		execute(shell->args, shell->envp, ht_get(shell->env, "PATH"));
	else
		waitpid(pid, &status, 0);
	return (ret);
}

int			execute_command(t_shell *shell)
{
	int		fd[2];
	void	(*builtin)(t_shell *);

	pipe(fd);
	builtin = ht_get(shell->builtins, shell->args[0]);
	if (builtin)
		builtin(shell);
	else
		create_process(shell);
	return (0);
}
