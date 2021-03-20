/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:36:27 by gariadno          #+#    #+#             */
/*   Updated: 2021/03/20 08:35:42 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "minishell.h"
#include "errcode.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*get_pwd(void)
{
	char	cwd[4096 + 1];
	char	*pwd;

	pwd = NULL;
	if (getcwd(cwd, 4096) == NULL)
		return (NULL);
	pwd = ft_strdup(cwd);
	return (pwd);
}

int			ft_pwd(char **argv, int fd, char **note)
{
	int		status;
	char	*pwd;

	status = 0;
	if (argv[1] != NULL)
	{
		*note = ft_strdup("pwd: ");
		status = ETMARGS;
	}
	pwd = get_pwd();
	if (pwd == NULL)
		return (ERRSYS);
	ft_putendl_fd(pwd, fd);
	free(pwd);
	return (status);
}

static int	update_pwd(t_hashtable *env, char *old, int errcode)
{
	t_variable	*tmp;
	char		*new;

	if (errcode)
	{
		free(old);
		return (errcode);
	}
	if ((new = get_pwd()) == NULL)
		return (ERRSYS);
	tmp = ht_get(env, "OLDPWD");
	free(tmp->value);
	tmp->value = old;
	tmp = ht_get(env, "PWD");
	free(tmp->value);
	tmp->value = new;
	return (errcode);
}

int			ft_cd(char **argv, t_hashtable *env, char **note)
{
	char	*old_pwd;
	int		status;
	char	*tmp;

	status = 0;
	if ((old_pwd = get_pwd()) == NULL)
		return (ERRSYS);
	if (argv[1] == NULL)
		status = chdir(get_value(env, "HOME"));
	else if (argv[2] == NULL)
		status = chdir(argv[1]);
	else
	{
		*note = ft_strdup("cd: ");
		status = ETMARGS;
	}
	if (status && status != ETMARGS)
	{
		tmp = ft_strjoin("cd: ", argv[1]);
		*note = ft_strjoin(tmp, ": ");
		free(tmp);
		status = ENOFDI;
	}
	return (update_pwd(env, old_pwd, status));
}

int			ft_exit(t_session *session)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	free_shell(session);
	exit(EXIT_SUCCESS);
}
