/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2021/02/17 14:19:01 by aroque           ###   ########.fr       */
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

/*
**
**
**
**
*/

#include <stdio.h>

static int			execute_fork(t_astnode *cmd_node, int fd[2])
{
	pid_t	pid;
	int		status;
	int		ret;
	char	**argv;

	ret = 0;
	ft_putstr_fd("passou aqui 1", STDOUT_FILENO);
	if ((pid = fork()) < 0)
		message_and_exit(ERRSYS, NULL);
	else if (pid == 0)
	{
		//fd[1] = 1;
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		argv = ft_split(cmd_node->left->content, ' ');
		ft_putstr_fd("passou aqui 2", STDOUT_FILENO);
		execve("/usr/bin/", argv, g_shell->envp);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, &status, 0);
	}
	return (ret);
}

int			execute_command(t_shell *shell)
{
	void	(*builtin)(t_shell *);

	builtin = ht_get(shell->builtins, shell->args[0]);
	if (builtin)
		builtin(shell);
	else
		create_process(shell);
	return (0);
}


static int execute_cmd(t_astnode *cmd_node, int fd[2])
{
	char *name;
	char *suffix;

	suffix = NULL;
	name = cmd_node->left->content;
	//if (cmd_node->right)
	//	suffix = cmd_node->right->content;
	//if (ft_streq(name, "echo"))
	//	ft_echo(suffix, fd);
	//else
		execute_fork(cmd_node, fd);
	return (0);
}

int      pipe_execution(t_astnode *node, int std[2])
{
    int pp[2];

    if (node)
    {
        if (node->type == PIPE_SEQUENCE)
        {
            if (node->left)
            {
                pipe(pp);
                std[1] = pp[1];
                pipe_execution(node->left, std);
                close(pp[1]);
            }
            if (node->right)
            {
                std[0] = pp[0];
                std[1] = 1;
                pipe_execution(node->right, std);
                close(std[0]);
            }
        }
		else if (node->type == COMMAND)
            execute_cmd(node, std);
    }
    return (0);
}
