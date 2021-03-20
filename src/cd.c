/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:40:25 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 08:41:19 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "errcode.h"

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
