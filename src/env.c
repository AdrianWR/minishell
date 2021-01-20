/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:45:19 by aroque            #+#    #+#             */
/*   Updated: 2021/01/20 19:25:50 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "libft.h"
#include <unistd.h>

#define HT_SIZE_ENV 1031

t_hashtable		*load_env(char *envp[])
{
	char		**pair;
	t_hashtable	*env;

	env = ht_create(HT_SIZE_ENV);
	while (*envp)
	{
		pair = ft_split(*envp, '=');
		ht_set(env, pair[0], pair[1]);
		free(pair[0]);
		free(pair);
		envp++;
	}
	return (env);
}

void			env(char *const *args, t_hashtable *env)
{
	(void)args;
	(void)env;
}

void			export(char *const *args, t_hashtable *env)
{
	(void)args;
	(void)env;
}

void			unset(char *const *args, t_hashtable *env)
{
	(void)args;
	(void)env;
}

/*
** TODO in CD
** SET OLDPWD
** SET PWD
*/

void			cd(char *const *args)
{
	if (chdir(args[1]) != 0)
		return ;
}
