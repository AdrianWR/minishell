/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2021/01/21 01:32:15 by gariadno         ###   ########.fr       */
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

/*
** Makes an absolute path by concatenating
** an item i of environment path with argv and
** returns a pointer of it
*/

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
	fullpath = malloc((end - start + 2 + ft_strlen(argv)) * sizeof(char));
	if (!fullpath)
		return (NULL);
	i = 0;
	while (start < end)
		fullpath[i++] = path[start++];
	fullpath[i++] = '/';
	while (*argv)
		fullpath[i++] = *argv++;
	return (fullpath);
}

/*
** Returns a pointer to absolute
** path of a program
*/

char	*abspath(const char *argv)
{
	char	*abspath;
	char	cwd[4096 + 1];
	int		i;

	abspath = NULL;
	if (*argv == '.')
	{
		if (getcwd(cwd, 4096) == NULL)
			return (NULL);
		abspath = malloc((ft_strlen(cwd) + ft_strlen(argv) + 1) * sizeof(char));
		if (!abspath)
			return (NULL);
		i = -1;
		while (cwd[++i])
			abspath[i] = cwd[i];
		while (*argv)
			abspath[i++] = *argv++;
		return (abspath);
	}
	return (ft_strdup(argv));
}

/*
** Use environment path and argv to make
** paths of a program to try to execute
*/

void	execute(char *const *argv, char **envp, char *path)
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
