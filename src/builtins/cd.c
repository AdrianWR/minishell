/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 08:40:25 by aroque            #+#    #+#             */
/*   Updated: 2021/03/21 00:13:13 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "errcode.h"
#include "environment.h"

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

static void	pwd_variable(t_hashtable *env, const char *key, char *pwd)
{
	char		*tmp;
	char		*tmp2;
	t_variable	*v;

	v = ht_get(env, key);
	if (v)
	{
		free(v->value);
		v->value = pwd;
	}
	else
	{
		if (!pwd)
			tmp = ft_strdup(key);
		else
		{
			tmp2 = ft_strjoin(key, "=");
			tmp = ft_strjoin(tmp2, pwd);
			free(tmp2);
		}
		set_value(env, tmp, false);
		free(tmp);
		free(pwd);
	}
}

static int	update_pwd(t_hashtable *env, char *old, int errcode)
{
	char		*new;

	if (errcode)
	{
		free(old);
		return (errcode);
	}
	if ((new = get_pwd()) == NULL)
		return (ERRSYS);
	pwd_variable(env, "OLDPWD", old);
	pwd_variable(env, "PWD", new);
	return (errcode);
}

int			ft_cd(char **argv, t_hashtable *env, char **note)
{
	char	*old_pwd;
	int		status;

	status = 0;
	old_pwd = ft_strdup(get_value(env, "PWD"));
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
		*note = ft_strjoin("cd: ", argv[1]);
		status = ENOFDI;
	}
	return (update_pwd(env, old_pwd, status));
}
