/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2021/01/20 02:49:10 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commands.h"
#include "minishell.h"
#include "libft.h"
#include "errcode.h"

#include <stdio.h>

int		pathslen(char c, const char *path)
{
	int	len;

	len = 0;
	if (*path)
		len++;
	while (*path)
		if (*path++ == ':')
			len++;
	if (c == '/' || c == '~' || c == '.')
		len = 1;
	return (len);
}

char	*setpath(const char *path, const char *argv, int i)
{
	char	*fullpath;
	int		start;
	int		end;

	end = 0;
	start = 0;
	while (path[end])
		if (path[end++] == ':')
		{
			if (!i-- && end--)
				break ;
			else
				start = end;
		}
	if (!(fullpath = malloc(
		(end - start + 2 + ft_strlen(argv)) * sizeof(char))))
		return (NULL);
	i = 0;
	while (start < end)
		fullpath[i++] = path[start++];
	fullpath[i++] = '/';
	start = 0;
	while (argv[start])
		fullpath[i++] = argv[start++];
	return (fullpath);
}

char	*abrlpath(const char *argv)
{
	char	*fullpath;
	char	cwd[4096 + 1];
	int		len;
	int		i;

	fullpath = NULL;
	if (*argv == '.')
	{
		if (getcwd(cwd, 4096) == NULL)
			return (NULL);
		len = ft_strlen(cwd);
		if (!(fullpath = malloc((len + ft_strlen(argv) + 1) * sizeof(char))))
			return (NULL);
		i = 0;
		len = 0;
		while (cwd[len])
			fullpath[len++] = cwd[i++];
		i = 0;
		while (argv[i])
			fullpath[len++] = argv[i++];
		return (fullpath);
	}
	return (ft_strdup(argv));
}

void	execute(char *const *argv, char **envp, char *path)
{
	char	**paths;
	int		len;
	int		r;
	int		i;

	r = -1;
	i = 0;
	len = pathslen(**argv, path);
	if (!(paths = malloc((len + 1) * sizeof(char *))))
		return ;
	paths[len] = NULL;
	if (**argv == '/' || **argv == '~' || **argv == '.')
		paths[--len] = abrlpath(*argv);
	while (len--)
		paths[len] = setpath(path, *argv, i++);
	i = 0;
	while (r < 0 && paths[i])
		r = execve(paths[i++], &argv[0], envp);
	freemat(paths);
}

/*
**	void	(*builtin)();
**	if ((builtin = ht_get(env, *argv)) != NULL)
**		builtin(argv);
*/

void	create_process(char *const *argv, char **envp, t_hashtable *env)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) < 0)
		message_and_exit(ERRSYS, NULL);
	else if (pid == 0)
	{
		if (ft_strncmp("cd", *argv, 2) == 0)
			cd(argv);
		else
		{
			execute(argv, envp, ht_get(env, "PATH"));
		}
	}
	else
	{
		while (wait(&status) != pid)
			;
	}
}
